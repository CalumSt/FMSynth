/*****************************************************************************
 *   ,ad8888ba,    88        88  88  88      888888888888  ad88888ba
 *  d8"'    `"8b   88        88  88  88           88      d8"     "8b
 * d8'        `8b  88        88  88  88           88      Y8,
 * 88          88  88        88  88  88           88      `Y8aaaaa,
 * 88          88  88        88  88  88           88        `"""""8b,
 * Y8,    "88,,8P  88        88  88  88           88              `8b
 *  Y8a.    Y88P   Y8a.    .a8P  88  88           88      Y8a     a8P
 *   `"Y8888Y"Y8a   `"Y8888Y"'   88  88888888888  88       "Y88888P"
 *
 * ███╗   ███╗ ██████╗ ██████╗ ██╗   ██╗██╗      █████╗ ████████╗ ██████╗ ██████╗
 * ████╗ ████║██╔═══██╗██╔══██╗██║   ██║██║     ██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗
 * ██╔████╔██║██║   ██║██║  ██║██║   ██║██║     ███████║   ██║   ██║   ██║██████╔╝
 * ██║╚██╔╝██║██║   ██║██║  ██║██║   ██║██║     ██╔══██║   ██║   ██║   ██║██╔══██╗
 * ██║ ╚═╝ ██║╚██████╔╝██████╔╝╚██████╔╝███████╗██║  ██║   ██║   ╚██████╔╝██║  ██║
 * ╚═╝     ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝
*
* fm_SynthVoice.h
* 
* A Class representing a synthesiser voice. A voice holds 
* oscillators and note information.
* 
* CS Islay
*****************************************************************************/


#pragma once
#include "Synthesizers/caspi_PMAlgorithm.h"
#include "Utilities/caspi_Maths.h"
#include "Utilities/caspi_Gain.h"
#include "Oscillators/caspi_BlepOscillator.h"

template <typename FloatType>
class fm_SynthVoice
{
    using enum CASPI::PM::Algorithms::BasicCascadeOpCodes;
    public:
        CASPI::Gain<FloatType> Gain;
        CASPI::PM::Algorithms::BasicCascade<FloatType> Oscillator;

        // methods
        void noteOn(const int _note, const int _velocity)
        {
            note = _note;
            velocity = _velocity;
            auto frequency = CASPI::Maths::midiNoteToHz<FloatType> (note);
            auto modIndex = static_cast<FloatType> (0.50); /// CHANGE ME
            Oscillator.setFrequency (frequency, sampleRate);
            Oscillator.setModulation (modIndex, static_cast<FloatType> (0.25));
            Oscillator.enableADSR(Carrier);
            Oscillator.noteOn();
            Gain.setGainRampDuration (static_cast<FloatType> (0.003),sampleRate); // Suppress audible pops
            Gain.setGain (static_cast<FloatType> (0.75), sampleRate);
            active = true;
        }

        void noteOff()
        {
            Oscillator.noteOff();
            Gain.setGainRampDuration (static_cast<FloatType> (0.001),sampleRate); // Suppress audible pops
            Gain.setGain (CASPI::Constants::zero<FloatType>, sampleRate, true);
            active = false;
        }

        void shutdown()
        {
            Gain.setGain(static_cast<FloatType>(0), sampleRate);
            Gain.setGainRampDuration (0.01,sampleRate);
            if (Gain.getGain() <= Oscillator.zero)
            {
                reset();
            }
        }

        void reset()
        {
            Gain.reset();
            noteOff();
            Oscillator.reset();
        }
        FloatType render()
        {
            FloatType nextSample = Oscillator.render();
            Gain.apply(nextSample);
            return nextSample;
        }
        void setSampleRate (FloatType _sampleRate)
        {
            CASPI_ASSERT (sampleRate > 0, "Sample Rate must be greater than zero.");
            sampleRate = _sampleRate;
            Oscillator.setSampleRate(_sampleRate);
            Gain.setSampleRate (_sampleRate);
        }

        void setADSR(FloatType _attackTime, FloatType _decayTime, FloatType _sustainLevel, FloatType _releaseTime)
        {
            setAttackTime (_attackTime);
            setSustainLevel (_sustainLevel);
            setDecayTime (_decayTime);
            setReleaseTime (_releaseTime);
        }
        // just use Carrier ADSR for now
        void setAttackTime(FloatType _attackTime) { Oscillator.setAttackTime (Carrier,_attackTime); }
        void setDecayTime(FloatType _decayTime) { Oscillator.setDecayTime (Carrier,_decayTime); }
        void setSustainLevel(FloatType _sustainLevel) { Oscillator.setSustainLevel (Carrier,_sustainLevel); }
        void setReleaseTime(FloatType _releaseLevel) { Oscillator.setReleaseTime (Carrier,_releaseLevel); }

        [[nodiscard]] int getNote() const { return note; }
        [[nodiscard]] int getVelocity() const { return velocity; }
        [[nodiscard]] FloatType getSampleRate() const { return sampleRate; }
        [[nodiscard]] bool isActive() const { return active; }

private:
        bool active = false;
        int note = 0;
        int velocity = 0;
        FloatType sampleRate = CASPI::Constants::DEFAULT_SAMPLE_RATE<FloatType>;
};