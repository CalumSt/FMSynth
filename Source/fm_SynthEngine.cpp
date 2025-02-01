#include "fm_SynthEngine.h"

fm_SynthEngine::fm_SynthEngine(fm_Parameters<float>& parameters) : parameters (parameters) { }

void fm_SynthEngine::reset()
{
    for (auto& voice: voices)
    {
        voice.reset();
    }

}

void fm_SynthEngine::noteOn (const int note, const int velocity)
{
    // call the voice's noteOn function, using the note num number as the voice index
    const auto voiceIndex = note - 1;
    voices.at(voiceIndex).noteOn (note, velocity);
}

void fm_SynthEngine::noteOff (const int note)
{
    const auto voiceIndex = note - 1;
    voices.at(voiceIndex).noteOff ();
}

void fm_SynthEngine::render (juce::AudioBuffer<float>& buffer, const int startSample, const int endSample)
{
    auto* firstChannel = buffer.getWritePointer (0);

    for (auto& voice : voices)
    {
        if (voice.isActive())
        {
            for (auto sample = startSample; sample < endSample; ++sample)
            {
                firstChannel[sample] += voice.render();
            }
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
    for (auto &voice : voices)
    {
        voice.noteOff();
    }

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

void fm_SynthEngine::initialiseVoices ()
{

    for (auto& voice : voices)
    {
        voice.setADSR (0.01f, 0.1f, 0.8f, 0.2f);
        voice.setSampleRate (sampleRate);
    }
}