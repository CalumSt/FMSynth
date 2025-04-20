/*
==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/LookAndFeel.h"

#include "GUI/Font.h"
#include "GUI/Components.h"

//==============================================================================

class SynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit SynthAudioProcessorEditor (SynthAudioProcessor&);
    ~SynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthAudioProcessor& audioProcessor;

    ModulatorLookAndFeel style; // Look and Feel

    Header header;

    TooltipWindow tooltip;

    DialArea leftDialArea;

    DrawableRectangle rightDialArea;




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};
