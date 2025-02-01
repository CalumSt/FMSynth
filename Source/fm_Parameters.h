
#ifndef FM_PARAMETERS_H
#define FM_PARAMETERS_H

#include "Utilities/caspi_Constants.h"

#include <JuceHeader.h>

namespace ParameterID
{
    const juce::ParameterID carrierAttackTime { "carrierAttackTime", 1 };
    const juce::ParameterID carrierDecayTime { "carrierDecayTime", 1 };
    const juce::ParameterID carrierSustain { "carrierSustain", 1 };
    const juce::ParameterID carrierReleaseTime { "carrierReleaseTime", 1 };
    const juce::ParameterID modulatorAttackTime { "modulatorAttackTime", 1 };
    const juce::ParameterID modulatorDecayTime { "modulatorDecayTime", 1 };
    const juce::ParameterID modulatorSustain { "modulatorSustain", 1 };
    const juce::ParameterID modulatorReleaseTime { "modulatorReleaseTime", 1 };
    const juce::ParameterID modDepth { "modDepth", 1 };
    const juce::ParameterID modIndex { "modIndex", 1 };
    const juce::ParameterID modFeedback { "modFeedback", 1 };
}

template<typename T>
inline void castParameter(AudioProcessorValueTreeState& apvts,
                          const juce::ParameterID& id, T& destination)
{
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID())); /// I don't understand the dynamic cast here
    jassert(destination);  // parameter does not exist or wrong type
}

template<typename FloatType>
struct fm_Parameters
{
    explicit fm_Parameters (AudioProcessorValueTreeState& apvts)
    {
        // Cast parameters
        castParameter(apvts, juce::ParameterID("drive"), modDepthParam);

    }


    static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        AudioProcessorValueTreeState::ParameterLayout layout;

        return layout;
    }

    void prepareToPlay(float sampleRate) noexcept;
    void reset() noexcept;  /// TODO: Implement me!
    void update() noexcept; /// TODO: Implement me!

    void randomize() noexcept; /// TODO: Implement me!

    // *** Plug-in parameters ***
private:

    // *** Carrier parameters ***
    AudioParameterFloat* carrierAttackTimeParam;
    AudioParameterFloat* carrierDecayTimeParam;
    AudioParameterFloat* carrierSustainParam;
    AudioParameterFloat* carrierReleaseTimeParam;

    // *** Modulator parameters ***
    AudioParameterFloat* modulatorAttackTimeParam;
    AudioParameterFloat* modulatorDecayTimeParam;
    AudioParameterFloat* modulatorSustainParam;
    AudioParameterFloat* modulatorReleaseTimeParam;

    AudioParameterFloat* modDepthParam;
    AudioParameterFloat* modIndexParam;
    AudioParameterFloat* modFeedbackParam;

    // *** Gain parameters ***

    AudioParameterFloat* outputLevelParam;

    // TODO: Add more parameters for new algorithms - how to handle a variable number of modulators?


    // *** Parameter values ***

    FloatType sampleRate = CASPI::Constants::DEFAULT_SAMPLE_RATE<FloatType>;
    FloatType carrierAttackTime   = CASPI::Constants::zero<FloatType>;      // 0 - 1
    FloatType carrierDecayTime    = CASPI::Constants::zero<FloatType>;      // 0 - 1
    FloatType carrierSustainLevel = CASPI::Constants::one<FloatType>;      // 0 - 1
    FloatType carrierReleaseTime  = CASPI::Constants::zero<FloatType>;      // 0 - 1

    FloatType modulatorAttackTime   = CASPI::Constants::zero<FloatType>;      // 0 - 1
    FloatType modulatorDecayTime    = CASPI::Constants::zero<FloatType>;      // 0 - 1
    FloatType modulatorSustainLevel = CASPI::Constants::one<FloatType>;      // 0 - 1
    FloatType modulatorReleaseTime  = CASPI::Constants::zero<FloatType>;      // 0 - 1

    FloatType modulatorDepth    = CASPI::Constants::zero<FloatType>;      // 0 - 1
    FloatType modulatorIndex    = CASPI::Constants::zero<FloatType>;      // 0 - 1
    FloatType modulatorFeedback = CASPI::Constants::zero<FloatType>;      // 0 - 1

    FloatType outputLevel = CASPI::Constants::zero<FloatType>;      // 0 - 1

};

#endif //FM_PARAMETERS_H