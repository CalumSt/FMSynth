//
// Created by calum on 18/04/2025.
//

#include "Components.h"


Header::Header()
{
    Component::setVisible (true);
}

Header::~Header()
{

}

void Header::paint (juce::Graphics& g)
{

}

void Header::resized()
{

}

DialArea::DialArea (SynthAudioProcessor& audioProcessor)
    : modDepthAttachment (audioProcessor.parameterTree, SynthParamIDs::modDepth.getParamID(), modulationDial.slider),
      modIndexAttachment (audioProcessor.parameterTree, SynthParamIDs::modIndex.getParamID(), modIndexDial.slider),
      modFeedbackAttachment (audioProcessor.parameterTree, SynthParamIDs::modFeedback.getParamID(), modFeedbackDial.slider),
      tempAttachment(audioProcessor.parameterTree, SynthParamIDs::outputLevel.getParamID(), tempDial.slider),
      attackAttachment(audioProcessor.parameterTree, SynthParamIDs::modulatorAttackTime.getParamID(), attackDial.slider),
      decayAttachment(audioProcessor.parameterTree, SynthParamIDs::modulatorDecayTime.getParamID(), decayDial.slider),
      sustainAttachment(audioProcessor.parameterTree, SynthParamIDs::modulatorSustain.getParamID(), sustainDial.slider),
      releaseAttachment(audioProcessor.parameterTree, SynthParamIDs::modulatorReleaseTime.getParamID(), releaseDial.slider)
{
    Component::setVisible (true);

    modulationDial.label = "Mod Depth";
    modulationDial.unit  = "%";
    modulationDial.setTooltip ("Modulation Depth");
    addAndMakeVisible (modulationDial);

    modIndexDial.label = "Mod Index";
    modIndexDial.unit  = "%";
    modIndexDial.setTooltip ("Modulation Index");
    addAndMakeVisible (modIndexDial);

    modFeedbackDial.label = "Mod Feedback";
    modFeedbackDial.unit  = "%";
    modFeedbackDial.setTooltip ("Modulation Feedback");
    addAndMakeVisible (modFeedbackDial);

    tempDial.label = "Output";
    tempDial.unit  = "%";
    tempDial.setTooltip ("Output Level");
    addAndMakeVisible (tempDial);

    attackDial.label = "Attack";
    attackDial.unit  = "s";
    attackDial.setTooltip ("Attack Time");
    addAndMakeVisible (attackDial);

    decayDial.label = "Decay";
    decayDial.unit  = "s";
    decayDial.setTooltip ("Decay Time");
    addAndMakeVisible (decayDial);

    sustainDial.label = "Sustain";
    sustainDial.setTooltip ("Sustain Level");
    addAndMakeVisible (sustainDial);

    releaseDial.label = "Release";
    releaseDial.setTooltip ("Release Time");
    addAndMakeVisible (releaseDial);


}

DialArea::~DialArea()
{

}

void DialArea::paint (juce::Graphics& g)
{

}

void DialArea::resized()
{

    const auto area = getLocalBounds();

    Grid grid;

    using Track = juce::Grid::TrackInfo;

    using Fr = juce::Grid::Fr;

    grid.templateColumns = { Track { Fr { 1 } }, Track { Fr { 1 } }, Track { Fr { 1 } }, Track { Fr { 1 } } };

    grid.templateRows = { Track { Fr { 1 } }, Track { Fr { 1 } } };

    grid.items = { GridItem { modulationDial },  GridItem { modIndexDial }, GridItem { modFeedbackDial }, GridItem { tempDial },
                   GridItem { attackDial }, GridItem { decayDial }, GridItem { sustainDial }, GridItem { releaseDial } };

    grid.performLayout (area);
}