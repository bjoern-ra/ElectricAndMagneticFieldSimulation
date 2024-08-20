cmake_minimum_required(VERSION 3.29)
project(ElectricAndMagneticFieldSimulation C)

set(CMAKE_C_STANDARD 11)

add_executable(ElectricAndMagneticFieldSimulation main.c
        electric_field.c
        electric_field.h
        magnetic_field.c
        magnetic_field.h
        flow_field.c
        flow_field.h
)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(ElectricAndMagneticFieldSimulation ${SDL2_LIBRARIES} m)
