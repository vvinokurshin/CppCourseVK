#include "gtest/gtest.h"
#include "basic_tests.h"

int main(int argc, char **argv)
{
    internal_tests::run_all();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}