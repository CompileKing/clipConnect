/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
using namespace std;

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
    }

private:
    
    void oscMessageReceived (const OSCMessage& message) override
    {
        // cout << "current message: " << message[0].isString() << endl;
        if (message.size() == 1 && message[0].isString())
        {
            timeCodeLabel.setText(message[0].getString(), dontSendNotification);
            const char * str1 = message[0].getString().toStdString().c_str();
            const char * str2 = "14:49:00";
            int strncmpResult = strncmp(str1, str2, sizeof(&str2));
            if (strncmpResult == 0)
            {
                cout << "timecode match" << endl;
            }
        }
        
    }
    
    
    
    Slider testSlider;
    OSCSender sender;
    Label timeCodeLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
