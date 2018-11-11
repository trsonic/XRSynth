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
class UnitySynthAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    UnitySynthAudioProcessor();
    ~UnitySynthAudioProcessor();

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
    
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples);
    void createEnvelope();
    Array<float> envelope;


private:
    //==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UnitySynthAudioProcessor)

    float frequency = 440;
    float prev_freq = frequency;
    float level;
    bool envelopeOn = false;
    int envelopeLength;
    
    
    
    int t = 0;
    float pi = 3.14159265358979323846;
    float FS;
    float sawtooth = 0;

    int envelopePoint = 0;
    
    float test = 0;

	double lastSampleRate;
    
    AudioParameterFloat* freq;
    AudioParameterFloat* lfofreq;
    AudioParameterFloat* trigger;

    
};
