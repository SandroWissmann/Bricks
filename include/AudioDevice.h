#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <SDL.h>
#include <SDL_mixer.h>

#include <string>

namespace bricks {

class AudioDevice {
public:
    AudioDevice(int rate = 44100, Uint16 format = AUDIO_S16SYS,
        int channels = 2, int buffers = 4096);
    ~AudioDevice() noexcept;

    AudioDevice(const AudioDevice&) = delete;
    AudioDevice(AudioDevice&&) = delete;
    AudioDevice& operator=(const AudioDevice&) = delete;
    AudioDevice& operator=(AudioDevice&&) = delete;

    void playSound(const std::string& filename);

private:
    int mRate;
    Uint16 mFormat;
    int mChannels;
    int mBuffers;

    Mix_Chunk *mChunk;
};

void playDestroyBrick(AudioDevice& audioDevice);
void playHitBrick(AudioDevice& audioDevice);
void playHitPlatform(AudioDevice& audioDevice);
void playGameOver(AudioDevice& audioDevice);
void playNextLevel(AudioDevice& audioDevice);
void playLostBall(AudioDevice& audioDevice);
void playExtraLife(AudioDevice& audioDevice);
void playWinGame(AudioDevice& audioDevice);
} // namespace bricks

#endif