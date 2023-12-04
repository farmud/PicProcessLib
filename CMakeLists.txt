cmake_minimum_required(VERSION 3.23)
project(PicProcessLib)

set(CMAKE_CXX_STANDARD 14)



add_executable(prewitt lab7/prewitt.c)
add_executable(sobel lab7/sobel.c)
add_executable(main main.c
        tools/ImagefileHelper.c
        tools/ImagefileHelper.h
        lab1/lab1.c
        lab1/lab1.h
        lab2/lab2.c
        lab2/lab2.h
        lab3/lab3.c
        lab3/lab3.h
        lab4/lab4.c
        lab4/lab4.h
        lab4/lab4.h
        lab5/lab5.c
        lab5/lab5.h
        lab7/lab7.c
        lab7/lab7.h)
