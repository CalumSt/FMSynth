#include "fm_SynthEngine.h"

void fm_SynthEngine::reset()
{
    /// DO SOME STUFF
}

void fm_SynthEngine::noteOn(int note, int velocity)
{

}

void fm_SynthEngine::noteOff(int note)
{

}

void fm_SynthEngine::render(juce::AudioBuffer<float>& buffer, int startSample, int endSample)
{
    float* outputBufferLeft = outputBuffers[0];
    float* outputBufferRight = outputBuffers[1];
}

void fm_SynthEngine::update()
{

}

void fm_SynthEngine::allNotesOff()
{

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
    // render(buffer,currentSample,messagePosition);
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

float fm_SynthEngine::midiNoteNumberToFrequency(const int midiNoteNumber)
{
    constexpr auto A4_FREQUENCY = 440.f;
    constexpr auto A4_NOTE_NUMBER = 69.f;
    constexpr auto NOTES_IN_AN_OCTAVE = 12.f;
    return A4_FREQUENCY * std::powf(2, (static_cast<float>(midiNoteNumber) - A4_NOTE_NUMBER) / NOTES_IN_AN_OCTAVE);
}