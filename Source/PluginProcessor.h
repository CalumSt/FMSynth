/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
//==============================================================================
class SynthAudioProcessor : public juce::AudioProcessor, public juce::ValueTree::Listener
{
public:
    //==============================================================================
    juce::AudioProcessorValueTreeState parameterTree { *this, nullptr, "Parameters", createParameterLayout() };

    //==============================================================================
    SynthAudioProcessor();
    ~SynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void reset() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    // Synth Parameters
    //juce::AudioParameterFloat* outputLevel;
    //juce::AudioParameterChoice* polyMode;
    //==============================================================================
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    //==============================================================================

    void splitBufferByEvents(juce::AudioBuffer<float>&buffer, juce::MidiBuffer& midiMessages);
    void handleMidi(uint8_t data0, uint8_t data1, uint8_t data2);
    void render(juce::AudioBuffer<float>& buffer, int sampleCount, int bufferOffset);


    //==============================================================================
    std::atomic<bool> parametersChanged { false }; // Use an atomic bool to check for any parameter changes

    void valueTreePropertyChanged(juce::ValueTree&, const juce::Identifier&) override
    {
      parametersChanged.store(true);
    }

    void update();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessor)
};
