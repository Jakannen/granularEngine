/*
  ==============================================================================

    Granulator.h
    Created: 8 Dec 2024 7:52:01pm
    Author:  Jack

  ==============================================================================
*/

#pragma once
#include <vector>
#include <cmath>
#include <random>
#include <juce_audio_processors/juce_audio_processors.h>

// Forward Declarations
class Grain;
class Scheduler;

class Granulator {
public:
    Granulator(size_t maxGrains, size_t sampleRate);
    void setGrainDensity(float density);
    void setPlaybackRate(float rate);
    void setParameters(const juce::AudioProcessorValueTreeState& parameters);
    void process(float* buffer, size_t numSamples);

private:
    Scheduler* scheduler;
    std::vector<Grain*> grains;
    float sampleRate;
    float grainDensity;
    float playbackRate;
    bool timeFreeze = false; // Time freeze toggle
    float smearAmount = 0.0f; // Controls the randomness in playback rate
};