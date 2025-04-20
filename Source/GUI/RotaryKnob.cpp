/*
  ==============================================================================

    RotaryKnob.cpp
    Created: 4 Mar 2024 10:01:25pm
    Author:  CS Islay

  ==============================================================================
*/

#include "RotaryKnob.h"
#include <JuceHeader.h>

#include "Font.h"

//==============================================================================

static constexpr int labelHeight = 15;
static constexpr int textBoxHeight = 20;


RotaryKnob::RotaryKnob()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, textBoxHeight);
    addAndMakeVisible(slider);
    slider.setTextValueSuffix(unit); // Unsure why this doesn't seem to work

}

RotaryKnob::~RotaryKnob() = default;

void RotaryKnob::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.setFont (BinaryData::Font::getCustomFontLight());
    g.setColour (getLookAndFeel().findColour (juce::Slider::textBoxTextColourId));

    auto bounds = getLocalBounds();
    g.drawText (label, juce::Rectangle<int>{ 0, 0, bounds.getWidth(), labelHeight },
                juce::Justification::centred);   // unsure why the text/font here is different?
}

void RotaryKnob::resized()
{
    auto bounds = getLocalBounds();
    slider.setBounds(0, labelHeight, bounds.getWidth(), bounds.getHeight() - labelHeight);
}