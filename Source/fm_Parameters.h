
#ifndef FM_PARAMETERS_H
#define FM_PARAMETERS_H

#include "Utilities/caspi_Constants.h"

#include <JuceHeader.h>

namespace SynthParamIDs
{
    const juce::ParameterID carrierAttackTime { "carrierAttackTime", 1 };
    const juce::ParameterID carrierDecayTime { "carrierDecayTime", 1 };
    const juce::ParameterID carrierSustain { "carrierSustainLevel", 1 };
    const juce::ParameterID carrierReleaseTime { "carrierReleaseTime", 1 };
    const juce::ParameterID modulatorAttackTime { "modulatorAttackTime", 1 };
    const juce::ParameterID modulatorDecayTime { "modulatorDecayTime", 1 };
    const juce::ParameterID modulatorSustain { "modulatorSustain", 1 };
    const juce::ParameterID modulatorReleaseTime { "modulatorReleaseTime", 1 };
    const juce::ParameterID modDepth { "modDepth", 1 };
    const juce::ParameterID modIndex { "modIndex", 1 };
    const juce::ParameterID modFeedback { "modFeedback", 1 };
    const juce::ParameterID outputLevel { "outputLevel", 1 };
}

template<typename T>
inline void castParameter(AudioProcessorValueTreeState& apvts,
                          const juce::ParameterID& id, T& destination)
{
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID())); /// I don't understand the dynamic cast here
    jassert(destination);  // parameter does not exist or wrong type
}

struct fm_Parameters
{
    explicit fm_Parameters (AudioProcessorValueTreeState& apvts)
    {
        // Cast parameters
        castParameter (apvts, juce::ParameterID("carrierAttackTime"), carrierAttackTimeParam);
        castParameter (apvts, juce::ParameterID("carrierDecayTime"), carrierDecayTimeParam);
        castParameter (apvts, juce::ParameterID("carrierSustainLevel"), carrierSustainLevelParam);
        castParameter (apvts, juce::ParameterID("carrierReleaseTime"), carrierReleaseTimeParam);
        castParameter (apvts, juce::ParameterID("modulatorAttackTime"), modulatorAttackTimeParam);
        castParameter (apvts, juce::ParameterID("modulatorDecayTime"), modulatorDecayTimeParam);
        castParameter (apvts, juce::ParameterID("modulatorSustain"), modulatorSustainParam);
        castParameter (apvts, juce::ParameterID("modulatorReleaseTime"), modulatorReleaseTimeParam);
        castParameter (apvts, juce::ParameterID("modDepth"), modDepthParam);
        castParameter (apvts, juce::ParameterID("modIndex"), modIndexParam);
        castParameter (apvts, juce::ParameterID("modFeedback"), modFeedbackParam);
        castParameter (apvts, juce::ParameterID("outputLevel"), outputLevelParam);
    }


    static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        AudioProcessorValueTreeState::ParameterLayout layout;

        layout.add (std::make_unique<juce::AudioParameterFloat> (
            SynthParamIDs::carrierAttackTime,
            "Carrier Attack Time",
            NormalisableRange<float> (0.0f, 1.0f),
            0.02f,
            juce::AudioParameterFloatAttributes().withLabel("sec")));

        layout.add (std::make_unique<juce::AudioParameterFloat> (
            SynthParamIDs::carrierDecayTime,
            "Carrier Decay Time",
            NormalisableRange<float> (0.0f, 1.0f),
            0.0f,
            juce::AudioParameterFloatAttributes().withLabel("sec")));

        layout.add (std::make_unique<juce::AudioParameterFloat> (
            SynthParamIDs::carrierSustain,
            "Carrier Sustain Level",
            NormalisableRange<float> (0.0f, 100.0f),
            80.0f,
            juce::AudioParameterFloatAttributes().withLabel("%")));

        layout.add (std::make_unique<juce::AudioParameterFloat> (
            SynthParamIDs::carrierReleaseTime,
            "Carrier Release Time",
            NormalisableRange<float> (0.0f, 1.0f),
            0.02f,
            juce::AudioParameterFloatAttributes().withLabel("sec")));

        layout.add (std::make_unique<juce::AudioParameterFloat> (
            SynthParamIDs::modulatorAttackTime,
            "Modulator Attack Time",
            NormalisableRange<float> (0.0f, 1.0f),
            0.0f,
            juce::AudioParameterFloatAttributes().withLabel("sec")));

        layout.add (std::make_unique<juce::AudioParameterFloat> (
            SynthParamIDs::modulatorDecayTime,
            "Modulator Decay Time",
            NormalisableRange<float> (0.0f, 1.0f),
            0.0f,
            juce::AudioParameterFloatAttributes().withLabel("sec")));

        layout.add (std::make_unique<juce::AudioParameterFloat> (
            SynthParamIDs::modulatorSustain,
            "Modulator Sustain Level",
            NormalisableRange<float> (0.0f, 100.0f),
            80.0f,
            juce::AudioParameterFloatAttributes().withLabel("%")));

