/**
 * ███╗   ███╗ ██████╗ ██████╗ ██╗   ██╗██╗      █████╗ ████████╗ ██████╗ ██████╗
 * ████╗ ████║██╔═══██╗██╔══██╗██║   ██║██║     ██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗
 * ██╔████╔██║██║   ██║██║  ██║██║   ██║██║     ███████║   ██║   ██║   ██║██████╔╝
 * ██║╚██╔╝██║██║   ██║██║  ██║██║   ██║██║     ██╔══██║   ██║   ██║   ██║██╔══██╗
 * ██║ ╚═╝ ██║╚██████╔╝██████╔╝╚██████╔╝███████╗██║  ██║   ██║   ╚██████╔╝██║  ██║
 * ╚═╝     ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝
 *
 * @file fm_SynthEngine.h
 * @brief Header file for the SynthEngine class.
 * @author CS Islay
 *
 * @par Description
 * This header file defines the SynthEngine class, which is responsible for generating audio.
 *
 * @par Usage
 * To use the SynthEngine class, include this header file in your code and create an instance of the SynthEngine class.
 *
 * @par Classes
 * - SynthEngine: The main class for generating audio.
 *
 * @par Functions
 * - reset(): Resets the SynthEngine to its initial state.
 * - noteOn(): Starts playing a note.
 * - render(): Renders the audio.
 * - noteOff(): Stops playing a note.
 * - update(): Updates the SynthEngine's state.
*/

#ifndef SYNTHENGINE_H
#define SYNTHENGINE_H

#include <JuceHeader.h>
#include "fm_Parameters.h"
#include "fm_SynthVoice.h"

class fm_SynthEngine {
public:
    explicit fm_SynthEngine(fm_Parameters& parameters);
    void initialiseVoices();
    void reset();
    void noteOn(int note, int velocity);
    void render(AudioBuffer<float>& buffer, int startSample, int endSample);
    void noteOff(int note);
    void allNotesOff();
    void update();
    void setSampleRate (const float newSampleRate)
    {
        parameters.sampleRate = newSampleRate;
        for (auto & voice : voices) { voice.setSampleRate (newSampleRate); }
    }

    int getNumActiveVoices ();
    float getGainControl ();

    /// MIDI - uses JUCE so is isolated here
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer const& midiMessageList);
    void handleMidiMessage (const juce::MidiMessage& message);

private:
    // holds a pointer to an array of voices
    std::vector<fm_SynthVoice<float>> voices {128};
    int numActiveVoices = 0;
    fm_Parameters& parameters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(fm_SynthEngine)
};



#endif //SYNTHENGINE_H
