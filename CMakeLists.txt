cmake_minimum_required(VERSION 3.10.2)
project(Bookstore)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Ofast")
set(src_dir
        main.cpp
        People.cpp People.h Book.cpp Book.h
add_executable(code ${src_dir})