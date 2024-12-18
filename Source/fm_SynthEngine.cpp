#include "fm_SynthEngine.h"

void fm_SynthEngine::reset()
{
    voice.reset();
}

void fm_SynthEngine::noteOn (const int note, const int velocity)
{
    voice.noteOn (note,velocity);
}

void fm_SynthEngine::noteOff(int note [[maybe_unused]] )
{
    voice.noteOff();
}

void fm_SynthEngine::render(juce::AudioBuffer<float>& buffer, int startSample, int endSample)
{
    auto* firstChannel = buffer.getWritePointer(0);
    if (voice.isActive())
    {
        for (auto sample = startSample; sample < endSample; ++sample)
        {
            firstChannel[sample] += voice.render();
        }
    }

    for (int channel = 1; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        std::copy(firstChannel + startSample, firstChannel + endSample, channelData + startSample);
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

void fm_SynthEngine::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessageList)
{
    auto currentSample = 0;

    for (const auto midiMetadata : midiMessageList)
    {
        const auto message = midiMetadata.getMessage();
        const auto messagePosition = static_cast<int>(message.getTimeStamp());

        render(buffer,currentSample,messagePosition);
        currentSample = messagePosition;
        handleMidiMessage(message);
    }
    // render the last bit ?
    /// TODO: Work out what's going on here
    //render(buffer,currentSample,messagePosition);
}//


void fm_SynthEngine::handleMidiMessage (const juce::MidiMessage& message)
{
    if (message.isNoteOn())
    {
        // get note number and velocity
        const auto velocity = message.getVelocity();
        const auto note = message.getNoteNumber();
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
    voice.setADSR (0.1f,0.1f,0.8f,0.2f);
    voice.setSampleRate (sampleRate);
}


float fm_SynthEngine::midiNoteNumberToFrequency(const int midiNoteNumber)
{
    constexpr auto A4_FREQUENCY = 440.f;
    constexpr auto A4_NOTE_NUMBER = 69.f;
    constexpr auto NOTES_IN_AN_OCTAVE = 12.f;
    return A4_FREQUENCY * std::powf(2, (static_cast<float>(midiNoteNumber) - A4_NOTE_NUMBER) / NOTES_IN_AN_OCTAVE);
}