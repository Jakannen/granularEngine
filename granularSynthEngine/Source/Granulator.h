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


// Forward Declarations
class Grain;
class Scheduler;

class Granulator {
public:
    Granulator(size_t maxGrains, size_t sampleRate);
    void setGrainDensity(float density);
    void setPlaybackRate(float rate);
    void process(float* buffer, size_t numSamples);

private:
    Scheduler* scheduler;
    std::vector<Grain*> grains;
    float sampleRate;
};