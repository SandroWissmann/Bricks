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
    test/types/Angle_test.cpp
    src/types/Angle.cpp
    test/types/Gravity_test.cpp
    src/types/Gravity.cpp
    test/types/Height_test.cpp
    src/types/Height.cpp
    test/types/Hitpoints_test.cpp
    src/types/Hitpoints.cpp
    test/types/MaxPositionX_test.cpp
    src/types/MaxPositionX.cpp
    test/types/MaxPositionY_test.cpp
    src/types/MaxPositionY.cpp
    test/types/Point_test.cpp
    src/types/Point.cpp
    test/types/Velocity_test.cpp
    src/types/Velocity.cpp
    test/types/Width_test.cpp
    src/types/Width.cpp
    
    test/Ball_test.cpp
    src/Ball.cpp
    test/Brick_test.cpp
    src/Brick.cpp
    test/GameObject_test.cpp
    src/GameObject.cpp
    test/IsNumber_test.cpp
    src/IsNumber.cpp
    test/MoveableGameObject_test.cpp
    src/MoveableGameObject.cpp
    test/NearlyEqual_test.cpp
    src/NearlyEqual.cpp
    test/OperatorDegree_test.cpp

    test/Platform_test.cpp
    src/Platform.cpp
)

#    test/GameObjectPhysics_test.cpp
#    src/GameObjectPhysics.cpp


target_link_libraries(test 
    gtest_main 
)

