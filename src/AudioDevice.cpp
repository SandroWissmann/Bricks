#include "AudioDevice.h"

#include "SDL_RAII.h"

#include <iostream>

namespace bricks {

constexpr auto filenameDestroyBrick = "sounds/destroyBrick.wav";
constexpr auto filenameHitBrick = "sounds/hitBrick.wav";
constexpr auto filenameHitPlatform = "sounds/hitPlatform.wav";
constexpr auto filenameGameOver = "sounds/gameOver.wav";
constexpr auto filenameNextLevel = "sounds/nextLevel.wav";
constexpr auto filenameLostBall = "sounds/lostBall.wav";
constexpr auto filenameExtraLife = "sounds/extraLife.wav";

AudioDevice::AudioDevice(
    int rate, Uint16 format, int channels, int buffers)
    :mRate{rate}, mFormat{format}, mChannels{channels}, mBuffers{buffers},
    mChunk{nullptr}
{
    SDL_RAII::init();

    Mix_AllocateChannels(1);
}

AudioDevice::~AudioDevice() noexcept
{
    Mix_FreeChunk(mChunk);
    Mix_CloseAudio();
}

void AudioDevice::playSound(const std::string& filename)
{
    if(Mix_OpenAudio(mRate, mFormat, mChannels, mBuffers) != 0) {
        std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << '\n';
    }

    mChunk = Mix_LoadWAV(filename.c_str ());
    if(mChunk == NULL) {
        std::cerr << "Mix_LoadWAV failed: " << Mix_GetError() << '\n';
    }

    Mix_VolumeChunk(mChunk, MIX_MAX_VOLUME); 

    if(Mix_PlayChannel(-1, mChunk, 0) == -1) {
        std::cerr << "Mix_PlayChannel failed: " << Mix_GetError() << '\n';
    }
}

void playDestroyBrick(AudioDevice& audioDevice)
{
    audioDevice.playSound(filenameDestroyBrick);
}

void playHitBrick(AudioDevice& audioDevice)
{
    audioDevice.playSound(filenameHitBrick);
}

void playHitPlatform(AudioDevice& audioDevice)
{
    audioDevice.playSound(filenameHitPlatform);
}

void playGameOver(AudioDevice& audioDevice)
{
    audioDevice.playSound(filenameGameOver);
}

void playNextLevel(AudioDevice& audioDevice)
{
    audioDevice.playSound(filenameNextLevel);
}

void playLostBall(AudioDevice& audioDevice)
{
    audioDevice.playSound(filenameLostBall);
}

void playExtraLife(AudioDevice& audioDevice)
{
    audioDevice.playSound(filenameExtraLife);
}
} // namespace bricks