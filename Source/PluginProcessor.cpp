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
    
    //PARAMETERS HERE
    

    
//input selection buttons
    InputSelection = new AudioParameterChoice ("InputSelection", "Input", {"stereo", "Mid-Side"}, 1);
    addParameter(InputSelection);
    
//Output selection buttons
    OutputSelection = new AudioParameterChoice ("OutputSelection", "Output", { "stereo", "Mid-Side" }, 1);
    addParameter(OutputSelection);
    
    
    //  following perameters of type float. the arguments within the brackets are as follows: 1. perameter name 2. name shown on plugin, 3. minimum level 4. max level 5. defult level
    
    //advanced task gain slider creates gain slider in plug in
    gainslider = new AudioParameterFloat ("gainslider", "Gain", 0.0f, 1.0f, 0.5f);
    addParameter(gainslider);
    
    //advanced task Panner creates panning sliders for left and right signals in plugin
    left_chan_pan = new AudioParameterFloat ("left_chan_pan", "PanLeft", -1.0f, 1.0f, 0.0f);
    addParameter(left_chan_pan);
    
    right_chan_pan = new AudioParameterFloat ("right_chan_pan", "PanRight", -1.0f, 1.0f, 0.0f);
    addParameter(right_chan_pan);
    
    //stereo width perameter craetes width slider in plugin
    stereowidth = new AudioParameterFloat ("stereowidth", "stereo width", 0.0f, 2.0f, 1.0f);
    addParameter(stereowidth);
    
    //advanced task polarity flip creates phase iversoin buttons for left and right signals
    polarityleft = new AudioParameterBool ("polarityleft", "Inverse Polarity Left", 0);
    addParameter(polarityleft);

    polarityright = new AudioParameterBool("polarityright", "Inverse Polarity Right", 0);
    addParameter(polarityright);
    

    
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
    
    // gain slider
    buffer.applyGain(*gainslider);
    
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto currentGain = gainslider-> get();// retrevig gain value from plug in
    if (currentGain == previousGain){
        buffer.applyGain(currentGain);// if statement to check current gain value matches previous value
        
    }
    else {
        buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain, currentGain); //
        
        previousGain = currentGain;
        
        // resorce https://docs.juce.com/master/tutorial_audio_parameter.html?fbclid=IwAR3CXQ7iZvz3yseuiP-b4wAgMIN3AGD9WSMTSb2BxkvFawKKWCc-mHw9WQM
        
        
        
    }

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
    
   
    
    //receiving sample num from buffer
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        //Retreving audio from channels
        auto* audioLeft = buffer.getWritePointer (0);
        auto* audioRight = buffer.getWritePointer (1);
        
        //retreving values from plug-in
        auto InputChoice = InputSelection->getIndex();
        auto OutputChoice = OutputSelection->getIndex();
        auto controlwidth = stereowidth->get();
        auto LeftPan = left_chan_pan->get();
        auto RightPan = right_chan_pan->get();
        int getPolarityleft = polarityleft->get();
        int getPolarityright = polarityright->get();
        
        //calculating pan possitions, receving them from the plug in
        float pDash = (LeftPan + 1.0) / 2.0;
        float pDash2 = (RightPan + 1.0) / 2.0;
      

        //encoding mid side
        
        if (InputChoice == 1 && OutputChoice == 2)
        {
            auto side = 0.5f * (audioLeft[i] - audioRight[i]);
            auto mid = 0.5f * (audioLeft[i] + audioRight[i]);
            
            audioLeft[i] = mid;
            audioRight[i] = side; // Overwriting audio data with side data
         }
        
        
        //decoding midside
        
        else if (InputChoice == 2 && OutputChoice == 1)
        {
            //decoding equations
          float midtoleft = (audioLeft[i] + audioRight[i]);
          float sideright = (audioLeft[i] - audioRight[i]);
            
          audioLeft[i] = midtoleft;
          audioRight[i] = sideright; // Overwriting audio data with side data
    
        }
        //encoding width parameter
        float wideright = (controlwidth) * (audioLeft[i] - audioRight[i]);
        float wideleft = (2 - controlwidth) * (audioRight[i] + audioLeft[i]);
        
        audioLeft[i] = wideleft + wideright;
        audioRight[i] = wideleft - wideright; // Overwriting audio data with wide data
        
         //panner
        
        float panLeft = audioLeft[i] * (1.0 - pDash);
        audioLeft[i] = panLeft; // Overwriting audio data with pan data
        
        float panRight = audioRight[i] * (1.0 - pDash2);
        audioRight[i] = panRight; // Overwriting audio data with pan data
      
       
            
        //phase/ polarity shift
        if (getPolarityleft == 1)
        {
            float polarityflipL = audioLeft[i] * -1; // flips left audio polarity by multiplying the amplitude by -1
            audioLeft[i] = polarityflipL; // Overwriting audio data with polarity data
            
        }
        
        if (getPolarityright == 1)
        {
            
            float polarityflipR = audioRight[i] * -1; // flips right audio polarity by multiplying the amplitude by -1
            audioRight[i] = polarityflipR; // Overwriting audio data with polarity data
        }
        
     
        
                }
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

    
    // writing perameter data to memory for preset usage in plugin
    
    MemoryOutputStream stream(destData, true);
    stream.writeFloat (*stereowidth);
    stream.writeInt (*InputSelection);
    stream.writeInt (*OutputSelection);
    stream.writeFloat (*gainslider);
    stream.writeFloat(*left_chan_pan);
    stream.writeFloat(*right_chan_pan);
    stream.writeBool(*polarityleft);
    stream.writeBool(*polarityright);
    
    

}
void MsutilityAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
   
    //retreving infromation from memory
    MemoryInputStream stream(data, static_cast<size_t>(sizeInBytes), false);
    
    //outputting information to plug in
    
    stereowidth->setValueNotifyingHost(stereowidth->getNormalisableRange().convertTo0to1(stream.readFloat())); // converting data above float value of 1 to a range of 0-1 so information can be used by plugin.
    
    InputSelection->  setValueNotifyingHost(stream.readInt());
    OutputSelection-> setValueNotifyingHost(stream.readInt());
    gainslider->setValueNotifyingHost(stream.readFloat());
    left_chan_pan->setValueNotifyingHost(left_chan_pan->getNormalisableRange().convertTo0to1(stream.readFloat()));// converting data above float value of 1 to a range of 0-1 so
   // information can be used by plugin.
    right_chan_pan->setValueNotifyingHost(right_chan_pan->getNormalisableRange().convertTo0to1(stream.readFloat()));// converting data above float value of 1 to a range of 0-1 so
   // information can be used by plugin.
    polarityleft->setValueNotifyingHost(stream.readBool());
    polarityright->setValueNotifyingHost(stream.readBool());
   
    
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MsutilityAudioProcessor();
}


