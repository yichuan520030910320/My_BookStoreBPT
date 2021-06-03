cmake_minimum_required(VERSION 3.10.2)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(code
        bplustree.hpp
        utility.hpp
        exceptions.hpp
      main.cpp
        UserManager.h
        UserManager.cpp
        BookStore.h
        BookManager.cpp
       )
