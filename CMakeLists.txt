cmake_minimum_required(VERSION 3.29)
project(ElectricAndMagneticFieldSimulation C)

set(CMAKE_C_STANDARD 11)

# Find SDL2 and SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Include directories for SDL2 and SDL2_ttf
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

# Add the executable
add_executable(ElectricAndMagneticFieldSimulation
        main.c
        electric_field.c
        magnetic_field.c
        flow_field.c
)

# Manually link SDL2_ttf if the automatic linking fails
target_link_libraries(ElectricAndMagneticFieldSimulation ${SDL2_LIBRARIES} SDL2_ttf m)
