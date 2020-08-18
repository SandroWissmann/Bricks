cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

# set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-* -fix)

project(bricks)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_mixer_INCLUDE_DIRS} 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/include/game_objects
    ${CMAKE_SOURCE_DIR}/include/types
    ${CMAKE_SOURCE_DIR}/include/utility 
)

add_subdirectory(thirdparty/googletest)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_subdirectory(src)

add_executable(test 
    test/game_objects/Ball_test.cpp
    src/game_objects/Ball.cpp
    test/game_objects/Brick_test.cpp
    src/game_objects/Brick.cpp
    test/game_objects/GameObject_test.cpp
    src/game_objects/GameObject.cpp
    test/game_objects/MoveableGameObject_test.cpp
    src/game_objects/MoveableGameObject.cpp
    test/game_objects/Physics_test.cpp
    src/game_objects/Physics.cpp
    test/game_objects/Platform_test.cpp
    src/game_objects/Platform.cpp

    test/types/Angle_test.cpp
    src/types/Angle.cpp
    test/types/Gravity_test.cpp
    src/types/Gravity.cpp
    test/types/GridHeight_test.cpp
    src/types/GridHeight.cpp
    test/types/GridWidth_test.cpp
    src/types/GridWidth.cpp
    test/types/Height_test.cpp
    src/types/Height.cpp
    test/types/Hitpoints_test.cpp
    src/types/Hitpoints.cpp
    test/types/Point_test.cpp
    src/types/Point.cpp
    src/types/RGBColor.cpp
    test/types/RGBColor_test.cpp
    test/types/Velocity_test.cpp
    src/types/Velocity.cpp
    test/types/Width_test.cpp
    src/types/Width.cpp
    
    test/utility/IsNumber_test.cpp
    src/utility/IsNumber.cpp
    test/utility/NearlyEqual_test.cpp
    src/utility/NearlyEqual.cpp
    test/utility/OperatorDegree_test.cpp

# needs to be added so linker works with level
    src/GameParameter.cpp

    test/Level_test.cpp
    src/Level.cpp
)

target_link_libraries(test 
    gtest_main 
)