        layout.add (std::make_unique<juce::AudioParameterFloat> (
            SynthParamIDs::modulatorReleaseTime,
            "Modulator Release Time",
            NormalisableRange<float> (0.0f, 1.0f),
            0.0f,
            juce::AudioParameterFloatAttributes().withLabel("sec")));

        layout.add (std::make_unique<juce::AudioParameterFloat> (
            SynthParamIDs::modDepth,
            "Modulator Depth",
            NormalisableRange<float> (0.0f, 100.0f),
            0.0f,
            juce::AudioParameterFloatAttributes().withLabel("%")));

        layout.add (std::make_unique<juce::AudioParameterFloat> (
            SynthParamIDs::modIndex,
            "Modulator Index",
            NormalisableRange<float> (0.01f, 2.0f),
            1.0f,
            juce::AudioParameterFloatAttributes().withLabel("Index")));

        layout.add (std::make_unique<juce::AudioParameterFloat> (
            SynthParamIDs::modFeedback,
            "Modulator Feedback",
            NormalisableRange<float> (0.0f, 100.0f),
            0.0f,
            juce::AudioParameterFloatAttributes().withLabel("%")));

        layout.add (std::make_unique<juce::AudioParameterFloat> (
            SynthParamIDs::outputLevel,
            "Output Level",
            NormalisableRange<float> (0.0f, 100.0f),
            100.0f,
            juce::AudioParameterFloatAttributes().withLabel("%")));

        return layout;
    }

    void reset() noexcept
    {
        carrierAttackTime   = CASPI::Constants::zero<float>;      // 0 - 1
        carrierDecayTime    = CASPI::Constants::zero<float>;      // 0 - 1
        carrierSustainLevel = CASPI::Constants::one<float>;      // 0 - 1
        carrierReleaseTime  = CASPI::Constants::zero<float>;      // 0 - 1

        modulatorAttackTime   = CASPI::Constants::zero<float>;      // 0 - 1
        modulatorDecayTime    = CASPI::Constants::zero<float>;      // 0 - 1
        modulatorSustainLevel = CASPI::Constants::one<float>;      // 0 - 1
        modulatorReleaseTime  = CASPI::Constants::zero<float>;      // 0 - 1

        modulatorDepth    = CASPI::Constants::zero<float>;      // 0 - 1
        modulatorIndex    = CASPI::Constants::zero<float>;      // 0 - 1
        modulatorFeedback = CASPI::Constants::zero<float>;      // 0 - 1

        outputLevel = CASPI::Constants::one<float>;      // 0 - 1
    }
    void update()
    {
        carrierAttackTime     = carrierAttackTimeParam->get();
        carrierDecayTime      = carrierDecayTimeParam->get();
        carrierSustainLevel   = carrierSustainLevelParam->get() / 100.0f;
        carrierReleaseTime    = carrierReleaseTimeParam->get();
        modulatorAttackTime   = modulatorAttackTimeParam->get();
        modulatorDecayTime    = modulatorDecayTimeParam->get();
        modulatorSustainLevel = modulatorSustainParam->get() / 100.0f;
        modulatorReleaseTime  = modulatorReleaseTimeParam->get();

        modulatorDepth    = modDepthParam->get() / 100.0f;
        modulatorIndex    = modIndexParam->get();
        modulatorFeedback = modFeedbackParam->get() / 100.0f;
        outputLevel       = outputLevelParam->get() / 100.0f;
    }
    void randomize() noexcept; /// TODO: Implement me!

    // *** Plug-in parameters ***

    // *** Carrier parameters ***
    AudioParameterFloat* carrierAttackTimeParam;
    AudioParameterFloat* carrierDecayTimeParam;
    AudioParameterFloat* carrierSustainLevelParam;
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

    float carrierAttackTime   = CASPI::Constants::zero<float>;      // 0 - 1
    float carrierDecayTime    = CASPI::Constants::zero<float>;      // 0 - 1
    float carrierSustainLevel = CASPI::Constants::one<float>;      // 0 - 1
    float carrierReleaseTime  = CASPI::Constants::zero<float>;      // 0 - 1

    float modulatorAttackTime   = CASPI::Constants::zero<float>;      // 0 - 1
    float modulatorDecayTime    = CASPI::Constants::zero<float>;      // 0 - 1
    float modulatorSustainLevel = CASPI::Constants::one<float>;      // 0 - 1
    float modulatorReleaseTime  = CASPI::Constants::zero<float>;      // 0 - 1

    float modulatorDepth    = CASPI::Constants::zero<float>;      // 0 - 1
    float modulatorIndex    = CASPI::Constants::one<float>;      // 0.1 - 2
    float modulatorFeedback = CASPI::Constants::zero<float>;      // 0 - 1

    float outputLevel = CASPI::Constants::one<float>;      // 0 - 1

    float sampleRate  = CASPI::Constants::DEFAULT_SAMPLE_RATE<float>;


};

#endif //FM_PARAMETERS_H