cmake_minimum_required(VERSION 3.30)
project(Assignment2 C)

set(CMAKE_C_STANDARD 99)

add_executable(Assignment2 main.c
        Stack.c
        Stack.h
        parser.c
        parser.h
        eval.c
        eval.h
        expression.c
        expression.h)
