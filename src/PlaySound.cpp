#include "PlaySound.h"    
    
#include <SDL.h>

#include <iostream>
#include <fstream>
#include <filesystem>

namespace bricks{

void playSoundDestroyBrick()
{
    playSound("sounds/destroyBrickNew.wav");
}

void playSoundHitBrick()
{
    playSound("sounds/hitBrickNew.wav");
}

void playSoundHitPlattform()
{
    playSound("sounds/hitPlattformNew.wav");
}

void playSound(const std::string& filename)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "Could not init SDL:" << SDL_GetError() << '\n';
    }
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    
    if(SDL_LoadWAV(filename.c_str(), &wavSpec, &wavBuffer, &wavLength) == NULL) {
        std::cerr << "Could not load wave:" << SDL_GetError() << '\n';
        return;
    }

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if(deviceId != 1) {
        std::cerr << "Not Successfull:" << SDL_GetError() << std::to_string(deviceId) <<'\n';
    }

    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    if(success == -1) {
        std::cerr << "No Sound:" << SDL_GetError() << '\n';
    }
    SDL_PauseAudioDevice(deviceId, 0);
    SDL_Delay(100);
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}

}