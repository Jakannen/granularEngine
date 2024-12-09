/*
  ==============================================================================

    Scheduler.h
    Created: 8 Dec 2024 7:52:34pm
    Author:  Jack

  ==============================================================================
*/

#pragma once
#include <vector>
#include "Grain.h"

/**
 * The Scheduler class manages the activation, deactivation, and processing of grains
 * in the granular synthesizer. It schedules grains based on user-defined parameters
 * such as grain density and playback rate and ensures efficient audio processing.
 */

class Scheduler {
public:
    /**
     * Constructor for the Scheduler class.
     *
     * @param maxGrains The maximum number of grains that can be active at any time.
     * @param sampleRate The audio sample rate (e.g., 44100 Hz).
     */
    Scheduler(size_t maxGrains, float sampleRate);

    /**
     * Sets the grain density, which determines how many grains are activated per second.
     *
     * @param density The grain density, typically a value between 0.0 and 1.0.
     */
    void setGrainDensity(float density);

    /**
     * Sets the playback rate, which adjusts the speed at which grains play back their source.
     *
     * @param rate The playback rate multiplier, where 1.0 is the normal speed.
     */
    void setPlaybackRate(float rate);

    /**
     * Processes audio output by iterating over active grains, mixing their output, and
     * activating new grains based on the current grain density and playback parameters.
     *
     * @param buffer Pointer to the audio buffer to store the mixed grain output.
     * @param numSamples The number of audio samples to process in this block.
     */
    void process(float* buffer, size_t numSamples);

private:
    std::vector<Grain> grainPool;
    size_t activeGrainCount;
    float sampleRate;
    float grainDensity;
    float playbackRate;

    /**
     * Activates new grains based on the current grain density and playback rate.
     * If the maximum number of active grains is reached, no additional grains are activated.
     */
    void activateNewGrains();
};
