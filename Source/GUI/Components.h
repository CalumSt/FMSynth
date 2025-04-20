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

class Header : public juce::Component
{
public:
    Header();
    ~Header();
    void paint (juce::Graphics&);
    void resized();
private:
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



#endif //COMPONENTS_H
