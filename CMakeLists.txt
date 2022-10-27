cmake_minimum_required(VERSION 3.23)
project(Projeto_AED)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projeto_AED
        main.cpp
        student.h student.cpp ucturma.h ucturma.cpp turmah.cpp turmah.h slot.cpp slot.h)
