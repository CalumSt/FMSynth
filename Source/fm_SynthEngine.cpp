#include "fm_SynthEngine.h"

fm_SynthEngine::fm_SynthEngine(fm_Parameters& parameters) : parameters (parameters) { }

void fm_SynthEngine::reset()
{
    for (auto& voice: voices)
    {
        voice.reset();
    }
    parameters.reset();
    numActiveVoices = getNumActiveVoices();

}

void fm_SynthEngine::noteOn (const int note, const int velocity)
{
    // call the voice's noteOn function, using the note num number as the voice index
    const auto voiceIndex = note - 1;
    voices.at(voiceIndex).noteOn (note, velocity);
    ++numActiveVoices;
}

void fm_SynthEngine::noteOff (const int note)
{
    const auto voiceIndex = note - 1;
    voices.at(voiceIndex).noteOff ();
    --numActiveVoices;
}

void fm_SynthEngine::render (juce::AudioBuffer<float>& buffer, const int startSample, const int endSample)
{
    auto* firstChannel = buffer.getWritePointer (0);

    auto const gain = getGainControl();

    for (auto& voice : voices)
    {
        if (voice.isActive())
        {
            for (auto sampleIdx = startSample; sampleIdx < endSample; ++sampleIdx)
            {
                auto sample              = voice.render();
                firstChannel[sampleIdx] += gain * sample;
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
    parameters.update();

    for (auto& voice : voices)
    {
        for (int i = 0; i < std::to_underlying(CASPI::PM::OpIndex::OpG); ++i)
        {
            auto op = static_cast<CASPI::PM::OpIndex>(i);
            voice.setModulation (op, parameters.get("modIndex", i), parameters.get ("modDepth", i), parameters.get ("modFeedback", i));
            voice.setADSR (op, parameters.get("attack", i), parameters.get("decay",i), parameters.get("sustain", i), parameters.get("release",i));

        }
    }
}

void fm_SynthEngine::allNotesOff()
{
    for (auto &voice : voices)
    {
        voice.noteOff();
    }

    getNumActiveVoices();

}

int fm_SynthEngine::getNumActiveVoices ()
{
    numActiveVoices = 0;
    for (auto const& voice : voices)
    {
        if (voice.isActive())
        {
            numActiveVoices++;
        }
    }
    return numActiveVoices;
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
        voice.setSampleRate (parameters.sampleRate);
    }
}

float fm_SynthEngine::getGainControl ()
{
    const auto activeVoices = static_cast<float> (getNumActiveVoices());
    const auto gain = parameters.get("outputLevel") / (0.5f * activeVoices + 0.5f );
    return std::clamp(gain, 0.0f, 1.0f);
}