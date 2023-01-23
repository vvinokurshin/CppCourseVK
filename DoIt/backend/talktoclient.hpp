#pragma once
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <iostream>
#include "json.hpp"
#include "database_interaction.h"
using json = nlohmann::json;

boost::asio::io_service service;

struct UserUpdate {
    size_t user_id;
    bool hasChanges;
};

#define MEM_FN(x)       boost::bind(&self_type::x, shared_from_this())
#define MEM_FN1(x,y)    boost::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z)  boost::bind(&self_type::x, shared_from_this(),y,z)

class TalkToClient : public boost::enable_shared_from_this<TalkToClient>, boost::noncopyable {
    typedef TalkToClient self_type;
    TalkToClient(DatabaseInteraction &di, std::vector<UserUpdate> &uu) : 
    sock_(service), started_(false), timer_(service), clients_changed_(false), interactor(di), _userUpdates(uu) {
    }
public:
    typedef boost::system::error_code error_code;
    typedef boost::shared_ptr<TalkToClient> ptr;

    static ptr new_(DatabaseInteraction &di, std::vector<UserUpdate> &uu) {
        ptr new_(new TalkToClient(di, uu));
        return new_;
    }
    void start() 
    {
        started_ = true;
        last_ping = boost::posix_time::microsec_clock::local_time();
        do_read();
    }
    void stop() 
    {
        if (!started_) return;
        started_ = false;
        sock_.close();
    }
    bool started() const 
    { 
        return started_; 
    }
    boost::asio::ip::tcp::socket& sock() 
    { 
        return sock_; 
    }
    std::string username() const 
    { 
        return username_; 
    }
private:
    void on_read(const error_code& err, size_t bytes) 
    {
        if (err) stop();
        if (!started()) return;
        std::string msg(read_buffer_, bytes);
        json msg_json = json::parse(msg);
        if (msg_json["cmd"] == "login") on_login(msg_json);
        else if (msg_json["cmd"] == "ping") on_ping(msg_json);
        else on_work_with_database(msg_json);
    }
    void on_login(json msg_json) 
    {
        std::string response = interactor.on_login(msg_json);
        do_write(response);
    }
    void on_work_with_database(json msg_json)
    {
        json response = interactor.analyze_msg(msg_json);
        if (response["users_changed"] != nullptr) {
            std::cout << "There are other users that got updates\n";
            json users = response["users_changed"];
            std::cout << "here" << users << std::endl;
            for (size_t i = 0; i < users.size(); ++i) {
                for (auto &user : _userUpdates) {
                    if (user.user_id == users[i]["user_id"]) {
                        user.hasChanges = true;
                        break;
                    }
                }
            }
            response["users_changed"] = nullptr;
        }

        do_write(convert(response));
    }
    void on_ping(json rqst) 
    {
        std::cout << "On Ping\n";
        json result;

        result["response"] = "no changes";  
        for (auto &user : _userUpdates) {
            if (user.hasChanges){
                std::cout << user.user_id << " "<< user.hasChanges << std::endl;
                }
            if (user.user_id == rqst["user_id"] && user.hasChanges) {
                result["response"] = "has changes"; 
                user.hasChanges = false; 
                break;
            }
        }
        do_write(convert(result));
    }

    void do_ping() {
        json result;
        result["response"] = "ping";
        do_write(convert(result));
    }

    void on_check_ping() 
    {
        boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
        if ((now - last_ping).total_milliseconds() > 10000) {
            std::cout << "stopping " << username_ << " - no ping in time" << std::endl;
            stop();
        }
        last_ping = boost::posix_time::microsec_clock::local_time();
    }
    void post_check_ping() {
        timer_.expires_from_now(boost::posix_time::millisec(10000));
        timer_.async_wait(MEM_FN(on_check_ping));
    }

    void on_write(const error_code& err, size_t bytes) {
        do_read();
    }

    void do_read() {
        async_read(sock_, boost::asio::buffer(read_buffer_), MEM_FN2(read_complete, _1, _2), MEM_FN2(on_read, _1, _2));
        post_check_ping();
    }
    void do_write(const std::string& msg) {
        if (!started()) return;
        std::copy(msg.begin(), msg.end(), write_buffer_);
        sock_.async_write_some(boost::asio::buffer(write_buffer_, msg.size()),MEM_FN2(on_write, _1, _2));
    }

    size_t read_complete(const boost::system::error_code& err, size_t bytes) {
        if (err) return 0;
        bool found = std::find(read_buffer_, read_buffer_ + bytes, '\n') < read_buffer_ + bytes;
        return found ? 0 : 1;
    }
private:
    boost::asio::ip::tcp::socket sock_;
    enum { max_msg = 1024 };
    char read_buffer_[max_msg];
    char write_buffer_[max_msg];
    bool started_;
    std::string username_;
    boost::asio::deadline_timer timer_;
    boost::posix_time::ptime last_ping;
    bool clients_changed_;
    DatabaseInteraction &interactor;
    std::vector<UserUpdate> &_userUpdates;
    json_to_string_response_convert convert;
};