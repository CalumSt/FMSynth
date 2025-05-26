//
// Created by calum on 18/04/2025.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "JuceHeader.h"
#include "../PluginProcessor.h"
#include "../fm_Parameters.h"
#include "RotaryKnob.h"
#include "CustomSlider.h"

class PresetUI : public juce::Component
{
public:
    PresetUI();
    ~PresetUI();
    void paint (juce::Graphics&);
    void resized();
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetUI)
};

class Header : public juce::Component
{
public:
    Header();
    ~Header();
    void paint (juce::Graphics&);
    void resized();
private:
    TextButton presetExplorer;
    TextButton saveButton;
    TextButton learnButton;
    TextButton settingsButton;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Header)
};

class DialArea : public juce::Component
{
public:
    explicit DialArea(SynthAudioProcessor &audioProcessor); // Dials need access to the audio processor
    ~DialArea();
    void paint (juce::Graphics&);
    void resized();
private:
    using APVTS = juce::AudioProcessorValueTreeState;
    using SliderAttachment = APVTS::SliderAttachment;
    // GUI components
    CustomSlider modulationDial;
    SliderAttachment modDepthAttachment;

    CustomSlider modIndexDial;
    SliderAttachment modIndexAttachment;

    CustomSlider modFeedbackDial;
    SliderAttachment modFeedbackAttachment;

    CustomSlider tempDial;
    SliderAttachment tempAttachment;

    CustomSlider attackDial;
    SliderAttachment attackAttachment;

    CustomSlider decayDial;
    SliderAttachment decayAttachment;

    CustomSlider sustainDial;
    SliderAttachment sustainAttachment;

    CustomSlider releaseDial;
    SliderAttachment releaseAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DialArea)
};

class AlgorithmMenu : public juce::Component
{
public:
    AlgorithmMenu();
    ~AlgorithmMenu();
    void paint (juce::Graphics&);
    void resized();
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlgorithmMenu)
};

class CustomToggleButton : public juce::ToggleButton
{
public:
    void paintButton (juce::Graphics& g, bool, bool) override
    {
        auto bounds = getLocalBounds().toFloat().reduced(2.0f);
        float cornerRadius = 10.0f;

        g.setColour (juce::Colours::yellow.withAlpha(0.3f));

        g.drawRoundedRectangle(bounds, cornerRadius, 2.0f);

        if (getToggleState())
        {
            auto delta = bounds.getHeight() * 0.1f;
            auto fillBounds = bounds.reduced (delta, delta);
            g.fillRoundedRectangle(fillBounds, cornerRadius);
            g.setColour(juce::Colours::black);
        }

        g.drawText(getButtonText(), getLocalBounds(), juce::Justification::centred, true);
    }
};

class OperatorButtons : public juce::Component
{
public:
    OperatorButtons();
    ~OperatorButtons() override = default;
    void paint (juce::Graphics&) override;
    void resized() override;
private:
    void selectButton(int index);
    const int numberOfOperators = 3;
    std::vector<CustomToggleButton> buttons;
    int currentOperator = 0;
    int buttonHeight = 20;
    int buttonWidth = 20;
    bool isRow = true;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OperatorButtons)
};




#endif 