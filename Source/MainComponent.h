/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TimecodeList/TimecodeList.h"
#include "StoreSettings/StoreSettings.h"
#include "GetResolumePreferences/GetResolumePreferences.h"



using namespace std;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public Component,
                        public Button::Listener,
                        public Slider::Listener,
                        private OSCReceiver,
                        private Timer,
                        private OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    
    void sliderValueChanged (Slider* slider) override
    {
    }
    
    void buttonLoad()
    {
        cout << "setToggleState: ";
        for ( int i = 0; i < layerButtonsA.size(); i++ )
        {
            layerButtonsA[i]->setToggleState(settings.feedbackArrayA[i], sendNotification);
            cout << to_string(settings.feedbackArrayA[i]);
            layerButtonsB[i]->setToggleState(settings.feedbackArrayB[i], sendNotification);
        }
    }
    
    void buttonClicked (Button* button) override
    {
        for ( int i = 0; i < layerButtonsA.size(); i++ )
        {
            if (button == layerButtonsA[i])
            {
                layerButtonsAstate[i] = layerButtonsA[i]->getToggleState();
            }
        }
        for ( int i = 0; i < layerButtonsB.size(); i++ )
        {
            if (button == layerButtonsB[i])
            {
                layerButtonsBstate[i] = layerButtonsB[i]->getToggleState();
            }
        }
        settings.setUserPrefs(layerButtonsAstate,layerButtonsBstate);
        settings.save();
    }

private:

    void oscMessageReceived (const OSCMessage& message) override
    {
        elapsed = 0.f;
        // /composition/layers/1/clips/1/connect
        string receivedAddress = message.getAddressPattern().toString().toStdString().c_str();
        {
            int value = tcTriggerCreator(message, receivedAddress, tcInputAddress1, 1);
            static int oldValue = value;
            if (value != oldValue)
            {
                for ( int i = 0; i < layerButtonsA.size(); i++ )
                {
                    if (layerButtonsAstate[i] == 1)
                    {
                        string tcOscOutA = "/composition/layers/" + to_string(i+1) + "/clips/" + to_string(value) + "/connect";
                        const char * tcOscOutAcharStar = tcOscOutA.c_str();
                        sender.send(tcOscOutAcharStar, 1);
                    }
                }
                oldValue = value;
            }
        }
        {
            int value = tcTriggerCreator(message, receivedAddress, tcInputAddress2, 2);
            static int oldValue = value;
            if (value != oldValue)
            {
                for ( int i = 0; i < layerButtonsB.size(); i++ )
                {
                    if (layerButtonsBstate[i] == 1)
                    {
                        string tcOscOutB = "/composition/layers/" + to_string(i+1) + "/clips/" + to_string(value) + "/connect";
                        const char * tcOscOutBcharStar = tcOscOutB.c_str();
                        sender.send(tcOscOutBcharStar, 1);
                    }
                }
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
                string oscMessageString = message[0].getString().toStdString();
                const char * str1 = oscMessageString.c_str();
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
            if (tcNumber == 1)
                timecodeSlider1.setValue(tcTrigger1/144.f);
            if (tcNumber == 2)
                timecodeSlider2.setValue(tcTrigger2/144.f);
            
            /*
            float triggerLabelColourOffset = 0.1;
            float colourOffset = 0.1;
            
            if (tcNumber == 1)
            {
                timeCodeLabel1.setColour(Label::textColourId,
                                         Colour::fromHSV(tcTrigger1/144.f*0.4+colourOffset, 1.f, 1.f, 1.f));
                tcTriggerLabel1.setColour(Label::textColourId,
                                         Colour::fromHSV(tcTrigger1/144.f*0.4+triggerLabelColourOffset, 1.f, 1.f, 1.f));
                timecodeSlider1.setColour(Slider::thumbColourId,
                                          Colour::fromHSV(tcTrigger1/144.f*0.4+colourOffset, 1.f, 1.f, 1.f));
            }
            else if (tcNumber == 2)
            {
                timeCodeLabel2.setColour(Label::textColourId,
                                         Colour::fromHSV(tcTrigger2/144.f*0.4+colourOffset, 1.f, 1.f, 1.f));
                 tcTriggerLabel2.setColour(Label::textColourId,
                                          Colour::fromHSV(tcTrigger2/144.f*0.4+triggerLabelColourOffset, 1.f, 1.f, 1.f));
                timecodeSlider2.setColour(Slider::thumbColourId,
                                          Colour::fromHSV(tcTrigger2/144.f*0.4+colourOffset, 1.f, 1.f, 1.f));
            }
            
            if (tcNumber == 1)
            {
                for ( int i = 0; i < layerButtonsA.size(); i++ )
                {
                    layerButtonsA[i]->setColour(TextButton::buttonOnColourId,
                                                Colour::fromHSV(tcTrigger1/144.f*0.4+colourOffset, 1.f, 1.f, 1.f));
                }
            }
            else if (tcNumber == 2)
            {
                for ( int i = 0; i < layerButtonsB.size(); i++ )
                {
                    layerButtonsB[i]->setColour(TextButton::buttonOnColourId,
                                                Colour::fromHSV(tcTrigger2/144.f*0.4+colourOffset, 1.f, 1.f, 1.f));
                }
            }
             */
        }
        
        if (tcNumber == 1)
            return tcTrigger1;
        else if (tcNumber == 2)
            return tcTrigger2;
        else
            return 0;
    }
    

    void timerCallback() override
    {
        //repaint();
        elapsed += 0.025f;
        String juceTimerLabelText = to_string(elapsed);
        
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
    
    int xOffset = -40;
    int yOffset = -55;
    
    float tcTrigger1;
    float tcTrigger2;
    float elapsed = 0.0f;
    float realtime = 0.0f;
    
    int layerButtonsAstate[16] {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int layerButtonsBstate[16] {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    LookAndFeel_V4 arenaLAF;
    LookAndFeel_V3 LAFvar;

    Colour arenaBrightGreen = Colour::fromRGB(133,254,211);
    Colour arenaLessGreen = Colour::fromRGB(79, 139, 117);
    Colour arenaLessPink = Colour::fromRGB(145,84,144);
    Colour arenaTopGrey = Colour::fromRGB(58,58,57);
    Colour arenaMidGrey = Colour::fromRGB(42,42,42);
    Colour arenaBottomGrey = Colour::fromRGB(25,25,25);
    Colour arenaDeepGrey = Colour::fromRGB(15,15,15);
    Colour brightOrange = Colour::  Colour::fromRGB(255, 160, 11);
    Colour backgroundGrey = Colour::fromRGB(43, 46, 46);
    Colour startColour = brightOrange;//Colour::fromHSV(0.f, 0.f, 1.f, 0.9);
    
    OwnedArray<TextButton> layerButtonsA;
    OwnedArray<TextButton> layerButtonsB;
    
    Settings settings;
    GetResolumePreferences getPrefRes6;
    GetResolumePreferences getPrefRes7;
    
    ComponentDragger dragger;

    /*
     print: /smptecontroller/smpte1 00:00:25.08
     print: /smptecontroller/smpte2 00:00:25.08
     */

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
