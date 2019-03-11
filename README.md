# XRSynth - VR and AR Synthesizer
## This project was created during the [Abbey Road Red Hackathon](https://www.abbeyroad.com/hackathon) on 10-11 November 2018 at the [Abbey Road Studios](https://www.abbeyroad.com).

### Authors:
- [Pedro Alvarez](https://github.com/psalvarez) - Unity programming, 3D environment creation, object interaction,
- [Tomasz Rudzki](https://github.com/trsonic) - Unity and C++ (JUCE) integration, C++ synth plugin code,
- [Ed Storey](https://github.com/edStorey) - DSP programing, C++ synth plugin code.

### The project won the Most Original Idea prize sponsored by the London Field Brewery.
![alt text](https://github.com/trsonic/XRSynth/blob/master/abbey_road_team.jpg "Tomasz Rudzki, Ed Storey and Pedro Alvarez")


## XRSynth is as an engaging, hyper-realistic XR experience, an introduction to the world of generative music.

XRSynth is a project that explores a new and unorthodox way of interacting with synthesizers. By mapping the physical behaviour of one or more virtual objects to the parameters of the synthesizer, we have created an instrument that encourages a different approach to sound design. This may allow composers and artists formulate ideas based on generative inputs. It also allows for those without any knowledge of sound design to engage with experimentation in sound. There is broad scope for this project, with application in video game development, augmented or virtual reality and lends itself to interest for end users with all levels of experience.

This app was built by writing both a small virtual world in the unity engine in C# and synthesiser plugin in C++ using the JUCE framework. The plugin was integrated in the unity framework using the new JUCE Unity integration system.

What's next for XRSynth:
User Interface tweaking. Implementing more advanced audio synthesis algorithms. Spatial audio implementation. Testing and optimization for the VR and AR headsets.


[//]: # (The example shown in this demo shows several objects mapped to different audio outputs. Two of the objects play a sample of audio when the collide with another object showing the potential for varying sounds. The third object has different components of the object mapped to parameters of a synthesisier plugin. In this case the y coordinate decides the pitch height of the synthesiser and the rotation decides frequency of an LFO amplitude modulator.
Trying to find new ways of interaction using 3d technology, virtual and augmented reality.
Controlling audio processing parameters with physical parameters.
We have created a working user-responsive prototype of our instrument.)




