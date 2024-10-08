# MAKEFILE FOR CONTAINERS
CC=g++
COMPILE_FLAGS= -Wall -Werror -Wextra -std=c++17 -ansi -pedantic -Weffc++ -Wshadow
OPTIMIZATION_FLAGS= -O2 -Wpessimizing-move -Wredundant-move
SANITIZER_FLAGS= -fsanitize=address -fsanitize=undefined
VECTOR_TEST_SRC=tests/vector_test.cpp

all:

vector-test:
	$(CC) -g $(SANITIZER_FLAGS) $(VECTOR_TEST_SRC) -lgtest -o vector-test.out

style-check:
	find . -name "*.cpp" -o -name "*.h" | xargs clang-format -n -verbose -Werror --style=Google
style:
	find . -name "*.cpp" -o -name "*.h" | xargs clang-format -i -verbose --style=Google
