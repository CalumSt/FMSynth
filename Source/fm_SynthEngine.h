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

class fm_SynthEngine {
public:
    void reset();
    void noteOn(int note, int velocity);
    void render(juce::AudioBuffer<float>& buffer, int startSample, int endSample);
    void noteOff(int note);
    void allNotesOff();
    void update();

    /// MIDI - uses JUCE so is isolated here
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessageList);
    void handleMidiMessage (const juce::MidiMessage& message);
    static float midiNoteNumberToFrequency(int midiNoteNumber);
private:
    fm_Parameters& parameters;
};



#endif //SYNTHENGINE_H
