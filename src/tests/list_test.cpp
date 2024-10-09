#include <gtest/gtest.h>

#include <list>
#include <string>

#include "../containers/sequence_containers/list/s21_list.h"

using namespace s21_containers;
TEST(s21_listTest, DefaultConstructor) {
  s21_list<int> list;
  // EXPECT_EQ(list.size(), 0);

  // EXPECT_TRUE(list.empty());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
