/*
  ==============================================================================

    ModulatorLookAndFeel.cpp
    Created: 4 Mar 2024 10:32:26pm
    Author:  CS Islay

  ==============================================================================
*/

#include "LookAndFeel.h"

ModulatorLookAndFeel::ModulatorLookAndFeel()
{
    setColour(juce::ResizableWindow::backgroundColourId, juce::Colour(BLACK));
    setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(BLACK));
    setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(PALE_ORANGE));
    setColour(juce::Slider::trackColourId, juce::Colour(PALE_ORANGE));
    setColour(juce::Slider::backgroundColourId, juce::Colour(BLACK));
    setColour(juce::Slider::thumbColourId, juce::Colour(PALE_ORANGE));
    setColour(Slider::textBoxTextColourId, juce::Colour(GREY));
}

void ModulatorLookAndFeel::drawLinearSlider (Graphics &g,
    int x, int y, int width, int height,  float sliderPos,
    float minSliderPos, float maxSliderPos, Slider::SliderStyle, Slider &slider)
{
    // Centre the slider bounds using the height

    x = width / 2 - height / 2;

    auto outlineColor = slider.findColour(juce::Slider::rotarySliderFillColourId);

    auto bounds = juce::Rectangle<int>(x, y, height, height).toFloat();

    bounds.reduce(10, 10);

    g.setColour(outlineColor);

    g.drawRoundedRectangle(bounds, 15.0f, 5.0f);

    // draw the slider fill
    auto sliderBounds = bounds;
    
    sliderBounds.reduce (10, 10);

    //const float minHeight = sliderBounds.getHeight() / 10.0f;

    auto fillBounds = sliderBounds;

    auto scaledPos = jmap(sliderPos, static_cast<float>(y), maxSliderPos, 1.0f, 0.0f);

    auto sliderHeight = scaledPos * sliderBounds.getHeight();

    //sliderHeight = sliderHeight < minHeight ? minHeight : sliderHeight;

    fillBounds.setY (sliderBounds.getY() + sliderBounds.getHeight() - sliderHeight);

    fillBounds.setHeight (sliderHeight);

    g.fillRoundedRectangle (fillBounds, 10.0f);
}

void ModulatorLookAndFeel::drawRotarySlider(
    juce::Graphics& g, int x, int y, int width, int /*height*/, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    auto outlineColor = slider.findColour(juce::Slider::rotarySliderOutlineColourId);
    auto fillColor = slider.findColour(juce::Slider::rotarySliderFillColourId);
    auto dialColor = slider.findColour(juce::Slider::thumbColourId);

    auto bounds = juce::Rectangle<int>(x, y, width, width).toFloat()
        .withTrimmedLeft(16.0f).withTrimmedRight(16.0f)
        .withTrimmedTop(0.0f).withTrimmedBottom(8.0f);

    auto radius = bounds.getWidth() / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = 6.0f;
    auto arcRadius = radius - lineW / 2.0f;

    auto arg = toAngle - juce::MathConstants<float>::halfPi;
    auto dialW = 3.0f;
    auto dialRadius = arcRadius - 6.0f;

    auto center = bounds.getCentre();
    auto strokeType = juce::PathStrokeType(lineW, juce::PathStrokeType::curved,
        juce::PathStrokeType::butt);

    juce::Path backgroundArc;
    backgroundArc.addCentredArc(center.x, center.y, arcRadius, arcRadius, 0.0f,
        rotaryStartAngle, rotaryEndAngle, true);
    g.setColour(outlineColor);
    g.strokePath(backgroundArc, strokeType);

    if (slider.isEnabled()) {
        juce::Path valueArc;
        valueArc.addCentredArc(center.x, center.y, arcRadius, arcRadius, 0.0f,
            rotaryStartAngle, toAngle, true);
        g.setColour(fillColor);
        g.strokePath(valueArc, strokeType);
    }

    juce::Point<float> thumbPoint(center.x + dialRadius * std::cos(arg),
        center.y + dialRadius * std::sin(arg));

    g.setColour(dialColor);
    g.drawLine(center.x, center.y, thumbPoint.x, thumbPoint.y, dialW);
    g.fillEllipse(juce::Rectangle<float>(dialW, dialW).withCentre(thumbPoint));
    g.fillEllipse(juce::Rectangle<float>(dialW, dialW).withCentre(center));
}

void ModulatorLookAndFeel::drawLabel (Graphics&, Label&)
{

}
