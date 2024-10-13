#include <gtest/gtest.h>

#include <cmath>
#include <list>
#include <queue>
#include <string>

#include "../containers/container_adaptors/queue/s21_queue.h"
#include "../containers/sequence_containers/list/s21_list.h"

using namespace s21_containers;
TEST(s21_listTest, DefaultConstructor) {
  s21_queue<int> queue;
  std::queue<int, std::list<int>> queue1;
  EXPECT_EQ(queue.size(), queue1.size());
  EXPECT_EQ(queue.empty(), queue1.empty());
}

TEST(s21_list, ConstructorWithInitializerList) {
  s21_queue<std::string> queue{"10", "10", "10", "10"};
  std::queue<std::string, std::list<std::string>> queue_or;
  queue_or.push("10");
  queue_or.push("10");
  queue_or.push("10");
  queue_or.push("10");

  EXPECT_EQ(queue.size(), queue_or.size());
  while (!(queue.empty())) {
    EXPECT_EQ(queue.back(), queue_or.back());
    queue.pop();
    queue_or.pop();
  }
}

TEST(s21_list, CopyConstructor) {
  s21_queue<std::string> queue{"10", "20", "30", "40"};
  s21_queue<std::string> queue1(queue);
  EXPECT_EQ(queue.size(), queue1.size());
  while (!(queue.empty())) {
    EXPECT_EQ(queue.back(), queue1.back());
    queue.pop();
    queue1.pop();
  }
}

TEST(s21_list, MoveConstructor) {
  s21_queue<std::string> queue{"10", "20", "30", "40"};
  s21_queue<std::string> queue1(std::move(queue));
  EXPECT_EQ(queue.size(), 0); 
  EXPECT_EQ(queue1.size(), 4);
}

TEST(s21_list, MoveOperator) {
  s21_queue<std::string> queue{"10", "20", "30", "40"};
  s21_queue<std::string> queue1(std::move(queue));
  EXPECT_EQ(queue.size(), 0); 
  EXPECT_EQ(queue1.size(), 4);
}

TEST(s21_list, emplace) {
  s21_queue<int> queue;
  std::queue<int, std::list<int>> queue1;
  queue.emplace(10);
  queue.emplace(20);
  queue.emplace(30);
  queue1.emplace(10);
  queue1.emplace(20);
  queue1.emplace(30);
  EXPECT_EQ(queue.size(), queue1.size());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
