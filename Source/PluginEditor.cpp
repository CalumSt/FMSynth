/*
==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
constexpr int FIXED_HEIGHT = 400;
constexpr int FIXED_WIDTH = 900;
//==============================================================================
SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), leftDialArea(p)
{
    juce::LookAndFeel::setDefaultLookAndFeel (&style);

    setSize (FIXED_WIDTH, FIXED_HEIGHT);

    addAndMakeVisible (header);

    addAndMakeVisible (tooltip);

    addAndMakeVisible (leftDialArea);

    addAndMakeVisible (testArea);
}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
= default;

//==============================================================================
void SynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
    g.setFont (BinaryData::Font::getCustomFontRegular());
    g.setColour (juce::Colours::yellow);

    //header.paint(g);

    g.setColour (juce::Colours::red);

    g.setColour (juce::Colours::blue);
    leftDialArea.paint(g);

    g.setColour (juce::Colours::green);
    testArea.paint(g);

    g.setColour (juce::Colours::grey);


}

void SynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor...

    auto area = getLocalBounds();

    header.setBounds(area.removeFromTop (FIXED_HEIGHT / 10));

    tooltip.setBounds(area.removeFromBottom (FIXED_HEIGHT / 10));

    leftDialArea.setBounds(area.removeFromLeft (FIXED_WIDTH / 2));

    testArea.setBounds(area.removeFromRight (FIXED_WIDTH / 2));

}
