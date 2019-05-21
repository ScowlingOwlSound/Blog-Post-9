/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NoiseGateAudioProcessor::NoiseGateAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       .withInput ("Sidechain", AudioChannelSet::stereo(), true)
                       )
#endif
{
    addParameter (threshold = new AudioParameterFloat ("threshold", "Threshold", 0.0f, 1.0f, 0.5f));
    addParameter (alpha     = new AudioParameterFloat ("alpha",     "Alpha",     0.0f, 1.0f, 0.8f));
}

NoiseGateAudioProcessor::~NoiseGateAudioProcessor()
{
}

//==============================================================================
const String NoiseGateAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NoiseGateAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NoiseGateAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NoiseGateAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NoiseGateAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NoiseGateAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NoiseGateAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NoiseGateAudioProcessor::setCurrentProgram (int index)
{
}

const String NoiseGateAudioProcessor::getProgramName (int index)
{
    return {};
}

void NoiseGateAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NoiseGateAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void NoiseGateAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool NoiseGateAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const 
{
   return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet()
    && ! layouts.getMainInputChannelSet().isDisabled();
}


void NoiseGateAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)

    {
        auto mainInputOutput = getBusBuffer (buffer, true, 0);
        auto sideChainInput  = getBusBuffer (buffer, true, 1);
        
        auto alphaCopy = alpha->get();
        auto thresholdCopy = threshold->get();
        
        for (auto j = 0; j <buffer.getNumSamples(); ++j)
        {
            //buffer.clear (j, 0, buffer.getNumSamples());
            //To clear the buffer if req.
            
            auto mixedSamples = 0.0f;
            //Our Sidechain

            for (auto i = 0; i < sideChainInput.getNumChannels(); ++i)
            {
                mixedSamples += sideChainInput.getReadPointer (i) [j];
            }
            
            //To Sum to Mono
            mixedSamples /= static_cast<float>(sideChainInput.getNumChannels());
            
            //For Our Low Pass Filter
            lowPassCoefficient = (alphaCopy * lowPassCoefficient) + ((1.0f - alphaCopy) * mixedSamples);
            
            if (lowPassCoefficient >= thresholdCopy)
                sampleCountDown = (int) getSampleRate();

            for (auto i = 0; i < mainInputOutput.getNumChannels(); ++i)
                *mainInputOutput.getWritePointer (i, j) = sampleCountDown > 0 ? *mainInputOutput.getReadPointer (i, j)
                : 0.0f;
            
            if (sampleCountDown > 0)
                --sampleCountDown;
        }
    }

//==============================================================================
bool NoiseGateAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NoiseGateAudioProcessor::createEditor()
{
    return new NoiseGateAudioProcessorEditor (*this);
}

//==============================================================================
void NoiseGateAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NoiseGateAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NoiseGateAudioProcessor();
}
