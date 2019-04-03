/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MsutilityAudioProcessor::MsutilityAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    
    // ADD PARAMETERS HERE 
    
    //stereo width perameter
    stereowidth = new AudioParameterFloat ("stereowidth", "stereo width", 0.0f, 2.0f, 1.0f);
    addParameter(stereowidth);
    
//input selection
    InputSelection = new AudioParameterChoice ("InputSelection", "Input", {"stereo", "Mid-Side"}, 1);
    addParameter(InputSelection);
    
    //Output selection

    OutputSelection = new AudioParameterChoice ("OutputSelection", "Output", { "stereo", "Mid-Side" }, 1);
    addParameter(OutputSelection);
}

MsutilityAudioProcessor::~MsutilityAudioProcessor()
{
}

//==============================================================================
const String MsutilityAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MsutilityAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MsutilityAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MsutilityAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MsutilityAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MsutilityAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MsutilityAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MsutilityAudioProcessor::setCurrentProgram (int index)
{
}

const String MsutilityAudioProcessor::getProgramName (int index)
{
    return {};
}

void MsutilityAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MsutilityAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MsutilityAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MsutilityAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MsutilityAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    auto* audioLeft = buffer.getWritePointer (0);
    auto* audioRight = buffer.getWritePointer (1);

    
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        auto inLeft = audioLeft[i];
        auto inRight = audioRight[i];
    
        auto side = 0.5 * (inLeft - inRight);
        auto mid = 0.5 * (inLeft + inRight);
    }
    
        
        
        // ADD ALL YOUR ENCODING/DECODING EQUATIONS HERE

        // ..do something to the data...
    }

//==============================================================================
bool MsutilityAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MsutilityAudioProcessor::createEditor()
{
    return new GenericAudioProcessorEditor (this);
}

//==============================================================================
void MsutilityAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MsutilityAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MsutilityAudioProcessor();
}
