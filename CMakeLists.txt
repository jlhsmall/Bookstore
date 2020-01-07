cmake_minimum_required(VERSION 3.10)
project(Bookstore)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bookstore main.cpp People.cpp People.h Book.cpp Book.h)