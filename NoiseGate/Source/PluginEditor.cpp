/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NoiseGateAudioProcessorEditor::NoiseGateAudioProcessorEditor (NoiseGateAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);
    
    addAndMakeVisible(thresholdSlider);
    thresholdSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    thresholdSlider.setSkewFactor(0.7f);
    thresholdSlider.setRange(0.0f, 1.0f,0.01f);
    thresholdSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 50, 20);
    
    addAndMakeVisible(thresholdLabel);
    thresholdLabel.setText("Threshold", dontSendNotification);
    thresholdLabel.attachToComponent(&thresholdSlider, true);
    
    addAndMakeVisible(alphaSlider);
    alphaSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    alphaSlider.setRange(0.0f,1.0f,0.1f);
    alphaSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 50, 20);
    
    addAndMakeVisible(alphaLabel);
    alphaLabel.setText("Alpha", dontSendNotification);
    alphaLabel.attachToComponent(&alphaSlider, true);

}

NoiseGateAudioProcessorEditor::~NoiseGateAudioProcessorEditor()
{
    //Slider(thresholdSlider);
    //Slider(alphaSlider);
}

//==============================================================================
void NoiseGateAudioProcessorEditor::paint (Graphics& g)
{
    g.setColour(Colour::fromRGB(255, 222, 0));
    g.fillAll();
    g.setColour(Colours::black);
    g.setFont(60.0f);   
    g.drawFittedText("NOISE GATE", getLocalBounds(), Justification::centredLeft, 1);
    g.setColour(Colours::white);
    g.drawFittedText("BLOG POST ", getLocalBounds(), Justification::centredRight, 1);
}

void NoiseGateAudioProcessorEditor::resized()
{
    thresholdSlider.setBounds(150,180,400,40);
    alphaSlider.setBounds(150, 220, 400, 40);
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
