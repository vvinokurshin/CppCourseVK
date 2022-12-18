#include <gtest/gtest.h>

#include "set.hpp"

TEST(TestConstruct, Default) {
    set<int> my_s;
    std::set<int> std_s;

    EXPECT_EQ(my_s.size(), std_s.size());
}

TEST(TestConstruct, TwoIterators) {
    std::vector<int> data = {3, 2, 1, 4};
    set<int> my_s(data.begin(), data.end());
    std::set<int> std_s(data.begin(), data.end());

    EXPECT_EQ(my_s.size(), std_s.size());

    auto my_it = my_s.begin();

    for (auto std_it = std_s.begin(); std_it != std_s.end(); std_it++, ++my_it) {
        EXPECT_EQ(*my_it, *std_it);
    }
}

TEST(TestConstInterators, Simple) {
    std::vector<int> data = {3, 2, 1, 4};
    set<int> my_s(data.begin(), data.end());
    std::set<int> std_s(data.begin(), data.end());

    EXPECT_EQ(*my_s.cbegin(), *std_s.cbegin());
}

TEST(TestConstruct, InitializerList) {
    std::initializer_list<int> list = {5, 1, 3, 2, 6};
    set<int> my_s(list);
    std::set<int> std_s = list;

    EXPECT_EQ(my_s.size(), std_s.size());

    auto my_it = my_s.begin();

    for (auto std_it = std_s.begin(); std_it != std_s.end(); std_it++, ++my_it) {
        EXPECT_EQ(*my_it, *std_it);
    }
}

TEST(TestOperators, OperatorEQ) {
    std::initializer_list<int> list = {5, 1, 3, 2, 6};
    set<int> s1(list);
    set<int> s2 = s1;

    EXPECT_EQ(s1.size(), s2.size());

    auto s1_it = s1.begin();

    for (auto s2_it = s2.begin(); s2_it != s2.end(); ++s1_it, ++s2_it) {
        EXPECT_EQ(*s1_it, *s2_it);
    }
}

TEST(TestMethods, Empty) {
    set<int> s;
    std::set<int> ans;
    s.insert(10);
    ans.insert(10);

    EXPECT_EQ(s.size(), ans.size());

    auto s_it = s.begin();

    for (auto ans_it = ans.begin(); ans_it != ans.end(); ++s_it, ++ans_it) {
        EXPECT_EQ(*s_it, *ans_it);
    }
}

TEST(TestInsert, OneEl) {
    std::initializer_list<int> list = {4};
    set<int> s(list);
    std::set<int> ans = list;
    s.insert(10);
    ans.insert(10);

    EXPECT_EQ(s.size(), ans.size());

    auto s_it = s.begin();

    for (auto ans_it = ans.begin(); ans_it != ans.end(); ++s_it, ++ans_it) {
        EXPECT_EQ(*s_it, *ans_it);
    }
}

TEST(TestInsert, Simple) {
    std::initializer_list<int> list = {2, 3, 5, 1, 6};
    set<int> s(list);
    std::set<int> ans = list;
    s.insert(10);
    ans.insert(10);

    EXPECT_EQ(s.size(), ans.size());

    auto s_it = s.begin();

    for (auto ans_it = ans.begin(); ans_it != ans.end(); ++s_it, ++ans_it) {
        EXPECT_EQ(*s_it, *ans_it);
    }
}

TEST(TestInsert, AlreadyHasElement) {
    std::initializer_list<int> list = {2, 3, 5, 1, 6};
    set<int> s(list);
    std::set<int> ans = list;
    s.insert(5);
    ans.insert(5);

    EXPECT_EQ(s.size(), ans.size());

    auto s_it = s.begin();

    for (auto ans_it = ans.begin(); ans_it != ans.end(); ++s_it, ++ans_it) {
        EXPECT_EQ(*s_it, *ans_it);
    }
}

TEST(TestErase, Empty) {
    set<int> s;
    std::set<int> ans;
    s.erase(5);
    ans.erase(5);

    EXPECT_EQ(s.size(), ans.size());
}

TEST(TestErase, OneEl) {
    std::initializer_list<int> list = {1};
    set<int> s(list);
    std::set<int> ans = list;
    s.erase(1);
    ans.erase(1);

    EXPECT_EQ(s.size(), ans.size());
}

TEST(TestErase, TwoEl) {
    std::initializer_list<int> list = {1, 2};
    set<int> s(list);
    std::set<int> ans = list;
    s.erase(1);
    ans.erase(1);

    EXPECT_EQ(s.size(), ans.size());

    auto s_it = s.begin();

    for (auto ans_it = ans.begin(); ans_it != ans.end(); ++s_it, ++ans_it) {
        EXPECT_EQ(*s_it, *ans_it);
    }
}

TEST(TestErase, ElementNotExists) {
    std::initializer_list<int> list = {1, 2};
    set<int> s(list);
    std::set<int> ans = list;
    s.erase(3);
    ans.erase(3);

    EXPECT_EQ(s.size(), ans.size());

    auto s_it = s.begin();

    for (auto ans_it = ans.begin(); ans_it != ans.end(); ++s_it, ++ans_it) {
        EXPECT_EQ(*s_it, *ans_it);
    }
}

TEST(TestEmpty, True) {
    set<int> s;
    std::set<int> ans;

    EXPECT_EQ(s.empty(), ans.empty());
}

TEST(TestEmpty, False) {
    std::initializer_list<int> list = {1};
    set<int> s(list);
    std::set<int> ans = list;

    EXPECT_EQ(s.empty(), ans.empty());
}

TEST(TestFind, Empty) {
    set<int> s;
    auto res = s.find(3);

    EXPECT_EQ(res, s.end());
}

TEST(TestFind, OneEl) {
    std::initializer_list<int> list = {3};
    set<int> s(list);
    auto res = s.find(3);

    EXPECT_EQ(res, s.begin());
}

TEST(TestFind, Simple) {
    std::initializer_list<int> list = {2, 1, 3, 5};
    set<int> s(list);
    auto res = s.find(3);

    EXPECT_EQ(*res, 3);
}

TEST(TestFind, NotExists) {
    std::initializer_list<int> list = {2, 1, 3, 5};
    set<int> s(list);
    auto res = s.find(6);

    EXPECT_EQ(res, s.end());
}

TEST(TestLowerBound, Empty) {
    set<int> s;
    auto res = s.lower_bound(3);

    EXPECT_EQ(res, s.end());
}

TEST(TestLowerBound, OneElEQ) {
    std::initializer_list<int> list = {3};
    set<int> s(list);
    auto res = s.lower_bound(3);

    EXPECT_EQ(res, s.begin());
}

TEST(TestLowerBound, OneElLT) {
    std::initializer_list<int> list = {3};
    set<int> s(list);
    auto res = s.lower_bound(4);

    EXPECT_EQ(res, s.end());
}

TEST(TestLowerBound, OneElGT) {
    std::initializer_list<int> list = {4};
    set<int> s(list);
    auto res = s.lower_bound(3);

    EXPECT_EQ(res, s.begin());
}

TEST(TestLowerBound, Simple) {
    std::initializer_list<int> list = {3, 1, 2, 4, 10};
    set<int> s(list);
    auto res = s.lower_bound(8);

    EXPECT_EQ(*res, 10);
}
