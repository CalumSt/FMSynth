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
#include "Oscillators/caspi_PMOperator.h"
#include "Envelopes/caspi_EnvelopeGenerator.h"
#include "Utilities/caspi_Gain.h"
#include <cmath>
#include "Oscillators/caspi_BlepOscillator.h"

template <typename FloatType>
class fm_SynthVoice
{
    public:
        CASPI::Gain<FloatType> Gain;

        // methods
        void noteOn(const int _note, const int _velocity)
        {
            auto frequency = convertMidiToHz (note);
            auto modIndex = static_cast<FloatType>(0.00); /// CHANGE ME
            oscillator.setFrequency (frequency, modIndex ,sampleRate);
            testOsc.setFrequency(frequency, sampleRate);
            note = _note;
            velocity = _velocity;
            Gain.setGain (static_cast<FloatType>(0.75));
            envelope.noteOn();
            active = true;

        }

        void noteOff()
        {
            envelope.noteOff();
            active = false;
        }

        void shutdown()
        {
            Gain.derampGain(static_cast<FloatType>(0.01), sampleRate);
            if (Gain.getGain() <= oscillator.zero)
            {
                reset();
            }
        }

        void reset()
        {
            Gain.reset();
            noteOff();
            oscillator.reset();
            envelope.reset();
        }
        FloatType render() {
            // FloatType nextSample = oscillator.getNextSample();
            FloatType nextSample = testOsc.getNextSample();
            FloatType envSample = envelope.render();
            // auto gain = Gain.getGain();
            return envSample * nextSample;
        }
        void setSampleRate (FloatType _sampleRate)
        {
            CASPI_ASSERT (sampleRate > 0, "Sample Rate must be greater than zero.");
            sampleRate = _sampleRate;
            envelope.setSampleRate (_sampleRate);
        }

        void setADSR(FloatType _attackTime, FloatType _decayTime, FloatType _sustainLevel, FloatType _releaseTime)
        {
            setAttackTime (_attackTime);
            setSustainLevel (_sustainLevel);
            setDecayTime (_decayTime);
            setReleaseTime (_releaseTime);
        }

        void setAttackTime(FloatType _attackTime) { envelope.setAttackTime (_attackTime); }
        void setDecayTime(FloatType _decayTime) { envelope.setDecayTime (_decayTime); }
        void setSustainLevel(FloatType _sustainLevel) { envelope.setSustainLevel (_sustainLevel); }
        void setReleaseTime(FloatType _releaseLevel) { envelope.setReleaseTime (_releaseLevel); }

        [[nodiscard]] int getNote() const { return note; }
        [[nodiscard]] int getVelocity() const { return velocity; }
        [[nodiscard]] FloatType getSampleRate() const { return sampleRate; }
        [[nodiscard]] bool isActive() const { return active; }

        static FloatType convertMidiToHz(const int _note)
        {
            constexpr auto A4_FREQUENCY = 440.0;
            constexpr auto A4_NOTE_NUMBER = 69.0;
            constexpr auto NOTES_IN_AN_OCTAVE = 12.0;
            return static_cast<FloatType>(A4_FREQUENCY * std::pow(2, (static_cast<double>(_note) - A4_NOTE_NUMBER) / NOTES_IN_AN_OCTAVE));
        }

private:
        bool active = false;
        int note = 0;
        int velocity = 0;
        FloatType sampleRate = static_cast<FloatType>(44100.0);
        CASPI::PMOperator<FloatType> oscillator;
        CASPI::Envelope::ADSR<FloatType> envelope;
        CASPI::BlepOscillator::Saw<FloatType> testOsc;
};