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
#include "Gain/caspi_Gain.h"
#include "Synthesizers/caspi_PMAlgorithm.h"
#include "Utilities/caspi_Maths.h"

#include <numeric>

enum class SixOperatorAlgorithmIndex : int
{
    Alg1,
    Alg2,
    Alg3,
    Alg4,
    Alg5,
    Alg6,
    Alg7,
    Alg8,
    Count
};

// Set up our test implementations, give it a float type, how many operators, and the Algorithm enum
template <typename FloatType>
class SixOperatorAlgorithm final : public CASPI::PM::Algorithm<FloatType, 6, SixOperatorAlgorithmIndex>
{
public:
    FloatType render() noexcept override
    {
        using enum CASPI::PM::OpIndex;

        auto out = CASPI::Constants::zero<FloatType>;
        switch (this->getAlgorithm())
        {
            // Algorithm 1: 2 parallel sets of 3 series operators
            case SixOperatorAlgorithmIndex::Alg1:
            {
                auto a1m1 = this->operators.at(std::to_underlying(OpA)).render();
                auto a1m2 = this->operators.at(std::to_underlying(OpB)).render(a1m1);
                auto a1c1 = this->operators.at(std::to_underlying(OpC)).render(a1m2);
                auto a1m3 = this->operators.at(std::to_underlying(OpD)).render();
                auto a1m4 = this->operators.at(std::to_underlying(OpE)).render(a1m3);
                auto a1c2 = this->operators.at(std::to_underlying(OpF)).render(a1m4);
                out = std::midpoint(a1c1, a1c2);
                break;
            }
            // Algorithm 2: 4 operators in series, parallel with 2 operators in series
            case SixOperatorAlgorithmIndex::Alg2:
            {
                auto a2m1 = this->operators.at(std::to_underlying(OpA)).render();
                auto a2m2 = this->operators.at(std::to_underlying(OpB)).render(a2m1);
                auto a2m3 = this->operators.at(std::to_underlying(OpC)).render(a2m2);
                auto a2c1 = this->operators.at(std::to_underlying(OpD)).render(a2m3);
                auto a2m5 = this->operators.at(std::to_underlying(OpE)).render();
                auto a2c2 = this->operators.at(std::to_underlying(OpF)).render(a2m5);
                out = std::midpoint(a2c1, a2c2);
                break;
            }
            // 3 groups of 2 series operators
            case SixOperatorAlgorithmIndex::Alg3:
            {
                auto a3m1 = this->operators.at(std::to_underlying(OpA)).render();
                auto a3c1 = this->operators.at(std::to_underlying(OpB)).render(a3m1);
                auto a3m2 = this->operators.at(std::to_underlying(OpC)).render();
                auto a3c2 = this->operators.at(std::to_underlying(OpD)).render(a3m2);
                auto a3m3 = this->operators.at(std::to_underlying(OpE)).render();
                auto a3c3 = this->operators.at(std::to_underlying(OpF)).render(a3m3);
                out = (a3c1 + a3c2 + a3c3) / 3;
                break;
            }
            default:
                break;
        }

        return out * this->getOutputLevel();
    }

    template <typename buffer>
    void render (buffer& outputBuffer, const int blockSize) noexcept
    {
        for (int i = 0; i < blockSize; ++i)
        {
            outputBuffer[i] = render();
        }
    }

    template <typename buffer>
    void render (buffer& outputBufferLeft, buffer& outputBufferRight, const int blockSize) noexcept
    {
        for (int i = 0; i < blockSize; ++i)
        {
            auto signal = render();
            outputBufferLeft[i] = signal;
            outputBufferRight[i] = signal;
        }
    }
};

template <typename FloatType>
class fm_SynthVoice
{
    using enum CASPI::PM::OpIndex;
    public:
        CASPI::Gain<FloatType> Gain;
        SixOperatorAlgorithm<FloatType> Oscillator;

        // methods
        void noteOn(const int _note, const int _velocity)
        {
            note = _note;
            velocity = _velocity;
            Gain.setGain (1.0, sampleRate);
            Gain.setGainRampDuration (static_cast<FloatType> (0.002),sampleRate);
            Oscillator.setAlgorithm (SixOperatorAlgorithmIndex::Alg2);
            auto frequency = CASPI::Maths::midiNoteToHz<FloatType> (note);
            Oscillator.setFrequency (frequency, sampleRate);
            Oscillator.noteOn();
            active = true;
        }

        void noteOff()
        {
            Oscillator.noteOff();
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
            return nextSample;
        }
        void setSampleRate (FloatType _sampleRate)
        {
            CASPI_ASSERT (sampleRate > 0, "Sample Rate must be greater than zero.");
            sampleRate = _sampleRate;
            Oscillator.setSampleRate(_sampleRate);
            Gain.setSampleRate (_sampleRate);
        }

        void setAlgorithm(SixOperatorAlgorithmIndex alg)
        {
            Oscillator.setAlgorithm (alg);
        }
        /// Modulation setters
        void setModulationFeedback(const CASPI::PM::OpIndex op, const FloatType modFeedback)
        {
            Oscillator.setModulationFeedback (op, modFeedback);
        };
        // this might need to be changed in future to account for different algorithms!
        void setModulation(const CASPI::PM::OpIndex op, FloatType modIndex, FloatType modDepth)
        {
            Oscillator.setModulation(op, modIndex, modDepth);
        };

        void setModulation(const CASPI::PM::OpIndex op, const FloatType modIndex, const FloatType modDepth, const FloatType modFeedback)
        {
            Oscillator.setModulation(op, modIndex, modDepth, modFeedback);
        };

        void setADSR(const CASPI::PM::OpIndex op, FloatType _attackTime, FloatType _decayTime, FloatType _sustainLevel, FloatType _releaseTime)
        {
            setAttackTime (op, _attackTime);
            setSustainLevel (op, _sustainLevel);
            setDecayTime (op, _decayTime);
            setReleaseTime (op, _releaseTime);
        }
        // just use Carrier ADSR for now
        void setAttackTime(const CASPI::PM::OpIndex op, FloatType _attackTime) { Oscillator.setAttackTime (op,_attackTime); }
        void setDecayTime(const CASPI::PM::OpIndex op, FloatType _decayTime) { Oscillator.setDecayTime (op,_decayTime); }
        void setSustainLevel(const CASPI::PM::OpIndex op, FloatType _sustainLevel) { Oscillator.setSustainLevel (op,_sustainLevel); }
        void setReleaseTime(const CASPI::PM::OpIndex op, FloatType _releaseLevel) { Oscillator.setReleaseTime (op,_releaseLevel); }

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