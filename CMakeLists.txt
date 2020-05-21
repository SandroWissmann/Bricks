cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(bricks)

set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_subdirectory(thirdparty/googletest)

add_executable(bricks src/main.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(bricks 
    ${SDL2_LIBRARIES}
)

add_executable(test 
    test/Angle_test.cpp
    src/Angle.cpp
    test/GameObject_test.cpp
    src/GameObject.cpp
    test/GameObjectPhysics_test.cpp
    src/GameObjectPhysics.cpp
    test/NearlyEqual_test.cpp
    src/NearlyEqual.cpp
    test/OperatorDegree_test.cpp
)
target_link_libraries(test 
    gtest_main 
)

