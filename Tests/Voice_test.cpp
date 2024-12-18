#pragma once
#include <gtest/gtest.h>
#include <cstdio>
#include "fm_SynthVoice.h"

// Arrange, Act and Assert
TEST(VoiceTests, Constructor_test) {
    fm_SynthVoice<float> voice;
    voice.reset();
    EXPECT_EQ(0, voice.getNote());
    EXPECT_EQ(0, voice.getVelocity());
    EXPECT_EQ(44100.0f, voice.getSampleRate());
}

TEST(VoiceTests, Render_test)
{
    fm_SynthVoice<float> voice;
    voice.reset();
    voice.setADSR (0.5f,0.5f,0.5f,0.5f);
    voice.setSampleRate (44100.0f);
    voice.noteOn(70,127);

    for (int i = 0; i < 44100; i++)
    {
        auto sample = voice.render();
        if (i != 0) { EXPECT_NE (0.0f,sample); }
        EXPECT_LE (sample,1.0f);
        EXPECT_GE (sample,-1.0f);
    }
}