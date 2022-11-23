// https://www.youtube.com/watch?v=a5kUr-u2UNo

cmake_minimum_required(VERSION 3.0.0)
project(cpp-course-project-repository 0.1.0)

include(CTest)
enable_testing()

add_executable(cpp-course-project-repository src/main.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.5.1/include)
target_link_libraries(cpp-course-project-repository ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.5.1/bin)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_NAME})
include(CPack)