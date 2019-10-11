/*
  ==============================================================================

    StoreSettings.h
    Created: 24 Sep 2019 10:08:02am
    Author:  Sem Shimla

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
using namespace std;

class Settings
{
public:
    
    Settings ();
    ~Settings ();
    bool save ();
    void loadParseSettings ();
    void setUserPrefs (int buttonStateArrayA[],int buttonStateArrayB[]);
    void setUserPort (int port);
    int storedUserPort;
    int feedbackArrayA[100];
    int feedbackArrayB[100];
    int indexFeedbackA;
    int indexFeedbackB;
    
private:
    File getXmlFile ();
    std::unique_ptr<XmlElement> settingsData;
    
    
};
