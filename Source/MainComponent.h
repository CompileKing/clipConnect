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
#include "CreateSettingsFolder/CreateSettingsFolder.h"



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
                        private MultiTimer,
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
        for ( int i = 0; i < layerButtonsA.size(); i++ )
        {
            layerButtonsA[i]->setToggleState(settings.feedbackArrayA[i], sendNotification);
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
    
    void timerCallback(int timerId) override
    {
        if (timerId == 1)
        {
            elapsed1 += 0.025f;
            if (elapsed1 > 2.f && !sendTriggerA)
            {
                sendTriggerA = true;
            }
            elapsed2 += 0.025f;
            if (elapsed2 > 2.f && !sendTriggerB)
            {
                sendTriggerB = true;
            }
        }
    }

    void oscMessageReceived (const OSCMessage& message) override
    {
        receivedAddress = message.getAddressPattern().toString().toStdString();
        if (receivedAddress == tcInputAddress1)
        {
            triggerSender(message[0].getString().toStdString(), sendTriggerA, 1);
            elapsed1 = 0.f;
            sendTriggerA = false;
        }
        if (receivedAddress == tcInputAddress2)
        {
            triggerSender(message[0].getString().toStdString(), sendTriggerB, 2);
            elapsed2 = 0.f;
            sendTriggerB = false;
        }
    }
    
    void triggerSender(string message, bool sendAgain, int tcNumber )
    {
        if (tcNumber == 1)
        {
            int value = tcTriggerCreator(message, 1);
            static int oldValue = value;
            if (value != oldValue || sendAgain)
            {
                
                for ( int i = 0; i < layerButtonsA.size(); i++ )
                {
                    if (layerButtonsAstate[i] == 1)
                    {
                        string tcOscOut = "/composition/layers/" + to_string(i+1) + "/clips/" + to_string(value) + "/connect";
                        const char * tcOscOutCharStar = tcOscOut.c_str();
                        sender.send(tcOscOutCharStar, 1);
                    }
                }
                
                oldValue = value;
            }
        }
        
        if (tcNumber == 2)
        {
            int value = tcTriggerCreator(message, 2);
            static int oldValue = value;
            if (value != oldValue || sendAgain)
            {
                
                for ( int i = 0; i < layerButtonsB.size(); i++ )
                {
                    if (layerButtonsBstate[i] == 1)
                    {
                        string tcOscOut = "/composition/layers/" + to_string(i+1) + "/clips/" + to_string(value) + "/connect";
                        const char * tcOscOutCharStar = tcOscOut.c_str();
                        sender.send(tcOscOutCharStar, 1);
                    }
                }
                oldValue = value;
            }
        }
    }
    
    int tcTriggerCreator(const string message,int tcNumber)
    {
        if (tcNumber == 1)
            timeCodeLabel1.setText(message, dontSendNotification);
        else if (tcNumber == 2)
            timeCodeLabel2.setText(message, dontSendNotification);
        
            for (int i=0;i<144;i++)
            {
                string oscMessageString = message;
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
                    
        if (tcNumber == 1)
            return tcTrigger1;
        else if (tcNumber == 2)
            return tcTrigger2;
        else
            return 0;
    }
            
    string tcInputAddress1 = "/smptecontroller/smpte1";
    string tcInputAddress2 = "/smptecontroller/smpte2";
    string receivedMessage = to_string(42);
    string receivedAddress = "/oh/hi/there";
    
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
    float elapsed1 = 0.0f;
    float elapsed2 = 0.0f;
    float realtime = 0.0f;
    
    bool sendTriggerA = false;
    bool sendTriggerB = false;
    
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
    
    SettingsFolder settingsFolder;
    Settings settings;
    
    GetResolumePreferences getPrefRes6;
    GetResolumePreferences getPrefRes7;

    ComponentDragger dragger;
    
    String firstTimeString = "Hi! because this is your first time using ClipConnect you need to make sure you start ClipConnect BEFORE you start Resolume in order for both programs to sync properly. \n\nPlease close both Resolume and ClipConnect and open ClipConnect first. Then Resolume. \n\nThis is only important the first time you run ClipConnect. After you've done it the first time it doesn't matter which program you start first :) \nEnjoy!";

    /*
     print: /smptecontroller/smpte1 00:00:25.08
     print: /smptecontroller/smpte2 00:00:25.08
     */

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
