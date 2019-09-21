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
        string receivedAddress = message.getAddressPattern().toString().toStdString().c_str();
        {
            int value = tcUpdater(message, receivedAddress, "/fake/resolume/adress1", 1);
            static int oldValue = value;
            if (value != oldValue)
            {
                sender.send("/max/triggercolumn1",value);
                oldValue = value;
            }
        }
        {
            int value = tcUpdater(message, receivedAddress, "/fake/resolume/adress2", 2);
            static int oldValue = value;
            if (value != oldValue)
            {
                sender.send("/max/triggercolumn2",value);
                oldValue = value;
            }
        }
    }
    
    int tcUpdater(const OSCMessage& message, string receivedAddress, string checkAddress,int tcNumber)
    {
        const char * address1 = receivedAddress.c_str();
        const char * address1Set = checkAddress.c_str();
        int strncmpResult = strncmp(address1, address1Set, checkAddress.length());
        if (strncmpResult == 0)
        {
            
            if (tcNumber == 1)
                timeCodeLabel1.setText(message[0].getString(), dontSendNotification);
            else if (tcNumber == 2)
                timeCodeLabel2.setText(message[0].getString(), dontSendNotification);
            
            for (int i=0;i<100;i++)
            {
                const char * str1 = message[0].getString().toStdString().c_str();
                const char * str2 = timecodeList.timeCodeArray10min[i].c_str();
                int strncmpResult = strncmp(str1, str2, 4);
                if (strncmpResult == 0)
                {
                    String timeCodeLabelString = "current column: " + to_string(i);
                    if (tcNumber == 1)
                        tcTriggerLabel1.setText(timeCodeLabelString, dontSendNotification);
                    else if (tcNumber == 2)
                        tcTriggerLabel2.setText(timeCodeLabelString, dontSendNotification);

                    if (tcNumber == 1)
                        tcTrigger1 = i;
                    else if (tcNumber == 2)
                        tcTrigger2 = i;
                }
            }
            int value;
            if (tcNumber == 1)
                value = tcTrigger1;
            else if (tcNumber == 2)
                value = tcTrigger2;
    
            
            if (tcNumber == 1)
            {
                timecodeSlider1.setValue(tcTrigger1/72.f);
                timeCodeLabel1.setColour(Label::textColourId,
                                         Colour::fromHSV(tcTrigger1/72.f*0.4+0.1, 1.f, 1.f, 1.f));
                timecodeSlider1.setColour(Slider::thumbColourId,
                                          Colour::fromHSV(tcTrigger1/72.f*0.4+0.1, 1.f, 1.f, 1.f));
            }
            else if (tcNumber == 2)
            {
                timecodeSlider2.setValue(tcTrigger2/72.f);
                timeCodeLabel2.setColour(Label::textColourId,
                                         Colour::fromHSV(tcTrigger2/72.f*0.4+0.1, 1.f, 1.f, 1.f));
                timecodeSlider2.setColour(Slider::thumbColourId,
                                          Colour::fromHSV(tcTrigger2/72.f*0.4+0.1, 1.f, 1.f, 1.f));
            }
        }
        if (tcNumber == 1)
            return tcTrigger1;
        else if (tcNumber == 2)
            return tcTrigger2;
        else
            return 0;
    }
  
    Slider timecodeSlider1;
    Slider timecodeSlider2;
    Label timeCodeLabel1;
    Label timeCodeLabel2;
    Label tcTriggerLabel1;
    Label tcTriggerLabel2;
    TimecodeList timecodeList;
    OSCSender sender;
    float tcTrigger1;
    float tcTrigger2;
    
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
