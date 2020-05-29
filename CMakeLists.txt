cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(bricks)

set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} include include/types)

add_subdirectory(thirdparty/googletest)

add_executable(bricks 
src/types/Angle.cpp
src/types/Gravity.cpp
src/types/GridHeight.cpp
src/types/GridWidth.cpp
src/types/Hitpoints.cpp
src/types/Length.cpp
src/types/MaxPositionX.cpp
src/types/MaxPositionY.cpp
src/types/Point.cpp
src/types/Velocity.cpp
src/types/Width.cpp

src/Ball.cpp
src/Brick.cpp
src/Game.cpp
src/GameObject.cpp
src/GameObjectPhysics.cpp
src/GetEvent.cpp
src/IsNumber.cpp
src/Level.cpp
src/main.cpp
src/MoveableGameObject.cpp
src/NearlyEqual.cpp
src/Platform.cpp
src/Renderer.cpp
src/RGBColor.cpp
src/TimeMeasure.cpp
)




string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(bricks 
    ${SDL2_LIBRARIES}
)

add_executable(test 
    test/types/Angle_test.cpp
    src/types/Angle.cpp
    test/types/Gravity_test.cpp
    src/types/Gravity.cpp
    test/types/GridHeight_test.cpp
    src/types/GridHeight.cpp
    test/types/GridWidth_test.cpp
    src/types/GridWidth.cpp
    test/types/Hitpoints_test.cpp
    src/types/Hitpoints.cpp
    test/types/Length_test.cpp
    src/types/Length.cpp
    test/types/Width_test.cpp
    src/types/Width.cpp
    test/types/MaxPositionX_test.cpp
    src/types/MaxPositionX.cpp
    test/types/MaxPositionY_test.cpp
    src/types/MaxPositionY.cpp
    test/types/Point_test.cpp
    src/types/Point.cpp
    test/types/Velocity_test.cpp
    src/types/Velocity.cpp
    
    test/Ball_test.cpp
    src/Ball.cpp
    test/Brick_test.cpp
    src/Brick.cpp
    test/GameObject_test.cpp
    src/GameObject.cpp
    test/GameObjectPhysics_test.cpp
    src/GameObjectPhysics.cpp
    test/IsNumber_test.cpp
    src/IsNumber.cpp
    test/Level_test.cpp
    src/Level.cpp
    test/MoveableGameObject_test.cpp
    src/MoveableGameObject.cpp
    test/NearlyEqual_test.cpp
    src/NearlyEqual.cpp
    test/OperatorDegree_test.cpp

    test/Platform_test.cpp
    src/Platform.cpp
    src/RGBColor.cpp
    test/RGBColor_test.cpp
)

#    test/GameObjectPhysics_test.cpp
#    src/GameObjectPhysics.cpp


target_link_libraries(test 
    gtest_main 
)

