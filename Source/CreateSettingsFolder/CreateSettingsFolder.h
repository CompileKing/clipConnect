/*
  ==============================================================================

    CreateSettingsFolder.h
    Created: 1 Oct 2019 2:47:45pm
    Author:  Sem Shimla

  ==============================================================================
*/

#pragma once

#pragma once
#include "JuceHeader.h"

class SettingsFolder
{
public:
    
    SettingsFolder ();
    ~SettingsFolder ();
    bool save();
    bool firstTime = false;
    
private:
    File getXmlFile();
    ScopedPointer<XmlElement> settingsFolderData;
};
