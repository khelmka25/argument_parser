cmake_minimum_required(VERSION 3.20)
project(a CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE ENGINE_SOURCE ${CMAKE_SOURCE_DIR}/src/*cc)
add_library(engine STATIC ${ENGINE_SOURCE})
target_include_directories(engine PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    engine
)
target_compile_options(${PROJECT_NAME} 
    PRIVATE 
    -g
    -Wall 
    -Wextra 
    -Wshadow 
    -Wconversion 
    -Wpedantic 
    -Wfloat-equal
    -Wcast-align
    -Wunused
    -Wformat
    -Wuninitialized
    -Wduplicated-cond
    -Wlogical-op
)