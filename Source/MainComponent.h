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
            
            string timeCodeArray[100] = {
                "00:00:00",
                "00:10:00",
                "00:20:00",
                "00:30:00",
                "00:40:00",
                "00:50:00",
                "01:00:00",
                "01:10:00",
                "01:20:00",
                "01:30:00",
                "01:40:00",
                "01:50:00",
                "02:00:00",
                "02:10:00",
                "02:20:00",
                "02:30:00",
                "02:40:00",
                "02:50:00",
                "03:00:00",
                "03:10:00",
                "03:20:00",
                "03:30:00",
                "03:40:00",
                "03:50:00",
                "04:00:00",
                "04:10:00",
                "04:20:00",
                "04:30:00",
                "04:40:00",
                "04:50:00",
                "05:00:00",
                "05:10:00",
                "05:20:00",
                "05:30:00",
                "05:40:00",
                "05:50:00",
                "06:00:00",
                "06:10:00",
                "06:20:00",
                "06:30:00",
                "06:40:00",
                "06:50:00",
                "07:00:00",
                "07:10:00",
                "07:20:00",
                "07:30:00",
                "07:40:00",
                "07:50:00",
                "08:00:00",
                "08:10:00",
                "08:20:00",
                "08:30:00",
                "08:40:00",
                "08:50:00",
                "09:00:00",
                "09:10:00",
                "09:20:00",
                "09:30:00",
                "09:40:00",
                "09:50:00",
                "10:00:00",
                "10:10:00",
                "10:20:00",
                "10:30:00",
                "10:40:00",
                "10:50:00",
                "11:00:00",
                "11:10:00",
                "11:20:00",
                "11:30:00",
                "11:40:00",
                "11:50:00",
                "12:00:00" };
                
                
            
            for (int i=0;i<100;i++)
            {
                const char * str1 = message[0].getString().toStdString().c_str();
                const char * str2 = timeCodeArray[i].c_str();
                int strncmpResult = strncmp(str1, str2, sizeof(&str2));
                if (strncmpResult == 0)
                {
                    String timeCodeLabelString = "current column: " + to_string(i);
                    currentColumn.setText(timeCodeLabelString, dontSendNotification);
                }
            }
        }

    }
  
    Slider testSlider;
    OSCSender sender;
    Label timeCodeLabel;
    Label currentColumn;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
