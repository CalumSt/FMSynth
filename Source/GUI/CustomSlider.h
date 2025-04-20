/*
  ==============================================================================

    CustomSlider.h
    Created: 5 Mar 2024 9:29:57pm
    Author:  CS Islay

  ==============================================================================
*/

#pragma once

#include "LookAndFeel.h"

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CustomSlider final : public juce::Component, public juce::SettableTooltipClient
{
public:
    explicit CustomSlider();
    ~CustomSlider() override;
    juce::Slider slider;
    juce::String label;
    juce::String unit;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomSlider)
};
