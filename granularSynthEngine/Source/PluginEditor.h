/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <juce_gui_extra/juce_gui_extra.h>

//==============================================================================
/**
*/
class GranularSynthEngineAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    GranularSynthEngineAudioProcessorEditor (GranularSynthEngineAudioProcessor&);
    ~GranularSynthEngineAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GranularSynthEngineAudioProcessor& audioProcessor;

    juce::Slider grainDensitySlider;
    juce::Slider playbackRateSlider;
    juce::Slider pitchSmearSlider;
    juce::ToggleButton timeFreezeButton;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> grainDensityAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> playbackRateAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pitchSmearAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> timeFreezeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularSynthEngineAudioProcessorEditor)
};
