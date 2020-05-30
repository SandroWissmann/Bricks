cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(bricks)

set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(
    ${SDL2_INCLUDE_DIRS} 
    include 
    include/types 
    include/game_objects
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
src/types/Velocity.cpp
src/types/Width.cpp

src/Game.cpp
src/GetEvent.cpp
src/IsNumber.cpp
src/Level.cpp
src/main.cpp
src/NearlyEqual.cpp
src/PlaySound.cpp
src/Renderer.cpp
src/RGBColor.cpp
src/SDL_RAII.cpp
src/TimeMeasure.cpp
)




string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(bricks 
    ${SDL2_LIBRARIES}
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
    test/types/Velocity_test.cpp
    src/types/Velocity.cpp
    test/types/Width_test.cpp
    src/types/Width.cpp
    
    test/IsNumber_test.cpp
    src/IsNumber.cpp
    test/Level_test.cpp
    src/Level.cpp
    test/NearlyEqual_test.cpp
    src/NearlyEqual.cpp
    test/OperatorDegree_test.cpp
    src/RGBColor.cpp
    test/RGBColor_test.cpp
)

target_link_libraries(test 
    gtest_main 
)

