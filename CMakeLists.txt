cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(bricks)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_mixer_INCLUDE_DIRS} 
    include 
    include/game_objects
    include/types
    include/utility 
)

add_subdirectory(thirdparty/googletest)

add_executable(bricks 
    src/game_objects/Ball.cpp
    src/game_objects/Brick.cpp
    src/game_objects/GameObject.cpp
    src/game_objects/MoveableGameObject.cpp
    src/game_objects/Physics.cpp
    src/game_objects/Platform.cpp

    src/types/Angle.cpp
    src/types/Gravity.cpp
    src/types/GridHeight.cpp
    src/types/GridWidth.cpp
    src/types/Height.cpp
    src/types/Hitpoints.cpp
    src/types/Point.cpp
    src/types/RGBColor.cpp
    src/types/Velocity.cpp
    src/types/Width.cpp

    src/utility/IsNumber.cpp
    src/utility/NearlyEqual.cpp
    src/utility/TimeMeasure.cpp

    src/AudioDevice.cpp
    src/Game.cpp
    src/InputHandler.cpp
    src/Level.cpp
    src/main.cpp
    src/Renderer.cpp
    src/SDL_RAII.cpp
)

target_link_libraries(
    bricks 
    SDL2::Main
    SDL2::Mixer
)

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

    test/Level_test.cpp
    src/Level.cpp
)

target_link_libraries(test 
    gtest_main 
)

