cmake_minimum_required(VERSION 3.22)
project(MySTL)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
add_subdirectory(src)
add_executable(${PROJECT_NAME} main.cpp)
add_executable(learn learn.cpp)
target_link_libraries(${PROJECT_NAME} SRC)