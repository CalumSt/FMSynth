
#ifndef FM_PARAMETERS_H
#define FM_PARAMETERS_H

#include "Synthesizers/caspi_PMAlgorithm.h"
#include "Utilities/caspi_Constants.h"

#include "fm_Version.h"

#include <JuceHeader.h>
#include <atomic>
#include <unordered_map>

constexpr double max_mod_depth = 1.0;
constexpr double max_mod_index = 5.0;
constexpr double max_mod_feedback = 1.0;
constexpr double max_adsr_time    = 1.0;
constexpr double min_sustain_level = 0.001;

/// TODO: Change this to be a float/choice/bool
struct fm_Parameter
{
    const std::string id;
    const std::string name;
    const std::string unit;
    const float min = 0.0;
    const float max = 1.0;
    const float defaultValue = 0.0;
    using OpIndex = CASPI::PM::OpIndex;
    const OpIndex opIndex = OpIndex::None;
    const int versionAdded = FM_VERSION; // version = major * 10000 + minor * 100 + patch
    std::atomic<float>* value = nullptr;


    [[nodiscard]] float getValue() const { return *value; }
};

inline void castParameter (const AudioProcessorValueTreeState& apvts,
    fm_Parameter& destination)
{
    destination.value = apvts.getRawParameterValue (destination.id);
    jassert (destination.value); // parameter does not exist or wrong type
}

extern std::vector<fm_Parameter> parameterList;

struct fm_Parameters
{
    AudioProcessorValueTreeState& apvts;

    explicit fm_Parameters (AudioProcessorValueTreeState& apvtsIn)
        : apvts (apvtsIn)
    {
        for (auto& p : parameterList)
        {
            castParameter (apvts, p);
            parameterMap[p.id] = &p; // Populate the map
        }
    }

    static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        AudioProcessorValueTreeState::ParameterLayout layout;

        for (const auto& p : parameterList)
        {
            layout.add (std::make_unique<juce::AudioParameterFloat> (
                    p.id,
                    p.name,
                    NormalisableRange<float> (p.min, p.max),
                    p.defaultValue,
                    juce::AudioParameterFloatAttributes().withLabel (p.unit)));

        }

        return layout;
    }

    // Reset all parameters to their default values. Note that this doesn't modify the actual
    // value of the parameters, just the apvts. The actual value will be updated in update().
    void reset() const noexcept
    {
        for (const auto& p : parameterList)
        {
            if (auto* param = apvts.getParameter(p.id))
            {
                // Normalize defaultValue to [0, 1] for setValueNotifyingHost
                param->setValueNotifyingHost(p.defaultValue);
            }
        }
    }

    [[nodiscard]] float get(const std::string& id) const noexcept
    {
        if (auto it = parameterMap.find(id); it != parameterMap.end() && it->second->value)
        {
            return it->second->getValue();
        }
        return 0.0f; // Default value if not found
    }

    [[nodiscard]] float get(const std::string& id, int opIndex) const noexcept
    {
        if (opIndex < 6)
        {
            std::string fullId = id;
            switch (opIndex)
            {
                case 0:
                    fullId += "_OpA";
                    break;
                case 1:
                    fullId += "_OpB";
                    break;
                case 2:
                    fullId += "_OpC";
                    break;
                case 3:
                    fullId += "_OpD";
                    break;
                case 4:
                    fullId += "_OpE";
                    break;
                case 5:
                    fullId += "_OpF";
                    break;
                default:
                    break;
            }

            if (auto it = parameterMap.find(fullId); it != parameterMap.end() && it->second->value)
            {
                return it->second->getValue();
            }
        }
        return 0.0f;
    }


    void update() const noexcept
    {
        for (auto& p : parameterList)
        {
            castParameter (apvts, p);
        }

    }

    float sampleRate = CASPI::Constants::DEFAULT_SAMPLE_RATE<float>;

private:
    std::unordered_map<std::string, fm_Parameter*, std::hash<std::string>, std::equal_to<>> parameterMap;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(fm_Parameters)
};

#endif //FM_PARAMETERS_H