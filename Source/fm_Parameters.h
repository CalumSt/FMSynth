
#ifndef FM_PARAMETERS_H
#define FM_PARAMETERS_H

#include "Utilities/caspi_Constants.h"
#include "Synthesizers/caspi_PMAlgorithm.h"

#include <JuceHeader.h>

namespace SynthParamIDs
{
    #define PARAMETER_ID(str) const juce::ParameterID str(#str, 1);
    PARAMETER_ID(carrierAttackTime)
    PARAMETER_ID(carrierDecayTime)
    PARAMETER_ID(carrierSustain)
    PARAMETER_ID(carrierReleaseTime)
    PARAMETER_ID(modulatorAttackTime)
    PARAMETER_ID(modulatorDecayTime)
    PARAMETER_ID(modulatorSustain)
    PARAMETER_ID(modulatorReleaseTime)
    PARAMETER_ID(modDepth)
    PARAMETER_ID(modIndex)
    PARAMETER_ID(modFeedback)
    PARAMETER_ID(outputLevel)
    #undef PARAMETER_ID
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
        castParameter (apvts, juce::ParameterID("carrierAttackTime"), AttackTimeParam_opB);
        castParameter (apvts, juce::ParameterID("carrierDecayTime"), DecayTimeParam_opB);
        castParameter (apvts, juce::ParameterID("carrierSustain"), SustainLevelParam_opB);
        castParameter (apvts, juce::ParameterID("carrierReleaseTime"), ReleaseTimeParam_opB);
        castParameter (apvts, juce::ParameterID("modulatorAttackTime"), AttackTimeParam_opA);
        castParameter (apvts, juce::ParameterID("modulatorDecayTime"), DecayTimeParam_opA);
        castParameter (apvts, juce::ParameterID("modulatorSustain"), SustainLevelParam_opA);
        castParameter (apvts, juce::ParameterID("modulatorReleaseTime"), ReleaseTimeParam_opA);
        castParameter (apvts, juce::ParameterID("modDepth"), modDepthParam_opA);
        castParameter (apvts, juce::ParameterID("modIndex"), modIndexParam_opA);
        castParameter (apvts, juce::ParameterID("modFeedback"), modFeedbackParam_opA);
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

    void prepareToPlay () noexcept
    {

    }

    void updateOperator (const CASPI::PM::OpIndex opIndex) noexcept
    {
        switch (opIndex)
        {
            case CASPI::PM::OpIndex::OpB:
                carrierAttackTime     = AttackTimeParam_opA->get();
                carrierDecayTime      = DecayTimeParam_opA->get();
                carrierSustainLevel   = SustainLevelParam_opA->get() / 100.0f;
                carrierReleaseTime    = ReleaseTimeParam_opA->get();
                break;
            case CASPI::PM::OpIndex::OpA:
                modulatorAttackTime     = AttackTimeParam_opA->get();
                modulatorDecayTime      = DecayTimeParam_opA->get();
                modulatorSustainLevel   = SustainLevelParam_opA->get() / 100.0f;
                modulatorReleaseTime    = ReleaseTimeParam_opA->get();
                break;
            default:
                break;
        }

    }

    void update() noexcept
    {
        carrierAttackTime     = AttackTimeParam_opB->get();
        carrierDecayTime      = DecayTimeParam_opB->get();
        carrierSustainLevel   = SustainLevelParam_opB->get() / 100.0f;
        carrierReleaseTime    = ReleaseTimeParam_opB->get();
        modulatorAttackTime   = AttackTimeParam_opA->get();
        modulatorDecayTime    = DecayTimeParam_opA->get();
        modulatorSustainLevel = SustainLevelParam_opA->get() / 100.0f;
        modulatorReleaseTime  = ReleaseTimeParam_opA->get();

        modulatorDepth    = modDepthParam_opA->get() / 100.0f;
        modulatorIndex    = modIndexParam_opA->get();
        modulatorFeedback = modFeedbackParam_opA->get() / 100.0f;
        outputLevel       = outputLevelParam->get() / 100.0f;
    }

    // *** Plug-in parameters ***

    struct SmoothParameters
    {
        juce::SmoothedValue<float> smoothedValue;
    };

    // *** Operator Parameters ***
    // 6 groups of ADSR, modulation, and waveshaper parameters
    AudioParameterBool*  AdsrEnabled_opA;
    AudioParameterFloat* AttackTimeParam_opA;
    AudioParameterFloat* DecayTimeParam_opA;
    AudioParameterFloat* SustainLevelParam_opA;
    AudioParameterFloat* ReleaseTimeParam_opA;
    AudioParameterBool*  FeedbackEnabled_opA;
    AudioParameterFloat* modDepthParam_opA;
    AudioParameterFloat* modIndexParam_opA;
    AudioParameterFloat* modFeedbackParam_opA;

    AudioParameterBool*  AdsrEnabled_opB;
    AudioParameterFloat* AttackTimeParam_opB;
    AudioParameterFloat* DecayTimeParam_opB;
    AudioParameterFloat* SustainLevelParam_opB;
    AudioParameterFloat* ReleaseTimeParam_opB;
    AudioParameterBool*  FeedbackEnabled_opB;
    AudioParameterFloat* modDepthParam_opB;
    AudioParameterFloat* modIndexParam_opB;
    AudioParameterFloat* modFeedbackParam_opB;

    AudioParameterBool*  AdsrEnabled_opC;
    AudioParameterFloat* AttackTimeParam_opC;
    AudioParameterFloat* DecayTimeParam_opC;
    AudioParameterFloat* SustainLevelParam_opC;
    AudioParameterFloat* ReleaseTimeParam_opC;
    AudioParameterBool*  FeedbackEnabled_opC;
    AudioParameterFloat* modDepthParam_opC;
    AudioParameterFloat* modIndexParam_opC;
    AudioParameterFloat* modFeedbackParam_opC;

    AudioParameterBool*  AdsrEnabled_opD;
    AudioParameterFloat* AttackTimeParam_opD;
    AudioParameterFloat* DecayTimeParam_opD;
    AudioParameterFloat* SustainLevelParam_opD;
    AudioParameterFloat* ReleaseTimeParam_opD;
    AudioParameterBool*  FeedbackEnabled_opD;
    AudioParameterFloat* modDepthParam_opD;
    AudioParameterFloat* modIndexParam_opD;
    AudioParameterFloat* modFeedbackParam_opD;

    AudioParameterBool*  AdsrEnabled_opE;
    AudioParameterFloat* AttackTimeParam_opE;
    AudioParameterFloat* DecayTimeParam_opE;
    AudioParameterFloat* SustainLevelParam_opE;
    AudioParameterFloat* ReleaseTimeParam_opE;
    AudioParameterBool*  FeedbackEnabled_opE;
    AudioParameterFloat* modDepthParam_opE;
    AudioParameterFloat* modIndexParam_opE;
    AudioParameterFloat* modFeedbackParam_opE;

    AudioParameterBool*  AdsrEnabled_opF;
    AudioParameterFloat* AttackTimeParam_opF;
    AudioParameterFloat* DecayTimeParam_opF;
    AudioParameterFloat* SustainLevelParam_opF;
    AudioParameterFloat* ReleaseTimeParam_opF;
    AudioParameterBool*  FeedbackEnabled_opF;
    AudioParameterFloat* modDepthParam_opF;
    AudioParameterFloat* modIndexParam_opF;
    AudioParameterFloat* modFeedbackParam_opF;

    // *** Filter Parameters ***

    // Compressor Parameters ***

    AudioParameterFloat* outputLevelParam;

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