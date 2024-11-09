/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cstdint>

//==============================================================================
SynthAudioProcessor::SynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    parameterTree.state.addListener(this);
}

SynthAudioProcessor::~SynthAudioProcessor()
{
    parameterTree.state.removeListener(this);
}

//==============================================================================
const juce::String SynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    parametersChanged.store(true);
}

void SynthAudioProcessor::releaseResources()
{
}

void SynthAudioProcessor::reset()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only{}
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessageList)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    if (bool expected = true; isNonRealtime() || parametersChanged.compare_exchange_strong(expected,false)) {
        update(); // This function is used to update parameters
    }

    // Process MIDI events - render is held in this too
    splitBufferByEvents(buffer, midiMessageList);
}
//==============================================================================

bool SynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthAudioProcessor::createEditor()
{
    return new SynthAudioProcessorEditor (*this);
}

//==============================================================================
void SynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout SynthAudioProcessor::createParameterLayout() {

    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // Examples left in

    layout.add(std::make_unique<juce::AudioParameterChoice>("polyMode", "Polyphony",
               juce::StringArray{"Mono","Poly"},1));

    layout.add(std::make_unique<juce::AudioParameterFloat>("outputLevel", "Output Level",
               juce::NormalisableRange<float>(-24.0f,6.0f,0.1f),0.0f,
               juce::AudioParameterFloatAttributes().withLabel("dB")));

    return layout;
}

//==============================================================================
void SynthAudioProcessor::splitBufferByEvents(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessageList)
{
    int bufferOffset = 0;

    for (const auto midiMessage : midiMessageList) {
        int samplesThisSegment = midiMessage.samplePosition - bufferOffset;
        // Render the audio that happened before this event if any
        if (samplesThisSegment > 0) {
            render(buffer, samplesThisSegment,bufferOffset);
            bufferOffset += samplesThisSegment;
        }

        if (midiMessage.numBytes <= 3) {
            uint8_t data1 = (midiMessage.numBytes >= 2) ? midiMessage.data[1] : 0;
            uint8_t data2 = (midiMessage.numBytes == 3) ? midiMessage.data[2] : 0;
            handleMidi(midiMessage.data[0],data1,data2);
        }
    }
    // Render audio after the last midi event
    int samplesLastSegment = buffer.getNumSamples() - bufferOffset;
    if (samplesLastSegment > 0) {
        render(buffer, samplesLastSegment,bufferOffset);
    }

    midiMessageList.clear();
    
}

void SynthAudioProcessor::handleMidi(uint8_t data0, uint8_t data1, uint8_t data2)
/*
 * Handles incoming MIDI messages.
 *
 * @param data0 The first byte of the MIDI message (status byte).
 * @param data1 The second byte of the MIDI message (data byte 1).
 * @param data2 The third byte of the MIDI message (data byte 2).
 */
{
    // Determine the type of MIDI message based on the status byte
    // TODO: Switch these to std::byte for byte-oriented data manipulation
    switch (data0 & 0xF0) {
        // Note off message (0x80-0x8F)
        case 0x80:
             ///< Turn off the note
        break;

        // Note on message (0x90-0x9F)
        case 0x90:
        {
            const uint8_t note = data1 & 0x7F; // Extract the note number

            // If velocity is non-zero, turn on the note; otherwise, turn it off
            // Extract the velocity is done implicitly
            if (uint8_t velocity = data2 & 0x7F; velocity > 0) {
                // NOTE ON FUNCTION GOES HERE
            } else {
                // NOTE OFF FUNCTION GOES HERE
            }
            break;
        }
        // Pitch bend message
        case 0xE0:
            // Pitch bend message (0xE0-0xEF)

        break;

        case 0xB0:
            // sustain pedal message

        break;

        default:
            break;
    }
}

void SynthAudioProcessor::render(juce::AudioBuffer<float>& buffer, int sampleCount, int bufferOffset)
{
    // Plugin processing goes here
}

void SynthAudioProcessor::update()
{
    // This method interfaces changes to the parameter tree to the synth engine
    auto sampleRate = float(getSampleRate());


    auto polyMode = parameterTree.getRawParameterValue("polyMode")->load();

    auto outputLevel = juce::Decibels::decibelsToGain(parameterTree.getRawParameterValue("outputLevel")->load());

}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthAudioProcessor();
}
