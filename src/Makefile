# MAKEFILE FOR CONTAINERS
CC=gcc
COMPILE_FLAGS= -Wall -Werror -Wextra -std=c++17 -ansi -pedantic -Weffc++ -Wshadow
OPTIMIZATION_FLAGS= -O2

all: s21_containers.h


style-check:
	find . -name "*.cpp" -o -name "*.h" | xargs clang-format -n -verbose --style=Google
style:
	find . -name "*.cpp" -o -name "*.h" | xargs clang-format -i -verbose --style=Google
