/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
//#include "PluginEditor.h"

//==============================================================================
UnitySynthAudioProcessor::UnitySynthAudioProcessor()
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
    addParameter (freq = new AudioParameterFloat ("freq", // parameter ID
                                                  "Freq", // parameter name
                                                  100.0f,   // minimum value
                                                  1000.0f,   // maximum value
                                                  200.0f)); // default value
    addParameter (lfofreq = new AudioParameterFloat ("lfofreq", // parameter ID
                                                  "LFOFreq", // parameter name
                                                  0.0f,   // minimum value
                                                  25.0f,   // maximum value
                                                  4.0f)); // default value
    addParameter (trigger = new AudioParameterFloat ("trigger", // parameter ID
                                                     "Trigger", // parameter name
                                                     0.0f,   // minimum value
                                                     1.0f,   // maximum value
                                                     0.0f)); // default value
    


	//Array<float> envelop = SynthVoice::createEnvelope();
}

UnitySynthAudioProcessor::~UnitySynthAudioProcessor()
{
}

//==============================================================================
const String UnitySynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool UnitySynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool UnitySynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool UnitySynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double UnitySynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int UnitySynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int UnitySynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void UnitySynthAudioProcessor::setCurrentProgram (int index)
{
}

const String UnitySynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void UnitySynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void UnitySynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    FS = getSampleRate();
    createEnvelope();
//    ignoreUnused(samplesPerBlock);
//    lastSampleRate = sampleRate;

}

void UnitySynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool UnitySynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void UnitySynthAudioProcessor::createEnvelope()
{
    float attack = 0.02;
    float sustain = 2.5;
    float decay = 0.02;
    
    float attackIncrement = 1 / (FS / attack);
    float decayIncrement = 1 / (FS / decay);
    envelopeLength = (int)(attack * FS + sustain * FS + decay * FS);
    
    float attackRamp = 0;
    float decayRamp = 1;
    envelope.resize(envelopeLength);
    
    for (int i = 0; i < envelopeLength; ++i)
    {
        
        if (i < attack * FS)
        {
            envelope.set(i, attackRamp);
            attackRamp += attackIncrement;
        }
        else if ((i >= attack * FS) && (i < (envelopeLength - (decay *FS))))
        {
            envelope.set(i, 1);
        }
        else
        {
            
            envelope.set(i, decayRamp);
            decayRamp -= decayIncrement;
            
        }
        
    }
    
    
}



void UnitySynthAudioProcessor::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    if(trigger->get() != 0.0f) envelopeOn = true;
    else envelopeOn = false;
    
    for (int sample = 0; sample < numSamples; sample++)
    {
        //double theWave = osc1.sinewave(440);
        float time = (float)t / (float)FS;
        float sinx = cos(2 * pi * *lfofreq * time)*0.9;
        float sawtoothInterval = 1/(FS / *freq);
        sawtooth = sawtooth + sawtoothInterval;
        if (sawtooth > 1)sawtooth -= 2;
        else if (sawtooth < -1)sawtooth += 2;
        //else if (frequency != prev_freq) { sawtooth = 0; prev_freq = frequency; }
        for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
        {
            //outputBuffer.addSample(channel, startSample, sinx/*envelope.getReference(envelopePoint)*/);
            if (envelopeOn)
            {
                outputBuffer.addSample(channel, startSample, sawtooth*sinx*envelope.getReference(envelopePoint));
                test = envelope.getReference(envelopePoint);
                envelopePoint++;
                if (envelopePoint >= envelopeLength)
                {
                    envelopePoint = 0;
                    envelopeOn = false;
                    *trigger = 0.0f;
                }
            }
            else
                outputBuffer.addSample(channel, startSample, 0);
        }
        t++;
        if (t > FS)t -= FS;
        
        startSample++;
    }
    
}

void UnitySynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	
	buffer.clear();
	renderNextBlock(buffer, 0, buffer.getNumSamples());
}

//==============================================================================
bool UnitySynthAudioProcessor::hasEditor() const
{
    return false; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* UnitySynthAudioProcessor::createEditor()
{
    return 0;
//    return new UnitySynthAudioProcessorEditor (*this);
}

//==============================================================================
void UnitySynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void UnitySynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new UnitySynthAudioProcessor();
}
