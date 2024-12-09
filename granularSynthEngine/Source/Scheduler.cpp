/*
  ==============================================================================

    Scheduler.cpp
    Created: 8 Dec 2024 7:52:34pm
    Author:  Jack

  ==============================================================================
*/

#include "Scheduler.h"
#include <random>

/**
 * Constructs the Scheduler object.
 * Initializes the grain pool with the specified maximum number of grains,
 * sets the sample rate for timing calculations, and sets initial parameters.
 *
 * @param maxGrains The maximum number of grains allowed to be active at once.
 * @param sampleRate The audio sample rate (e.g., 44100 Hz).
 */
Scheduler::Scheduler(size_t maxGrains, float sampleRate)
    : grainPool(maxGrains, Grain(sampleRate)), activeGrainCount(0), sampleRate(sampleRate) {
}

/**
 * Updates the grain density parameter.
 * This directly affects how frequently new grains are activated.
 *
 * @param density The new grain density value (e.g., grains per second).
 */
void Scheduler::setGrainDensity(float density) {
    grainDensity = density;
}

/**
 * Updates the playback rate for new grains.
 * The playback rate adjusts the speed at which grains read from the source buffer.
 *
 * @param rate The playback rate multiplier (e.g., 1.0 for normal speed).
 */
void Scheduler::setPlaybackRate(float rate) {
    playbackRate = rate;
}


/**
 * Processes the audio buffer by iterating over active grains and mixing their outputs.
 * After processing active grains, it schedules new grains based on grain density.
 *
 * @param buffer Pointer to the audio buffer to which grain output is added.
 * @param numSamples The number of audio samples to process in this block.
 */
void Scheduler::activateNewGrains() {
    // Calculate the number of grains to activate based on density
    size_t grainsToActivate = static_cast<size_t>(grainDensity * sampleRate);

    // Random number generator for grain start positions
    static std::default_random_engine generator;
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

    // Attempt to activate the calculated number of grains
    for (size_t i = 0; i < grainsToActivate && activeGrainCount < grainPool.size(); ++i) {
        for (Grain& grain : grainPool) {
            if (!grain.isActive()) {
                // Randomize start position and activate the grain
                float startSample = distribution(generator) * sampleRate;
                float duration = 0.05f; // Fixed grain duration (e.g., 50ms)
                grain.activate(startSample, duration, playbackRate, sourceBuffer);
                ++activeGrainCount;
                break; // Move to the next grain
            }
        }
    }
}