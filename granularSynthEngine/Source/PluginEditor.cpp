/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GranularSynthEngineAudioProcessorEditor::GranularSynthEngineAudioProcessorEditor (GranularSynthEngineAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(grainDensitySlider);
    addAndMakeVisible(playbackRateSlider);
    addAndMakeVisible(pitchSmearSlider);
    addAndMakeVisible(timeFreezeButton);

    grainDensityAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "grainDensity", grainDensitySlider);
    playbackRateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "playbackRate", playbackRateSlider);
    pitchSmearAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "pitchSmear", pitchSmearSlider);
    timeFreezeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        audioProcessor.parameters, "timeFreeze", timeFreezeButton);

    setSize (400, 300);
}

GranularSynthEngineAudioProcessorEditor::~GranularSynthEngineAudioProcessorEditor()
{
}

//==============================================================================
void GranularSynthEngineAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void GranularSynthEngineAudioProcessorEditor::resized()
{
    grainDensitySlider.setBounds(50, 50, getWidth() - 100, 20);
    playbackRateSlider.setBounds(50, 100, getWidth() - 100, 20);
    pitchSmearSlider.setBounds(50, 150, getWidth() - 100, 30);
    timeFreezeButton.setBounds(50, 200, getWidth() - 100, 30);
}
