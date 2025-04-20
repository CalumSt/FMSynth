/*
  ==============================================================================

    CustomSlider.cpp
    Created: 5 Mar 2024 9:29:57pm
    Author:  CS Islay

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomSlider.h"

//==============================================================================
static constexpr int labelHeight = 15;
static constexpr int textBoxHeight = 20;
static constexpr int textBoxWidth = 100;


CustomSlider::CustomSlider()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);

    slider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, textBoxWidth, textBoxHeight);

    slider.setTextValueSuffix(unit);

    addAndMakeVisible(slider);

    //setBounds(0, 0, textBoxWidth, 40);

}

CustomSlider::~CustomSlider()
{
}

void CustomSlider::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);

    g.setFont (BinaryData::Font::getCustomFontRegular());

    auto bounds = getLocalBounds();

    g.drawText(label, juce::Rectangle<int>{ 0, 0, bounds.getWidth(), labelHeight },
        juce::Justification::centred);

    g.drawText(unit, juce::Rectangle<int>{ 0, bounds.getHeight() - labelHeight, bounds.getWidth(), labelHeight }, juce::Justification::centred);
}

void CustomSlider::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto bounds = getLocalBounds();
    slider.setBounds(0, 0, bounds.getWidth(), bounds.getHeight() - labelHeight);
}
