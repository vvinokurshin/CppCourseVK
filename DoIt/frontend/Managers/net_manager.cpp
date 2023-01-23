#include "net_manager.h"

void NetManager::pingLoop(size_t user_id) {
    try {
        _ping_sock.connect(_ep);
    } catch (boost::system::system_error& err) {
        std::cout << "Ping Connect failed\n";
        return;
    }
    try {
        while (_started) {
            json js_ping;
            int err = 0;
            js_ping["cmd"] = "ping";
            js_ping["user_id"] = user_id;
            asio::write(_ping_sock, asio::buffer(js_ping.dump() + "\n"), asio::transfer_all());
            size_t bytes = boost::asio::read(_ping_sock, asio::buffer(_buff_ping),
                                             boost::bind(&NetManager::read_complete, _buff_ping, _1, _2));
            std::string response(_buff_ping, bytes - 1);  // -1 to remove \n

            json resp = json::parse(response);

            if (resp["response"] == "has changes") {
                updateDataSignal();
            }

            boost::this_thread::sleep(boost::posix_time::millisec(2000));
        }
    } catch (boost::system::system_error& err) {
        std::cout << "Ping Failed\n";
        _ping_sock.close();
        throw err;
    }

    _ping_sock.close();
}

void NetManager::connect() {
    try {
        _sock.connect(_ep);
    } catch (boost::system::system_error& err) {
        std::cout << "Connect failed\n";
        throw err;
    }
}

void NetManager::disconnect() {
    _sock.close();
}

void NetManager::sendMessage(const std::string& request, int& err_code) {
    err_code = 0;
    try {
        asio::write(_sock, asio::buffer(request), asio::transfer_all());
    } catch (std::exception& exc) { err_code = 1; }
}

std::string NetManager::getMessage(int& err_code) {
    err_code = 0;
    size_t bytes =
        boost::asio::read(_sock, asio::buffer(_buff), boost::bind(&NetManager::read_complete, _buff, _1, _2));
    std::string msg(_buff, bytes - 1);  // -1 to remove \n
    return msg;
}

void NetManager::sendFile(const std::string& fileName, int& err_code) {
    std::ifstream input(fileName, std::ios::binary);
    std::string buf(std::istreambuf_iterator<char>(input), {});
    err_code = 0;
    try {
        connect();
        _sock.write_some(asio::buffer(buf.data(), buf.size()));
        disconnect();
    } catch (std::exception& exc) { err_code = 1; }
    input.close();
}

size_t NetManager::read_complete(char* buff, const system::error_code& err, size_t bytes) {
    if (err)
        return 0;
    bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;
    return found ? 0 : 1;
}
