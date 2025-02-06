cmake_minimum_required(VERSION 3.0)
project(icm20948_linux C)

set(CMAKE_C_STANDARD 11)


add_executable(icm20948_linux main.c icm20948.c)

target_link_libraries(icm20948_linux m)
