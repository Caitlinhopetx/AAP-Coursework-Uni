/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class MsutilityAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MsutilityAudioProcessor();
    ~MsutilityAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float panPosition;
    
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MsutilityAudioProcessor)
    
    AudioParameterFloat* stereowidth;
    AudioParameterChoice* InputSelection;
    AudioParameterChoice* OutputSelection;
    AudioSampleBuffer delayBuffer;
    AudioParameterFloat* gainslider;
    AudioParameterFloat* left_chan_pan;
    AudioParameterFloat* right_chan_pan; 
    
    int delayBufferTime = 0;
    int inforead = 0;
    int infowrite = 0;
    float previousGain;
};
