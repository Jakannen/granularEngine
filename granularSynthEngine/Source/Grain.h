#pragma once
#include <vector>

class Grain {
public:
    Grain(float sampleRate);

    void activate(float startSample, float duration, float playbackRate, const std::vector<float>& sourceBuffer);
    void process(float* output, size_t numSamples);
    bool isActive() const;

private:
    float sampleRate;
    float startSample;
    float currentSample;
    float duration;
    float playbackRate;
    bool active;

    const std::vector<float>* sourceBuffer; // Pointer to source buffer
};
