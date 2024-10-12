#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../containers/sequence_containers/vector/s21_vector.h"

using namespace s21_containers;
TEST(s21_vectorTest, DefaultConstructor) {
  s21_vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(s21_vectorTest, SizeConstructorTrivial) {
  s21_vector<int> vec(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_GE(vec.capacity(), 5);
  EXPECT_FALSE(vec.empty());
}

TEST(s21_vectorTest, SizeConstructorNotTrivial) {
  s21_vector<std::string> vec(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_GE(vec.capacity(), 5);
  EXPECT_FALSE(vec.empty());
}

TEST(s21_vectorTest, SizeConstructorNotTrivial2) {
  s21_vector<std::vector<std::string>> vec(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_GE(vec.capacity(), 5);
  EXPECT_FALSE(vec.empty());
}

TEST(s21_vectorTest, SizeConstructorNotTrivial3) {
  s21_vector<s21_vector<int>> vec(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_GE(vec.capacity(), 5);
  EXPECT_FALSE(vec.empty());
}

TEST(s21_vectorTest, SizeConstructorNotTrivial4) {
  s21_vector<s21_containers::s21_vector<std::string>> vec(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_GE(vec.capacity(), 5);
  EXPECT_FALSE(vec.empty());
}

TEST(s21_vectorTest, SizeConstructorNotTrivial5) {
  class s21_test_class {
   public:
    s21_test_class() = default;
    s21_test_class(const s21_test_class &other) = delete;
    s21_test_class(s21_test_class &&other) = delete;

   private:
    int x;
  };
  s21_vector<s21_test_class> vec(5);
  std::vector<s21_test_class> vec_or(5);
  EXPECT_EQ(vec.size(), vec_or.size());
  EXPECT_EQ(vec.capacity(), vec_or.capacity());
  EXPECT_EQ(vec.empty(), vec_or.empty());
}

TEST(s21_vectorTest, SizeValueConstructor) {
  s21_vector<int> vec(5, 42);
  std::vector<int> vec1(5, 42);
  EXPECT_EQ(vec.size(), vec1.size());
  EXPECT_EQ(vec.capacity(), vec1.size());
  EXPECT_EQ(vec.empty(), vec1.empty());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], vec1[i]);
  }
}

TEST(s21_vectorTest, SizeValueConstructorNonTrivial) {
  s21_vector<std::string> vec(5, "100");
  std::vector<std::string> vec1(5, "100");
  EXPECT_EQ(vec.size(), vec1.size());
  EXPECT_EQ(vec.capacity(), vec1.size());
  EXPECT_EQ(vec.empty(), vec1.empty());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], vec1[i]);
  }
}

TEST(s21_vectorTest, SizeValueConstructorNonTrivial2) {
  s21_vector<s21_vector<std::string>> vec(5,
                                          s21_vector<std::string>(10, "100"));
  std::vector<std::vector<std::string>> vec1(
      5, std::vector<std::string>(10, "100"));
  EXPECT_EQ(vec.size(), vec1.size());
  EXPECT_EQ(vec.capacity(), vec1.size());
  EXPECT_EQ(vec.empty(), vec1.empty());
  for (size_t i = 0; i < vec.size(); ++i) {
    for (size_t j = 0; j < vec[0].size(); ++j) {
      EXPECT_EQ(vec[i][j], vec1[i][j]);
    }
  }
}

// TEST(s21_vectorTest, SizeValueConstructorNonTrivial3) {
//   class s21_test_class {
//   public:
//     s21_test_class() = default;
//     // s21_test_class(const s21_test_class &other) = delete;
//     // s21_test_class(s21_test_class &&other) = delete;
//     s21_test_class(int x) : x(x) {}
//     int x;
//   };
//   s21_vector<s21_test_class> vec(5, s21_test_class(10));
//   std::vector<s21_test_class> vec1(5, s21_test_class(10));
//   EXPECT_EQ(vec.size(), vec1.size());
//   EXPECT_EQ(vec.capacity(), vec1.size());
//   EXPECT_EQ(vec.empty(), vec1.empty());
//   for (size_t i = 0; i < vec.size(); ++i) {
//     EXPECT_EQ(vec[i], vec1[i]);
//   }
// }

