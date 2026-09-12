#ifndef SNES_APU_H
#define SNES_APU_H

#include <cstdint>
#include <queue>

class APU {
public:
    static constexpr int SAMPLE_RATE = 32000;
    static constexpr int AUDIO_BUFFER_SIZE = 2048;

    APU();
    ~APU();

    // Initialize APU
    void init();

    // Generate audio samples
    void generateSamples(int count);

    // Get audio buffer
    const int16_t* getAudioBuffer() const;

    // Get number of available samples
    int getAvailableSamples() const;

    // Reset APU
    void reset();

    // APU cycle step
    void step();

private:
    std::queue<int16_t> audioBuffer;
    uint8_t voiceCounter;

    // Voice processing
    void processVoices();
    void mixAudio();
};

#endif // SNES_APU_H
