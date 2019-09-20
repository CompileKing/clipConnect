/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TimecodeList/TimecodeList.h"

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

            for (int i=0;i<100;i++)
            {
                const char * str1 = message[0].getString().toStdString().c_str();
                const char * str2 = timecodeList.timeCodeArray[i].c_str();
                int strncmpResult = strncmp(str1, str2, 4);
                if (strncmpResult == 0)
                {
                    String timeCodeLabelString = "current column: " + to_string(i);
                    currentColumn.setText(timeCodeLabelString, dontSendNotification);
                    currentColumnIndex = i;
                    sender.send("/max/triggercolumn",i);
                }
            }
            timeCodeLabel.setColour(Label::textColourId,
                                    Colour::fromHSV(currentColumnIndex/72.f*0.4+0.1, 1.f, 1.f, 1.f));
            testSlider.setValue(currentColumnIndex/72.f);
            testSlider.setColour(Slider::thumbColourId,
                                 Colour::fromHSV(currentColumnIndex/72.f*0.4+0.1, 1.f, 1.f, 1.f));
        }
    }
  
    Slider testSlider;
    OSCSender sender;
    Label timeCodeLabel;
    Label currentColumn;
    TimecodeList timecodeList;
    float currentColumnIndex;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
