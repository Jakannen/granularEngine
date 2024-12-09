/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GranularSynthEngineAudioProcessor::GranularSynthEngineAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, "Parameters", createParameterLayout())
#endif
{
    granulator = std::make_unique<Granulator>(128, getSampleRate());
}

GranularSynthEngineAudioProcessor::~GranularSynthEngineAudioProcessor()
{
}

//==============================================================================
const juce::String GranularSynthEngineAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GranularSynthEngineAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GranularSynthEngineAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GranularSynthEngineAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GranularSynthEngineAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GranularSynthEngineAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GranularSynthEngineAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GranularSynthEngineAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GranularSynthEngineAudioProcessor::getProgramName (int index)
{
    return {};
}

void GranularSynthEngineAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GranularSynthEngineAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    granulator = std::make_unique<Granulator>(128, sampleRate);
}

void GranularSynthEngineAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GranularSynthEngineAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GranularSynthEngineAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    granulator->setParameters(parameters);
    auto* leftChannel = buffer.getWritePointer(0);
    granulator->process(leftChannel, buffer.getNumSamples());
}

//==============================================================================
bool GranularSynthEngineAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GranularSynthEngineAudioProcessor::createEditor()
{
    return new GranularSynthEngineAudioProcessorEditor (*this);
}

//==============================================================================
void GranularSynthEngineAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GranularSynthEngineAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GranularSynthEngineAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout GranularSynthEngineAudioProcessor::createParameterLayout() {
    return {
        std::make_unique<juce::AudioParameterFloat>("grainDensity", "Grain Density", 0.0f, 1.0f, 0.5f),
        std::make_unique<juce::AudioParameterFloat>("playbackRate", "Playback Rate", 0.5f, 2.0f, 1.0f)
    };
}