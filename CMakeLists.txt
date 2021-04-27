cmake_minimum_required(VERSION 3.17)
project(FibonacciHeap)

set(CMAKE_CXX_STANDARD 20)

file(GLOB HEADER_FILES
        include/FibonacciHeap/*.hpp)

file(GLOB SOURCE_FILES
        include/FibonacciHeap/*.inl)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)