#include "fm_SynthEngine.h"

void fm_SynthEngine::reset()
{
    voice.reset();
}

void fm_SynthEngine::noteOn (const int note, const int velocity)
{
    voice.noteOn (note, velocity);
}

void fm_SynthEngine::noteOff (int note [[maybe_unused]])
{
    voice.noteOff();
}

void fm_SynthEngine::render (juce::AudioBuffer<float>& buffer, int startSample, int endSample)
{
    auto* firstChannel = buffer.getWritePointer (0);
    if (voice.isActive())
    {
        for (auto sample = startSample; sample < endSample; ++sample)
        {
            firstChannel[sample] += voice.render();
        }
    }

    for (int channel = 1; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        std::copy (firstChannel + startSample, firstChannel + endSample, channelData + startSample);
    }
}

void fm_SynthEngine::update()
{
    // Currently empty, but will give new parameters in future
}

void fm_SynthEngine::allNotesOff()
{
    voice.noteOff();
}

void fm_SynthEngine::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer const& midiMessageList)
{
    auto currentSample = 0;

    for (const auto midiMetadata : midiMessageList)
    {
        const auto message         = midiMetadata.getMessage();
        const auto messagePosition = static_cast<int> (message.getTimeStamp());

        handleMidiMessage (message);
        render (buffer, currentSample, messagePosition);
        currentSample = messagePosition;
    }
    render (buffer, currentSample, buffer.getNumSamples());
}

void fm_SynthEngine::handleMidiMessage (const juce::MidiMessage& message)
{
    if (message.isNoteOn())
    {
        // get note number and velocity
        const auto velocity = message.getVelocity();
        const auto note     = message.getNoteNumber();
        noteOn (note, velocity); // Assume our synth engine has this function
    }
    else if (message.isNoteOff())
    {
        const auto note = message.getNoteNumber();
        noteOff (note);
    }
    else if (message.isAllNotesOff())
    {
        allNotesOff();
    }
    else if (message.isSustainPedalOn())
    {
        // Stub
    }
    else if (message.isSustainPedalOff())
    {
        // Stub
    }
    else if (message.isPitchWheel())
    {
        // Stub
    }
}

void fm_SynthEngine::initialiseVoices (int numberOfVoices [[maybe_unused]])
{
    voice.setADSR (0.01f, 0.1f, 0.8f, 0.2f);
    voice.setSampleRate (sampleRate);
}