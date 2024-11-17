
#ifndef FM_PARAMETERS_H
#define FM_PARAMETERS_H

#include <JuceHeader.h>

namespace ParameterID
{
    const juce::ParameterID width { "width", 1 };
    const juce::ParameterID drive { "drive", 1 };
    const juce::ParameterID octave { "octave", 1 };
    const juce::ParameterID tuning { "tuning", 1 };
    const juce::ParameterID glideTime { "glideTime", 1 };
}

template<typename T>
inline void castParameter(juce::AudioProcessorValueTreeState& apvts,
                          const juce::ParameterID& id, T& destination)
{
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID())); /// I don't understand the dynamic cast here
    jassert(destination);  // parameter does not exist or wrong type
}

struct fm_Parameters
{
    explicit fm_Parameters (juce::AudioProcessorValueTreeState& apvts)
    {
        // Cast parameters
        castParameter(apvts, juce::ParameterID("drive"), driveParam);

    }


    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    void prepareToPlay(float sampleRate) noexcept;
    void reset() noexcept;  /// TODO: Implement me!
    void update() noexcept; /// TODO: Implement me!

    // *** Plug-in parameters ***

    juce::AudioParameterFloat* driveParam;

    // *** Parameter values ***

    float sampleRate = 44100.0f;
    float drive      = 0.0f;      // 0 - 1

    // *** MIDI CC ***

    float pitchBend = 0.0f;

    // *** Derived values ***

    float pitchModulation = 0.0f;

};

#endif //FM_PARAMETERS_H