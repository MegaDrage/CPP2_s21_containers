#include <gtest/gtest.h>

#include <cmath>
#include <list>
#include <string>

#include "../containers/sequence_containers/list/s21_list.h"

using namespace s21_containers;
TEST(s21_listTest, DefaultConstructor) {
  s21_list<int> list;
  std::list<int> l1;
  EXPECT_EQ(list.max_size(), l1.max_size());
  EXPECT_EQ(list.size(), l1.size());
  EXPECT_EQ(list.empty(), l1.empty());
}

TEST(s21_listTest, DefaultConstructorIterator) {
  s21_list<int> list;
  std::list<int> l1;
  auto start = list.begin();
  auto start1 = l1.begin();
  EXPECT_EQ(*start, *start1);
}

TEST(s21_list, ConstructorWithParameters) {
  s21_list<std::string> list(10);
  std::list<std::string> l1(10);
  EXPECT_EQ(list.size(), l1.size());
}

TEST(s21_list, ConstructorWithInitializerList) {
  s21_list<std::string> list{"10", "10", "10", "10"};
  std::list<std::string> list_or{"10", "10", "10", "10"};

  EXPECT_EQ(list.size(), list_or.size());
  for (auto i = list.begin(), j = list.end(); i != j; ++i) {
    EXPECT_EQ(*i, "10");
  }
}

TEST(s21_list, CopyConstructor) {
  s21_list<std::string> list{"10", "20", "30", "40"};
  s21_list<std::string> list1(list);
  auto other_ptr = list1.begin();
  EXPECT_EQ(list.size(), list1.size());
  for (auto i = list.begin(), j = list.end(); i != j; ++i, ++other_ptr) {
    EXPECT_EQ(*i, *other_ptr);
  }
}

TEST(s21_list, MoveConstructor) {
  s21_list<std::string> list{"10", "20", "30", "40"};
  s21_list<std::string> list1(std::move(list));
  std::list<std::string> list2{"10", "20", "30", "40"};
  std::list<std::string> list3(std::move(list2));
  EXPECT_EQ(list1.size(), list3.size());
  auto itt = list3.begin();
  for (auto it = list1.begin(); it != list1.end(); ++it, ++itt)
    EXPECT_EQ(*it, *itt);
}

TEST(s21_list, MoveOperator) {
  s21_list<std::string> list{"10", "20", "30", "40"};
  s21_list<std::string> list1 = std::move(list);
  std::list<std::string> list2{"10", "20", "30", "40"};
  std::list<std::string> list3 = std::move(list2);
  EXPECT_EQ(list1.size(), list3.size());
  auto itt = list3.begin();
  for (auto it = list1.begin(); it != list1.end(); ++it, ++itt)
    EXPECT_EQ(*it, *itt);
}

TEST(s21_list, emplaceBack) {
  s21_list<int> list;
  std::list<int> list1;
  list.emplace_back(10);
  list.emplace_back(20);
  list.emplace_back(30);
  list1.emplace_back(10);
  list1.emplace_back(20);
  list1.emplace_back(30);
  EXPECT_EQ(list.size(), list1.size());
}

TEST(s21_list, emplaceBackString) {
  s21_list<std::string> list;
  std::list<std::string> list1;
  list.emplace_back("10");
  list.emplace_back("20");
  list.emplace_back("30");
  list1.emplace_back("10");
  list1.emplace_back("20");
  list1.emplace_back("30");
  EXPECT_EQ(list.size(), list1.size());
}

TEST(s21_list, pop_back) {
  s21_list<std::string> list;
  std::list<std::string> list1;
  list.emplace_back("10");
  list.emplace_back("20");
  list.emplace_back("30");
  list1.emplace_back("10");
  list1.emplace_back("20");
  list1.emplace_back("30");
  list.pop_back();
  list1.pop_back();
  EXPECT_EQ(list.size(), list1.size());
}

TEST(s21_list, pop_back_all) {
  s21_list<std::string> list;
  std::list<std::string> list1;
  list.emplace_back("10");
  list.emplace_back("20");
  list.emplace_back("30");
  list1.emplace_back("10");
  list1.emplace_back("20");
  list1.emplace_back("30");
  list.pop_back();
  list.pop_back();
  list.pop_back();
  list1.pop_back();
  list1.pop_back();
  list1.pop_back();
  EXPECT_EQ(list.size(), list1.size());
}

TEST(s21_list, pop_front) {
  s21_list<std::string> list;
  std::list<std::string> list1;
  list.emplace_back("10");
  list.emplace_back("20");
  list.emplace_back("30");
  list1.emplace_back("10");
  list1.emplace_back("20");
  list1.emplace_back("30");
  list.pop_front();
  list1.pop_front();
  EXPECT_EQ(list.size(), list1.size());
}

TEST(s21_list, pop_front_all) {
  s21_list<std::string> list;
  std::list<std::string> list1;
  list.emplace_front("10");
  list.emplace_front("20");
  list.emplace_front("30");
  list1.emplace_front("10");
  list1.emplace_front("20");
  list1.emplace_front("30");
  list.pop_front();
  list.pop_front();
  list.pop_front();
  list1.pop_front();
  list1.pop_front();
  list1.pop_front();
  EXPECT_EQ(list.size(), list1.size());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
