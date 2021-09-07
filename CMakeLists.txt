cmake_minimum_required(VERSION 3.20)

project(os_programming)
set(CMAKE_C_STANDARD 11)
# add the thread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/includes)
file(GLOB srcs "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_SOURCE_DIR}/src/*.c" "${PROJECT_SOURCE_DIR}/*.c")
add_executable(${CMAKE_PROJECT_NAME} ${srcs})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Threads::Threads)