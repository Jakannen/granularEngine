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
    : sourceBuffer(nullptr), grainPool(maxGrains, Grain(sampleRate)),
    activeGrainCount(0), sampleRate(sampleRate), grainDensity(0.5f), playbackRate(1.0f) {
}

/**
 * Sets the shared audio source buffer for the Scheduler.
 *
 * @param buffer The audio source buffer containing sound data.
 */
void Scheduler::setSourceBuffer(const std::vector<float>& buffer) {
    sourceBuffer = &buffer;
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
 * Processes audio by mixing active grains into the output buffer
 * and scheduling new grains based on current parameters.
 *
 * @param buffer Pointer to the output audio buffer.
 * @param numSamples The number of samples to process.
 */
void Scheduler::process(float* buffer, size_t numSamples) {
    // Clear the output buffer
    std::fill(buffer, buffer + numSamples, 0.0f);

    // Process active grains
    for (Grain& grain : grainPool) {
        if (grain.isActive()) {
            grain.process(buffer, numSamples);
        }
    }

    // Activate new grains
    activateNewGrains();
}

/**
 * Processes the audio buffer by iterating over active grains and mixing their outputs.
 * After processing active grains, it schedules new grains based on grain density.
 *
 * @param buffer Pointer to the audio buffer to which grain output is added.
 * @param numSamples The number of audio samples to process in this block.
 */
void Scheduler::activateNewGrains() {
    if (timeFreeze) return; // Stop activating new grains when freeze is enabled

    // Calculate the number of grains to activate based on density
    size_t grainsToActivate = static_cast<size_t>(grainDensity * sampleRate);
    // Attempt to activate the calculated number of grains
    for (size_t i = 0; i < grainsToActivate && activeGrainCount < grainPool.size(); ++i) {
        for (Grain& grain : grainPool) {
            if (!grain.isActive()) {
                // Randomize start position and activate the grain
                float startSample = static_cast<float>(std::rand()) / RAND_MAX * sourceBuffer->size();
                float duration = 0.05f; // Fixed grain duration (e.g., 50ms)
                // Apply pitch smearing
                float randomSmear = 1.0f + (static_cast<float>(std::rand()) / RAND_MAX - 0.5f) * smearAmount;

                // Activate the grain with parameters
                grain.activate(startSample, duration, playbackRate * randomSmear, *sourceBuffer);
                ++activeGrainCount;
                break; // Move to the next grain
            }
        }
    }
}

void Scheduler::setTimeFreeze(bool shouldFreeze)
{
    timeFreeze = shouldFreeze;
}

void Scheduler::setSmearAmount(float amount) {
    smearAmount = amount;
}
