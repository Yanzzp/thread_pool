cmake_minimum_required(VERSION 3.22)
project(ThreadPool)

set(CMAKE_CXX_STANDARD 17)

add_executable(ThreadPool main.cpp
        TaskQueue.cpp
        TaskQueue.h
        ThreadPool.cpp
        ThreadPool.h
        multithread.h
        threadpools.h
        )
