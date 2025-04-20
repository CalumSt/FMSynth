cmake_minimum_required(VERSION 3.22)
# Set up the testing project
project(TESTING)
# allow testing from this directory
enable_testing()

# set up sources
include(GoogleTest)

set(This Tests)
# --------------------------------------------------------------------------
# ADD TEST FILES HERE
set(SOURCES
        Test.cpp
        Voice_test.cpp
)
# --------------------------------------------------------------------------


add_executable(${PROJECT_NAME} ${SOURCES})

# --------------------------------------------------------------------------
# ADD DEPENDENCIES HERE
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../Libs/googletest/googletest/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../Source
        ${CMAKE_CURRENT_SOURCE_DIR}/../Libs/JUCE/modules
        ${CMAKE_CURRENT_SOURCE_DIR}/../Libs/CASPI/Source
    )    
# --------------------------------------------------------------------------
    
target_link_libraries(${PROJECT_NAME} 
PRIVATE
    juce::juce_audio_utils
PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags    
    CASPI
    GTest::gtest_main)


gtest_discover_tests(${PROJECT_NAME})