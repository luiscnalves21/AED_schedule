cmake_minimum_required(VERSION 3.23)
project(Projeto_AED)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projeto_AED
        main.cpp
        include/gestaoh.h src/gestaoh.cpp include/pedido.h src/pedido.cpp include/student.h src/student.cpp include/ucturma.h src/ucturma.cpp src/turmah.cpp include/turmah.h src/slot.cpp include/slot.h src/menu.cpp include/menu.h)
