#pragma once
#include <vector>
#include "Grain.h"

/**
 * The Scheduler class manages grain activation, deactivation, and scheduling.
 * It holds a shared source buffer and assigns segments of the buffer to grains for playback.
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
     * Sets the shared audio source buffer.
     *
     * @param buffer The audio source buffer containing the data for grains to process.
     */
    void setSourceBuffer(const std::vector<float>& buffer);

    /**
     * Sets the grain density, determining how many grains are activated per second.
     *
     * @param density The grain density, typically a value between 0.0 and 1.0.
     */
    void setGrainDensity(float density);

    /**
     * Sets the playback rate, adjusting the speed at which grains play.
     *
     * @param rate The playback rate multiplier, where 1.0 is normal speed.
     */
    void setPlaybackRate(float rate);

    /**
     * Processes audio output by iterating over active grains, mixing their output, and
     * activating new grains as needed.
     *
     * @param buffer Pointer to the audio buffer to store the mixed grain output.
     * @param numSamples The number of audio samples to process in this block.
     */
    void process(float* buffer, size_t numSamples);

private:
    const std::vector<float>* sourceBuffer; ///< Shared audio source buffer.
    std::vector<Grain> grainPool;           ///< Pool of reusable grains.
    size_t activeGrainCount;                ///< Current number of active grains.
    float sampleRate;                       ///< Audio sample rate (e.g., 44100 Hz).
    float grainDensity;                     ///< Number of grains activated per second.
    float playbackRate;                     ///< Playback speed multiplier.

    /**
     * Activates new grains based on the grain density and playback parameters.
     */
    void activateNewGrains();
};
