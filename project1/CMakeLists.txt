cmake_minimum_required(VERSION 3.30)
project(project1)

set(CMAKE_CXX_STANDARD 20)

# Add all source files
add_executable(project1
        main.cpp
        global/global.cpp
        afis/afis.cpp
)
