/*
  ==============================================================================

    RotaryKnob.h
    Created: 4 Mar 2024 10:01:25pm
    Author:  CS Islay

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Font.h"

//==============================================================================
/*
*/
class RotaryKnob : public juce::Component
{
public:
    RotaryKnob();
    ~RotaryKnob() override;
    juce::Slider slider;
    juce::String label;
    juce::String unit;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotaryKnob)
};
