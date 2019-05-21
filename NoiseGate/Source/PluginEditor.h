/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NoiseGateAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    NoiseGateAudioProcessorEditor (NoiseGateAudioProcessor&);
    ~NoiseGateAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void LookAndFeel();
    
    
private:
    Slider thresholdSlider;
    Label thresholdLabel;
    Slider alphaSlider;
    Label alphaLabel;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NoiseGateAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGateAudioProcessorEditor)
};

