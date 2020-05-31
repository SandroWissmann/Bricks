#include "AudioDevice.h"

#include <iostream>

namespace bricks{

    constexpr auto filenameDestroyBrick = "sounds/destroyBrick.wav";
    constexpr auto filenameHitBrick = "sounds/hitBrick.wav";
    constexpr auto filenameHitPlatform = "sounds/hitPlatform.wav";
    constexpr auto filenameGameOver = "sounds/gameOver.wav";
    constexpr auto filenameNextLevel = "sounds/nextLevel.wav";
    constexpr auto filenameLostBall = "sounds/lostBall.wav";
    constexpr auto filenameExtraLife = "sounds/extraLife.wav";

    AudioDevice::~AudioDevice() noexcept {
        if(mIsActive) {
            SDL_FreeWAV(mBuffer);
            SDL_CloseAudioDevice(mAudioDeviceId);
        }
    }

    void AudioDevice::playSound(const std::string& filename)
    {
        if(mIsActive) {
            SDL_FreeWAV(mBuffer);
        }

        if(SDL_LoadWAV(filename.c_str(), &mAudioSpec, &mBuffer, &mLength) 
            == NULL) {
            std::cerr<< "SLD_LoadWAV not succesfull\n"
             << SDL_GetError() << '\n';
            return;
        }

        if(!mIsActive) {
            mAudioDeviceId = SDL_OpenAudioDevice(NULL, 0, &mAudioSpec, NULL, 0);
            if(mAudioDeviceId == 0) {
                std::cerr << "SDL_Open Audio Not Successfull:\n" 
              << std::string(SDL_GetError()) << "\n" <<
             "Device ID:" << std::to_string(mAudioDeviceId) << "\n";
            }
        }

        if(SDL_QueueAudio(mAudioDeviceId, mBuffer, mLength) == -1) {
            std::cerr << "SDL_QueueAudio not succesfull\n" 
            <<   SDL_GetError() << '\n';
            SDL_FreeWAV(mBuffer);
            return;
        }
        SDL_PauseAudioDevice(mAudioDeviceId, 0);
        mIsActive = true;
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
}