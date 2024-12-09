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

void Granulator::process(float* buffer, size_t numSamples) {
    scheduler->process(buffer, numSamples);
}
