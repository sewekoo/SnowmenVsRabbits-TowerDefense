# https://www.youtube.com/watch?v=a5kUr-u2UNo

cmake_minimum_required(VERSION 3.0.0)
project(cpp-course-project-tower-defense)
set(VERBOSE 1)

include(CTest)
enable_testing()


#add_library(sfml-graphics STATIC IMPORTED)
#set_target_properties(sfml-graphics PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.5.1-macos-clang/lib/libsfml-graphics.dylib" )


add_executable(towerdef src/entrypoint.cpp src/game.cpp src/level.cpp src/tile.cpp src/tower_sniper.cpp src/exitpoint.cpp src/grass.cpp src/main.cpp src/road.cpp src/tower.cpp)
#add_executable(towerdef src/lauri_hello_test.C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.5.1/include) #Same include for all

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.5.1-macos-clang/lib) # Mac
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.5.1/bin) #Windows?
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.5.1/lib) #Linux?

target_link_libraries(towerdef sfml-audio sfml-graphics sfml-network sfml-system sfml-window)
#target_link_libraries(towerdef sfml-graphics sfml-system sfml-window)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_NAME})
include(CPack)