TEST(s21_vectorTest, CopyConstructor) {
  s21_vector<int> vec1(5, 42);
  s21_vector<int> vec2(vec1);
  EXPECT_EQ(vec2.size(), 5);
  EXPECT_GE(vec2.capacity(), 5);
  EXPECT_FALSE(vec2.empty());
  for (size_t i = 0; i < vec2.size(); ++i) {
    EXPECT_EQ(vec2[i], 42);
  }
  vec1[0] = 100;
  EXPECT_NE(vec1[0], vec2[0]);
}

TEST(s21_vectorTest, CopyConstructorWithOriginal) {
  s21_vector<int> vec1(5, 42);
  s21_vector<int> vec2(vec1);
  std::vector<int> vec3(5, 42);
  std::vector<int> vec4(vec3);
  EXPECT_EQ(vec2.size(), vec4.size());
  EXPECT_EQ(vec2.capacity(), vec4.capacity());
  EXPECT_EQ(vec2.empty(), vec4.empty());
  for (size_t i = 0; i < vec2.size(); ++i) {
    EXPECT_EQ(vec2[i], vec4[i]);
  }
}

TEST(s21_vectorTest, MoveConstructor) {
  s21_vector<int> vec1(5, 42);
  s21_vector<int> vec2(std::move(vec1));
  std::vector<int> vec3(5, 42);
  std::vector<int> vec4(std::move(vec3));
  EXPECT_EQ(vec2.size(), vec4.size());
  EXPECT_EQ(vec2.capacity(), vec4.capacity());
  EXPECT_EQ(vec2.empty(), vec4.empty());
  for (size_t i = 0; i < vec2.size(); ++i) {
    EXPECT_EQ(vec2[i], vec4[i]);
  }
  EXPECT_EQ(vec1.size(), vec3.size());
  EXPECT_EQ(vec1.capacity(), vec3.capacity());
  EXPECT_EQ(vec1.empty(), vec3.empty());
}

TEST(s21_vectorTest, InitializerListConstructor) {
  s21_vector<int> vec({1, 2, 3, 4, 5});
  std::vector<int> vec1({1, 2, 3, 4, 5});
  EXPECT_EQ(vec.size(), vec1.size());
  EXPECT_EQ(vec.capacity(), vec1.capacity());
  EXPECT_EQ(vec.empty(), vec1.empty());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], vec1[i]);
  }
}

TEST(s21_vectorTest, AssignmentOperator) {
  s21_vector<int> vec1({1, 2, 3, 4, 5, 6});
  s21_vector<int> vec2 = std::move(vec1);
  std::vector<int> vec3({1, 2, 3, 4, 5, 6});
  std::vector<int> vec4 = std::move(vec3);
  EXPECT_EQ(vec2.size(), vec4.size());
  EXPECT_EQ(vec2.capacity(), vec4.capacity());
  EXPECT_EQ(vec2.empty(), vec4.empty());
  for (size_t i = 0; i < vec2.size(); ++i) {
    EXPECT_EQ(vec2[i], vec4[i]);
  }
  EXPECT_EQ(vec1.size(), vec3.size());
  EXPECT_EQ(vec1.capacity(), vec3.capacity());
  EXPECT_EQ(vec1.empty(), vec3.empty());
}

TEST(s21_vectorTest, ClearTest) {
  s21_vector<std::string> vec{"1", "2030", "00420-"};
  std::vector<std::string> vec1{"1", "2030", "00420-"};
  vec.clear();
  vec1.clear();
  EXPECT_EQ(vec.size(), vec1.size());
  EXPECT_EQ(vec.capacity(), vec1.capacity());
  EXPECT_EQ(vec.empty(), vec1.empty());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_TRUE(vec[i].empty());
  }
}

