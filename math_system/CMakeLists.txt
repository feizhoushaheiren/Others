cmake_minimum_required(VERSION 3.28)
project(math1 C)

set(CMAKE_C_STANDARD 11)

include_directories(lib)

add_executable(math1
        lib/AccountManage.c
        lib/AccountManage.h
        lib/Operation.c
        lib/Operation.h
        lib/Question.c
        lib/Question.h
        lib/Queue.c
        lib/Queue.h
        main.c)
