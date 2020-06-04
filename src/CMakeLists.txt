add_executable(bricks 
    game_objects/Ball.cpp
    game_objects/Brick.cpp
    game_objects/GameObject.cpp
    game_objects/MoveableGameObject.cpp
    game_objects/Physics.cpp
    game_objects/Platform.cpp

    types/Angle.cpp
    types/Gravity.cpp
    types/GridHeight.cpp
    types/GridWidth.cpp
    types/Height.cpp
    types/Hitpoints.cpp
    types/Point.cpp
    types/RGBColor.cpp
    types/Velocity.cpp
    types/Width.cpp

    utility/IsNumber.cpp
    utility/NearlyEqual.cpp
    utility/TimeMeasure.cpp

    AudioDevice.cpp
    Game.cpp
    GameParameter.cpp
    InputHandler.cpp
    Level.cpp
    main.cpp
    Renderer.cpp
    SDL_RAII.cpp
)

target_link_libraries(
    bricks 
    SDL2::Main
    SDL2::Mixer
)