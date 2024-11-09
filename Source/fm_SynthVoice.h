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
*    _____   __ __   __  
*   |_  \ \ / //  | /  | 
*     | |\ V / `| | `| | 
*     | |/   \  | |  | | 
* /\__/ / /^\ \_| |__| |_
* \____/\/   \/\___/\___/
*
* fm_SynthVoice.h
* 
* A Class representing a synthesiser voice. A voice holds 
* oscillators and note information.
* 
* CS Islay
*****************************************************************************/


#pragma once
#include "caspi_BlepOscillator.h"
#include "caspi_EnvelopeGenerator.h"
#include <cmath>
#include <algorithm>
template <typename FloatType>
class Voice
{
    public:
        int note;
        int velocity;
        caspi_BlepOscillator<FloatType>::Sine SineCarrier;
        caspi_BlepOscillator<FloatType>::Saw SawCarrier;
        caspi_BlepOscillator<FloatType>::Square SquareCarrier;
        caspi_BlepOscillator<FloatType>::Triangle TriangleCarrier;
        caspi_ADSREnvelope env;
        jx11_Filter filter;
        ADSREnvelope filterEnv;
        FloatType period;
        FloatType cutoff;
        FloatType resonance;
        FloatType filterMod;
        FloatType filterEnvDepth;

        // panning
        FloatType panLeft;
        FloatType panRight;

        // methods
        void noteOff();
        void reset();
        void update();
        FloatType render(FloatType input);
        void setSampleRate(FloatType sampleRate);
};