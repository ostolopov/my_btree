cmake_minimum_required(VERSION 3.29)
project(my_btree)

set(CMAKE_CXX_STANDARD 20)

add_executable(my_btree main.cpp
        my_btree_funcs.cpp
        my_btree_funcs.h)