TEST(s21_vectorTest, IteratorTest) {
  s21_vector<int> p(10, 5);
  for (auto start = p.begin(), finish = p.end(); start != finish; ++start) {
    EXPECT_EQ(*start, 5);
  }
}

TEST(s21_vectorTest, emplace_backTest) {
  s21_vector<int> vec;
  vec.emplace_back(1);
  vec.emplace_back(2);
  vec.emplace_back(3);
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], i + 1);
  }
  EXPECT_EQ(vec.capacity(), 4);
}

TEST(s21_vectorTest, emplace_backTest1) {
  s21_vector<int> vec;
  vec.emplace_back(1);
  vec.emplace_back(2);
  vec.emplace_back(3);
  vec.emplace_back(4);
  vec.emplace_back(5);
  vec.emplace_back(6);
  vec.emplace_back(7);
  vec.emplace_back(8);
  vec.emplace_back(vec[5]);
  for (size_t i = 0; i < vec.size() - 1; ++i) {
    EXPECT_EQ(vec[i], i + 1);
  }
  EXPECT_EQ(vec[5], vec.back());
  EXPECT_EQ(vec.capacity(), 16);
}

TEST(s21_vectorTest, emplace_backTest2) {
  s21_vector<std::pair<int, int>> vec;
  vec.emplace_back(1, 2);
  vec.emplace_back(3, 4);
  vec.emplace_back(5, 6);
  vec.emplace_back(vec[0].first, vec[0].second);
  for (size_t i = 0; i < vec.size() - 1; ++i) {
    EXPECT_EQ(vec[i].first, i * 2 + 1);
    EXPECT_EQ(vec[i].second, i * 2 + 2);
  }
  EXPECT_EQ(vec[0].first, vec.back().first);
  EXPECT_EQ(vec[0].second, vec.back().second);
  EXPECT_EQ(vec.capacity(), 4);
}

TEST(s21_vectorTest, emplace_backTest3) {
  s21_vector<std::string> vec;
  vec.emplace_back("10");
  vec.emplace_back("20");
  vec.emplace_back("30");
  vec.emplace_back("40");
  vec.emplace_back("50");
  vec.emplace_back("60");
  vec.emplace_back("70");
  vec.emplace_back("80");
  vec.emplace_back(vec[0]);
  EXPECT_EQ(vec[0], vec.back());
  EXPECT_EQ(vec.capacity(), 16);
}

TEST(s21_vectorTest, emplace_backTest4) {
  s21_vector<std::vector<int>> vec;
  vec.emplace_back(5, 10);
  vec.emplace_back(6, 10);
  vec.emplace_back(7, 10);
  vec.emplace_back(8, 10);
  vec.emplace_back(9, 10);
  vec.emplace_back(10, 10);
  vec.emplace_back(11, 10);
  vec.emplace_back(12, 10);
  vec.emplace_back(vec[0]);
  EXPECT_EQ(vec[0], vec.back());
  EXPECT_EQ(vec.capacity(), 16);
}

TEST(s21_vectorTest, emplace_backTest5) {
  s21_vector<std::string> vec;
  vec.emplace_back("10");
  vec.emplace_back(vec[0]);
  vec.emplace_back(vec[0]);
  vec.emplace_back(vec[0]);
  vec.emplace_back(vec[3]);
  vec.emplace_back(vec[0]);
  vec.emplace_back(vec[0]);
  vec.emplace_back(vec[0]);
  vec.emplace_back(vec[5]);
  vec[2] = "100";
  EXPECT_EQ(vec[0], vec.back());
  EXPECT_EQ(vec.capacity(), 16);
}

TEST(s21_vectorTest, eraseTest) {
  s21_vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  p.erase(p.begin());
  EXPECT_EQ(p[0], "20");
}

