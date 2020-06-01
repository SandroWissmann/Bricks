#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <SDL.h>

#include <string>

namespace bricks {

class AudioDevice {
public:
    AudioDevice();
    ~AudioDevice() noexcept;

    AudioDevice(const AudioDevice&) = delete;
    AudioDevice(AudioDevice&&) = delete;
    AudioDevice& operator=(const AudioDevice&) = delete;
    AudioDevice& operator=(AudioDevice&&) = delete;

    void playSound(const std::string& filename);

private:
    SDL_AudioSpec mAudioSpec;
    SDL_AudioDeviceID mAudioDeviceId{0};
    Uint32 mLength;
    Uint8* mBuffer;
    bool mIsActive{false};
};

void playDestroyBrick(AudioDevice& audioDevice);
void playHitBrick(AudioDevice& audioDevice);
void playHitPlatform(AudioDevice& audioDevice);
void playGameOver(AudioDevice& audioDevice);
void playNextLevel(AudioDevice& audioDevice);
void playLostBall(AudioDevice& audioDevice);
void playExtraLife(AudioDevice& audioDevice);
} // namespace bricks

#endif