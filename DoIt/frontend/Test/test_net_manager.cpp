#include <gtest/gtest.h>

#include "net_manager.h"

TEST(NetWorkerTest, SendMessageTest) {
    NetManager netWorker;
    int err = 0;
    netWorker.sendMessage("some_message", err);
    EXPECT_EQ(err, 1);
}

TEST(NetWorkerTest, SendFileNotExistsTest) {
    NetManager netWorker;
    int err = 0;
    netWorker.sendFile("./Test/SentFiles/not_exist_file.txt", err);
    EXPECT_EQ(err, 1);
}

TEST(NetWorkerTest, SendFileImgTest) {
    NetManager netWorker;
    int err = 0;
    netWorker.sendFile("./Test/SentFiles/test_640_480.jpg", err);
    EXPECT_EQ(err, 1);
}

TEST(NetWorkerTest, SendFileTxtTest) {
    NetManager netWorker;
    int err = 0;
    netWorker.sendFile("./Test/SentFiles/text.txt", err);
    EXPECT_EQ(err, 1);
}
