//
// Created by calum on 08/06/2025.
//
#include <atomic>

#include "fm_Parameters.h"
using OpIndex = CASPI::PM::OpIndex;
/// TODO: Add other global params (algorithm, etc)
std::vector<fm_Parameter> parameterList =
    {
        // Operator A
        { "attack_OpA", "OpA Attack Time", "s", 0.0f, max_adsr_time, 0.02f, OpIndex::OpA, 100 },
        { "decay_OpA", "OpA Decay Time", "s", 0.0f, max_adsr_time, 0.0f, OpIndex::OpA, 100 },
        { "sustain_OpA", "OpA Sustain Level", "", min_sustain_level, 1.0f, 0.8f, OpIndex::OpA, 100 },
        { "release_OpA", "OpA Release Time", "s", 0.0f, max_adsr_time, 0.02f, OpIndex::OpA, 100 },
        { "adsrEnabled_OpA", "OpA ADSR Enabled", "", 0.0f, 1.0f, 1.0f, OpIndex::OpA, 100 },
        { "modDepth_OpA", "OpA Modulation Depth", "", 0.0f, max_mod_depth, 0.0f, OpIndex::OpA, 100 },
        { "modIndex_OpA", "OpA Modulation Index", "", 0.0f, max_mod_index, 0.0f, OpIndex::OpA, 100 },
        { "modFeedbackEnabled_OpA", "OpA Mod Feedback Enabled", "", 0.0f, 1.0f, 0.0f, OpIndex::OpA, 100 },
        { "modFeedback_OpA", "OpA Modulation Feedback", "", 0.0f, max_mod_feedback, 0.0f, OpIndex::OpA, 100 },

        // Operator B
        { "attack_OpB", "OpB Attack Time", "s", 0.0f, max_adsr_time, 0.02f, OpIndex::OpB, 100 },
        { "decay_OpB", "OpB Decay Time", "s", 0.0f, max_adsr_time, 0.0f, OpIndex::OpB, 100 },
        { "sustain_OpB", "OpB Sustain Level", "", min_sustain_level, 1.0f, 0.8f, OpIndex::OpB, 100 },
        { "release_OpB", "OpB Release Time", "s", 0.0f, max_adsr_time, 0.02f, OpIndex::OpB, 100 },
        { "adsrEnabled_OpB", "OpB ADSR Enabled", "", 0.0f, 1.0f, 1.0f, OpIndex::OpB, 100 },
        { "modDepth_OpB", "OpB Modulation Depth", "", 0.0f, max_mod_depth, 0.0f, OpIndex::OpB, 100 },
        { "modIndex_OpB", "OpB Modulation Index", "", 0.0f, max_mod_index, 0.0f, OpIndex::OpB, 100 },
        { "modFeedbackEnabled_OpB", "OpB Mod Feedback Enabled", "", 0.0f, 1.0f, 0.0f, OpIndex::OpD, 100 },
        { "modFeedback_OpB", "OpB Modulation Feedback", "", 0.0f, max_mod_feedback, 0.0f, OpIndex::OpB, 100 },

            // Operator C
        { "attack_OpC", "OpC Attack Time", "s", 0.0f, max_adsr_time, 0.02f, OpIndex::OpC, 100 },
        { "decay_OpC", "OpC Decay Time", "s", 0.0f, max_adsr_time, 0.0f, OpIndex::OpC, 100 },
        { "sustain_OpC", "OpC Sustain Level", "", min_sustain_level, 1.0f, 0.8f, OpIndex::OpC, 100 },
        { "release_OpC", "OpC Release Time", "s", 0.0f, max_adsr_time, 0.02f, OpIndex::OpC, 100 },
        { "adsrEnabled_OpC", "OpC ADSR Enabled", "", 0.0f, 1.0f, 1.0f, OpIndex::OpC, 100 },
        { "modDepth_OpC", "OpC Modulation Depth", "", 0.0f, max_mod_depth, 0.0f, OpIndex::OpC, 100 },
        { "modIndex_OpC", "OpC Modulation Index", "", 0.0f, max_mod_index, 0.0f, OpIndex::OpC, 100 },
        { "modFeedbackEnabled_OpC", "OpC Mod Feedback Enabled", "", 0.0f, 1.0f, 0.0f, OpIndex::OpC, 100 },
        { "modFeedback_OpC", "OpC Modulation Feedback", "", 0.0f, max_mod_feedback, 0.0f, OpIndex::OpC, 100 },

            // Operator D
        { "attack_OpD", "OpD Attack Time", "s", 0.0f, max_adsr_time, 0.02f, OpIndex::OpD, 100 },
        { "decay_OpD", "OpD Decay Time", "s", 0.0f, max_adsr_time, 0.0f, OpIndex::OpD, 100 },
        { "sustain_OpD", "OpD Sustain Level", "", min_sustain_level, 1.0f, 0.8f, OpIndex::OpD, 100 },
        { "release_OpD", "OpD Release Time", "s", 0.0f, max_adsr_time, 0.02f, OpIndex::OpD, 100 },
        { "adsrEnabled_OpD", "OpD ADSR Enabled", "", 0.0f, 1.0f, 1.0f, OpIndex::OpD, 100 },
        { "modDepth_OpD", "OpD Modulation Depth", "", 0.0f, max_mod_depth, 0.0f, OpIndex::OpD, 100 },
        { "modIndex_OpD", "OpD Modulation Index", "", 0.0f, max_mod_index, 0.0f, OpIndex::OpD, 100 },
        { "modFeedbackEnabled_OpD", "OpD Mod Feedback Enabled", "", 0.0f, 1.0f, 0.0f, OpIndex::OpD, 100 },
        { "modFeedback_OpD", "OpD Modulation Feedback", "", 0.0f, max_mod_feedback, 0.0f, OpIndex::OpD, 100 },

            // Operator E
        { "attack_OpE", "OpE Attack Time", "s", 0.0f, max_adsr_time, 0.02f, OpIndex::OpE, 100 },
        { "decay_OpE", "OpE Decay Time", "s", 0.0f, max_adsr_time, 0.0f, OpIndex::OpE, 100 },
        { "sustain_OpE", "OpE Sustain Level", "", min_sustain_level, 1.0f, 0.8f, OpIndex::OpE, 100 },
        { "release_OpE", "OpE Release Time", "s", 0.0f, max_adsr_time, 0.02f, OpIndex::OpE, 100 },
        { "adsrEnabled_OpE", "OpE ADSR Enabled", "", 0.0f, 1.0f, 1.0f, OpIndex::OpE, 100 },
        { "modDepth_OpE", "OpE Modulation Depth", "", 0.0f, max_mod_depth, 0.0f, OpIndex::OpE, 100 },
        { "modIndex_OpE", "OpE Modulation Index", "", 0.0f, max_mod_index, 0.0f, OpIndex::OpE, 100 },
        { "modFeedbackEnabled_OpE", "OpE Mod Feedback Enabled", "", 0.0f, 1.0f, 0.0f, OpIndex::OpE, 100 },
        { "modFeedback_OpE", "OpE Modulation Feedback", "", 0.0f, max_mod_feedback, 0.0f, OpIndex::OpE, 100 },

            // Operator F
        { "attack_OpF", "OpF Attack Time", "s", 0.0f, max_adsr_time, 0.02f, OpIndex::OpF, 100 },
        { "decay_OpF", "OpF Decay Time", "s", 0.0f, max_adsr_time, 0.0f, OpIndex::OpF, 100 },
        { "sustain_OpF", "OpF Sustain Level", "", min_sustain_level, 1.0f, 0.8f, OpIndex::OpF, 100 },
        { "release_OpF", "OpF Release Time", "s", 0.0f, max_adsr_time, 0.02f, OpIndex::OpF, 100 },
        { "adsrEnabled_OpF", "OpF ADSR Enabled", "", 0.0f, 1.0f, 1.0f, OpIndex::OpF, 100 },
        { "modDepth_OpF", "OpF Modulation Depth", "", 0.0f, max_mod_depth, 0.0f, OpIndex::OpF, 100 },
        { "modIndex_OpF", "OpF Modulation Index", "", 0.0f, max_mod_index, 0.0f, OpIndex::OpF, 100 },
        { "modFeedbackEnabled_OpF", "OpF Mod Feedback Enabled", "", 0.0f, 1.0f, 0.0f, OpIndex::OpF, 100 },
        { "modFeedback_OpF", "OpF Modulation Feedback", "", 0.0f, max_mod_feedback, 0.0f, OpIndex::OpF, 100 },

        // Output level
        { "outputLevel", "Output Level", "", 0.0f, 1.0f, 1.0f, OpIndex::None, 100 },
    };

