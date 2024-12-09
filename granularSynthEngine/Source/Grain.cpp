#include "Grain.h"
#include <algorithm> // For std::min

/**
 * Constructor for the Grain class.
 * Initializes the sample rate and sets the grain as inactive.
 *
 * @param sampleRate The sample rate of the audio (typically 44100 Hz).
 */
Grain::Grain(float sampleRate)
    : sampleRate(sampleRate), active(false), sourceBuffer(nullptr) {
}

/**
 * Activates the grain with a specified start sample, duration, playback rate,
 * and a reference to the audio source buffer. Sets the grain as active.
 *
 * @param startSample The starting sample position in the audio source for this grain.
 * @param duration The duration of the grain in seconds (converted to samples).
 * @param playbackRate The rate at which the grain plays back.
 * @param sourceBuffer The audio source buffer (e.g., a sample or delay line).
 */
void Grain::activate(float startSample, float duration, float playbackRate, const std::vector<float>& sourceBuffer) {
    this->startSample = startSample;       // Set the starting position in the source buffer.
    this->duration = duration * sampleRate; // Convert duration from seconds to sample count.
    this->playbackRate = playbackRate;     // Set the playback rate (e.g., 1.0 for normal speed).
    this->sourceBuffer = &sourceBuffer;    // Store the source buffer for playback.
    currentSample = startSample;           // Initialize current sample position.
    active = true;                         // Mark the grain as active.
}

/**
 * Processes the grain by reading audio samples from the source buffer and applying
 * an envelope to the sample before adding it to the output buffer.
 * The grain progresses through its duration and deactivates once it has finished.
 *
 * @param output The output audio buffer that the grain will be mixed into.
 * @param numSamples The number of samples to process in this block.
 */
void Grain::process(float* output, size_t numSamples) {
    // If the grain is not active, exit the function early.
    if (!active || !sourceBuffer) return;

    for (size_t i = 0; i < numSamples; ++i) {
        // If the grain has completed its duration, deactivate it and stop processing.
        if (currentSample >= duration || currentSample >= sourceBuffer->size()) {
            active = false;
            break;
        }

        // Calculate the integer and fractional parts of the sample position
        size_t intSample = static_cast<size_t>(currentSample); // Integer sample index
        float fracSample = currentSample - intSample; // Fractional sample index

        // Linearly interpolate between the current and next sample for smoother playback.
        // This handles non-integer sample positions due to playback rate changes.
        float sample = (*sourceBuffer)[intSample] * (1.0f - fracSample) +
            (*sourceBuffer)[std::min(intSample + 1, sourceBuffer->size() - 1)] * fracSample;

        // Apply an amplitude envelope (simple linear fade-out here).
        // The grain's amplitude gradually decreases over time (duration of the grain).
        float amplitude = 1.0f - (currentSample / duration); // Linear fade-out (could be replaced with more complex envelope functions).

        // Add the grain sample to the output buffer, applying the amplitude envelope.
        output[i] += sample * amplitude;

        // Increment the current sample position by the playback rate, effectively controlling playback speed.
        currentSample += playbackRate;
    }
}

/**
 * Returns whether the grain is still active (i.e., still playing and not finished).
 *
 * @return true if the grain is active; false if the grain has finished playing.
 */
bool Grain::isActive() const {
    return active;
}
