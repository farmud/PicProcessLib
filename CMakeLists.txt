cmake_minimum_required(VERSION 3.23)
project(PicProcessLib)

set(CMAKE_CXX_STANDARD 14)

add_executable(GrayProcess lab1/GrayProcess.c)
add_executable(ReverseProcess lab1/ReverseProcess.c)
add_executable(RGBDepartureProcess lab1/RGBDepartureProcess.c)
add_executable(HistogramEqualization lab2/HistogramEqualization.c)
add_executable(MakeHistogram lab2/MakeHistogram.c)
add_executable(avag lab3/avag.c
)
add_executable(mid lab3/mid.c)
add_executable(shrink lab4/shrink.c)
add_executable(translate lab4/translate.c)
add_executable(mirror lab4/mirror.c)
add_executable(revolve lab4/revolve.c)
add_executable(prewitt lab7/prewitt.c)
add_executable(sobel lab7/sobel.c)
add_executable(T lab5/T.c
        lab5/tool/tool.h
        lab5/tool/tool.c)
add_executable(iterate lab5/iterate.c
        lab5/tool/tool.h
        lab5/tool/tool.c)
add_executable(Otsu lab5/Otsu.c
        lab5/tool/tool.h
        lab5/tool/tool.c)
