cmake_minimum_required(VERSION 3.16)
project(diffdrive VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(core STATIC src/core/kinematics.cpp)
target_include_directories(core PUBLIC src/core)

if(NOT CMAKE_CROSSCOMPILING)
    include(FetchContent)
    FetchContent_Declare(
        unity
        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
        GIT_TAG        v2.6.0
    )
    FetchContent_MakeAvailable(unity)

    add_executable(test_kinematics tests/test_kinematics.cpp)
    target_link_libraries(test_kinematics PRIVATE unity core)
    add_test(NAME kinematics COMMAND test_kinematics)
else()
    add_executable(diffdrive.elf src/app/startup.c src/app/main.c)
    target_link_libraries(diffdrive.elf PRIVATE core)
    target_link_options(diffdrive.elf PRIVATE -T${CMAKE_SOURCE_DIR}/src/app/linker/stm32f401.ld -nostartfiles -nostdlib)
endif()
