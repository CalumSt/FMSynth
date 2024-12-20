/**
 * ███╗   ███╗ ██████╗ ██████╗ ██╗   ██╗██╗      █████╗ ████████╗ ██████╗ ██████╗
 * ████╗ ████║██╔═══██╗██╔══██╗██║   ██║██║     ██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗
 * ██╔████╔██║██║   ██║██║  ██║██║   ██║██║     ███████║   ██║   ██║   ██║██████╔╝
 * ██║╚██╔╝██║██║   ██║██║  ██║██║   ██║██║     ██╔══██║   ██║   ██║   ██║██╔══██╗
 * ██║ ╚═╝ ██║╚██████╔╝██████╔╝╚██████╔╝███████╗██║  ██║   ██║   ╚██████╔╝██║  ██║
 * ╚═╝     ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝
 *
 * @file SynthEngine.h
 * @brief Header file for the SynthEngine class.
 * @author [Your Name]
 * @date [Current Date]
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
    void initialiseVoices(int numberOfVoices);
    void reset();
    void noteOn(int note, int velocity);
    void render(juce::AudioBuffer<float>& buffer, int startSample, int endSample);
    void noteOff(int note);
    void allNotesOff();
    void update();
    void setSampleRate (const float _sampleRate) { sampleRate = _sampleRate; }

    /// MIDI - uses JUCE so is isolated here
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessageList);
    void handleMidiMessage (const juce::MidiMessage& message);
    static float midiNoteNumberToFrequency(int midiNoteNumber);
private:
    fm_SynthVoice<float> voice = fm_SynthVoice<float>();
    float sampleRate = 44100.0f;
};



#endif //SYNTHENGINE_H
