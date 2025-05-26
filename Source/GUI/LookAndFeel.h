/*
  ==============================================================================

    LookAndFeel.h
    Created: 4 Mar 2024 10:32:26pm
    Author:  CS Islay

  ==============================================================================
*/

#pragma once
#define BLACK 0, 0, 0
#define PALE_ORANGE 225, 206, 90
#define SEAFOAM 40, 255, 177
#define PURPLE 155, 0, 245
#define GREY 181, 181, 181

#include <JuceHeader.h>
#include "Font.h"

class ModulatorLookAndFeel final : public juce::LookAndFeel_V4 {
public:
    ModulatorLookAndFeel();
    void drawLinearSlider(Graphics &, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        Slider::SliderStyle, Slider &) override;

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float rotaryStartAngle,
        float rotaryEndAngle, juce::Slider& slider) override;

    void drawLabel(Graphics&, Label&) override;

    static FontOptions getMainFont() { return FontOptions(BinaryData::Font::getCustomFontRegular()); }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModulatorLookAndFeel)
};