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
            int value = tcTriggerCreator(message, receivedAddress, tcInputAddress1, 1);
            static int oldValue = value;
            if (value != oldValue)
            {
                sender.send("/max/triggercolumn1",value);
                oldValue = value;
            }
        }
        {
            int value = tcTriggerCreator(message, receivedAddress, tcInputAddress2, 2);
            static int oldValue = value;
            if (value != oldValue)
            {
                sender.send("/max/triggercolumn2",value);
                oldValue = value;
            }
        }
    }
    
    // this function handles everything timecode related for 2 incomming timecode signals and returns a trigger index for each of the 2 timecode inputs
    int tcTriggerCreator(const OSCMessage& message, string receivedAddress, string checkAddress,int tcNumber)
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
            
            for (int i=0;i<144;i++)
            {
                const char * str1 = message[0].getString().toStdString().c_str();
                const char * str2 = timecodeList.timeCodeArray10min[i].c_str();
                int strncmpResult = strncmp(str1, str2, 4);
                if (strncmpResult == 0)
                {
                    String timeCodeLabelString = to_string(i);
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
    
            float triggerLabelColourOffset = 0.13;
            float colourOffset = 0.1;
            
            if (tcNumber == 1)
            {
                timecodeSlider1.setValue(tcTrigger1/144.f);
                timeCodeLabel1.setColour(Label::textColourId,
                                         Colour::fromHSV(tcTrigger1/144.f*0.4+colourOffset, 1.f, 1.f, 1.f));
                tcTriggerLabel1.setColour(Label::textColourId,
                                         Colour::fromHSV(tcTrigger1/144.f*0.4+triggerLabelColourOffset, 1.f, 1.f, 1.f));
                timecodeSlider1.setColour(Slider::thumbColourId,
                                          Colour::fromHSV(tcTrigger1/144.f*0.4+colourOffset, 1.f, 1.f, 1.f));
                
            }
            else if (tcNumber == 2)
            {
                timecodeSlider2.setValue(tcTrigger2/144.f);
                timeCodeLabel2.setColour(Label::textColourId,
                                         Colour::fromHSV(tcTrigger2/144.f*0.4+colourOffset, 1.f, 1.f, 1.f));
                tcTriggerLabel2.setColour(Label::textColourId,
                                          Colour::fromHSV(tcTrigger2/144.f*0.4+triggerLabelColourOffset, 1.f, 1.f, 1.f));
                timecodeSlider2.setColour(Slider::thumbColourId,
                                          Colour::fromHSV(tcTrigger2/144.f*0.4+colourOffset, 1.f, 1.f, 1.f));
                
            }
        }
        if (tcNumber == 1)
            return tcTrigger1;
        else if (tcNumber == 2)
            return tcTrigger2;
        else
            return 0;
    }
  
    string tcInputAddress1 = "/smptecontroller/smpte1";
    string tcInputAddress2 = "/smptecontroller/smpte2";
    
    
    Slider timecodeSlider1;
    Slider timecodeSlider2;
    Label timeCodeLabel1;
    Label timeCodeLabel2;
    Label tcTriggerLabel1;
    Label tcTriggerLabel2;
    TimecodeList timecodeList;
    OSCSender sender;
    
    Image smpte1image = ImageCache::getFromMemory (BinaryData::SMPTE1_png, BinaryData::SMPTE1_pngSize);
    Image smpte2image = ImageCache::getFromMemory (BinaryData::SMPTE2_png, BinaryData::SMPTE2_pngSize);
    
    float tcTrigger1;
    float tcTrigger2;
    
    LookAndFeel_V4 arenaLAF;
    Colour arenaBrightGreen = Colour::fromRGB(133,254,211);
    Colour arenaLessGreen = Colour::fromRGB(79, 139, 117);
    Colour arenaLessPink = Colour::fromRGB(145,84,144);
    Colour arenaTopGrey = Colour::fromRGB(58,58,57);
    Colour arenaMidGrey = Colour::fromRGB(42,42,42);
    Colour arenaBottomGrey = Colour::fromRGB(25,25,25);
    Colour arenaDeepGrey = Colour::fromRGB(15,15,15);
    
    /*
     print: /smptecontroller/smpte1 00:00:25.08
     print: /smptecontroller/smpte2 00:00:25.08
     */
    
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
