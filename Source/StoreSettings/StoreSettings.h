/*
  ==============================================================================

    StoreSettings.h
    Created: 24 Sep 2019 10:08:02am
    Author:  Sem Shimla

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class Settings
{
public:
    
    Settings ();
    ~Settings ();
    bool save ();
    void setUserPrefs (int buttonStateArrayA[],int buttonStateArrayB[]);
    
private:
    File getXmlFile ();
    ScopedPointer<XmlElement> settingsData;
    
};
