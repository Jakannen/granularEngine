/*
  ==============================================================================

    Granulator.cpp
    Created: 8 Dec 2024 7:52:01pm
    Author:  Jack

  ==============================================================================
*/

#include "Granulator.h"
#include "Grain.h"
#include "Scheduler.h"

Granulator::Granulator(size_t maxGrains, size_t sampleRate)
    : sampleRate(sampleRate) {
    scheduler = new Scheduler(maxGrains, sampleRate);
}

void Granulator::setGrainDensity(float density) {
    scheduler->setGrainDensity(density);
}

void Granulator::setPlaybackRate(float rate) {
    scheduler->setPlaybackRate(rate);
}

void Granulator::setParameters(const juce::AudioProcessorValueTreeState& parameters) {
    grainDensity = parameters.getRawParameterValue("grainDensity")->load();
    playbackRate = parameters.getRawParameterValue("playbackRate")->load();
    timeFreeze = parameters.getRawParameterValue("timeFreeze")->load();
    smearAmount = parameters.getRawParameterValue("pitchSmear")->load();
    scheduler->setGrainDensity(grainDensity);
    scheduler->setPlaybackRate(playbackRate);
    scheduler->setTimeFreeze(timeFreeze);
    scheduler->setSmearAmount(smearAmount);
}


void Granulator::process(float* buffer, size_t numSamples) {
    scheduler->process(buffer, numSamples);
}
