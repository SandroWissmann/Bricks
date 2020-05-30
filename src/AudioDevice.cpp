#include "AudioDevice.h"

#include <iostream>

namespace bricks{

    constexpr auto filenameDestroyBrick = "sounds/destroyBrick.wav";
    constexpr auto filenameHitBrick = "sounds/hitBrick.wav";
    constexpr auto filenameHitPlatform = "sounds/hitPlatform.wav";

    AudioDevice::AudioDevice()
    {
        // mAudioDeviceId = SDL_OpenAudioDevice(NULL, 0, &mAudioSpec, NULL, 0);
        // if(mAudioDeviceId == 0) {
        //     throw std::runtime_error("SDL_Open Audio Not Successfull:\n" 
        //      + std::string(SDL_GetError()) + "\n" +
        //     "Device ID:" + std::to_string(mAudioDeviceId) + "\n");
        // }
    }

    AudioDevice::~AudioDevice() noexcept {
        SDL_CloseAudioDevice(mAudioDeviceId);
        if(mIsActive) {
            SDL_FreeWAV(mBuffer);
        }
    }

    void AudioDevice::playSound(const std::string& filename)
    {
        if(mIsActive) {
            std::cout << "close audio device:" << mAudioDeviceId <<'\n';
            SDL_FreeWAV(mBuffer);
        }

        if(SDL_LoadWAV(filename.c_str(), &mAudioSpec, &mBuffer, &mLength) 
            == NULL) {
            std::cerr<< "SLD_LoadWAV not succesfull\n"
             << SDL_GetError() << '\n';
            SDL_FreeWAV(mBuffer);
            return;
        }

        if(!mIsActive) {
            mAudioDeviceId = SDL_OpenAudioDevice(NULL, 0, &mAudioSpec, NULL, 0);
            // add error handling here
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
}