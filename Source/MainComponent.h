/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public Component,
                        public Slider::Listener,
                        private OSCReceiver,
                        private OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override
    {
        if (slider == &testSlider)
        {
             sender.send("/juce/knopjeSend",(float) testSlider.getValue());
        }
    }

private:
    
    void oscMessageReceived (const OSCMessage& message) override
    {
        if (message.size() == 1 && message[0].isFloat32())                       // [5]
            testSlider.setValue (jlimit (0.0f, 10.0f, message[0].getFloat32())); // [6]
    }
    
    Slider testSlider;
    OSCSender sender;
    OSCReceiver receiver;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