TEST(s21_vectorTest, eraseTest1) {
  s21_vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  auto pointer = p.begin();
  pointer -= 10;
  p.erase(pointer);
  EXPECT_EQ(p[0], "10");
}

TEST(s21_vectorTest, eraseTest2) {
  s21_vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  auto pointer = p.begin();
  pointer += 10;
  p.erase(pointer);
  EXPECT_EQ(p[0], "10");
}

TEST(s21_vectorTest, eraseTest3) {
  s21_vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  auto pointer = p.begin();
  pointer++;
  p.erase(pointer);
  std::vector<std::string> vec;
  vec.push_back("10");
  vec.push_back("20");
  vec.push_back("30");
  auto pointer1 = vec.begin();
  pointer1++;
  vec.erase(pointer1);
  EXPECT_EQ(p[0], vec[0]);
  EXPECT_EQ(p[1], vec[1]);
}

TEST(s21_vectorTest, multipleEraseTest) {
  s21_vector<int> p;
  p.push_back(10);
  p.push_back(20);
  p.push_back(30);
  auto pointer = p.begin();
  auto pointer1 = p.end();
  pointer1++;
  auto pointer2 = p.erase(pointer, pointer1);
  EXPECT_EQ(*pointer2, 10);
}

TEST(s21_vectorTest, multipleEraseTest2) {
  s21_vector<int> p;
  p.push_back(10);
  p.push_back(20);
  p.push_back(30);
  auto pointer = p.begin();
  pointer++;
  auto pointer1 = p.end();
  auto pointer2 = p.erase(pointer, pointer1);
  EXPECT_EQ(*pointer2, 20);
}

TEST(s21_vectorTest, multipleEraseTest3) {
  s21_vector<int> p;
  p.push_back(10);
  p.push_back(20);
  p.push_back(30);
  p.push_back(40);
  auto pointer = p.begin();
  pointer++;
  auto pointer1 = p.end();
  pointer1--;
  auto pointer2 = p.erase(pointer, pointer1);
  EXPECT_EQ(*pointer2, 40);
  EXPECT_EQ(p[1], 40);
}

TEST(s21_vectorTest, emplaceTest) {
  s21_vector<int> p;
  p.push_back(10);
  p.push_back(20);
  p.push_back(30);
  p.push_back(40);
  auto pointer = p.begin();
  pointer++;
  p.emplace(pointer, p[0]);
  EXPECT_EQ(p[0], p[1]);
}

TEST(s21_vectorTest, emplaceTest2) {
  s21_vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  p.push_back("40");
  p.push_back("50");
  auto pointer = p.begin();
  pointer++;
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  EXPECT_EQ(p[0], p[1]);
}

TEST(s21_vectorTest, emplaceTest3) {
  s21_vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  p.push_back("40");
  auto pointer = p.begin();
  pointer++;
  p.emplace(pointer, p[0]);
  EXPECT_EQ(p[0], p[1]);
}

TEST(s21_vectorTest, emplaceTest4) {
  s21_vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  p.push_back("40");
  p.push_back("50");
  auto pointer = p.begin();
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  EXPECT_EQ(p[0], p[1]);
}

TEST(s21_vectorTest, emplaceTest5) {
  s21_vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  p.push_back("40");
  p.push_back("50");
  auto pointer = p.end();
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  EXPECT_EQ(p[0], p[p.size() - 1]);
}

TEST(s21_vectorTest, shrink_to_fitTest) {
  s21_vector<int> p;
  p.push_back(10);
  p.push_back(20);
  p.push_back(30);
  p.push_back(40);
  s21_vector<int>::iterator pointer = p.begin();
  pointer++;
  p.emplace(pointer, p[0]);
  p.shrink_to_fit();
  EXPECT_EQ(p.capacity(), 5);
}

TEST(s21_vectorTest, shrink_to_fitTest2) {
  s21_vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  p.push_back("40");
  p.push_back("50");
  p.shrink_to_fit();
  EXPECT_EQ(p.capacity(), 5);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
