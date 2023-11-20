cmake_minimum_required(VERSION 3.23)
project(PicProcessLib)

set(CMAKE_CXX_STANDARD 14)

add_executable(GrayProcess
        lab1/GrayProcess.c
)
add_executable(ReverseProcess
        lab1/ReverseProcess.c
)
add_executable(RGBDepartureProcess
        lab1/RGBDepartureProcess.c
)
add_executable(HistogramEqualization
        lab2/HistogramEqualization.c
)
add_executable(MakeHistogram
        lab2/MakeHistogram.c
)
add_executable(avag
        lab3/avag.c
)
add_executable(mid
        lab3/mid.c
)


