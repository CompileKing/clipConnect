/*
  ==============================================================================

    CreateSettingsFolder.cpp
    Created: 1 Oct 2019 2:47:45pm
    Author:  Sem Shimla

  ==============================================================================
*/

#include "CreateSettingsFolder.h"


SettingsFolder::SettingsFolder()
{
    //defaults
    settingsFolderData = new XmlElement("SETTINGS");
}

SettingsFolder::~SettingsFolder()
{
    settingsFolderData = nullptr;
}

bool SettingsFolder::save()
{
    //save everything into an XML file
    File f = getXmlFile();
    if (! f.exists() )
    {
        firstTime = true;
        f.create();
        if (settingsFolderData->writeTo(f))
            return true;
        else
        {
            DBG("SAVE ERROR!");
            return false;
        }
    }
    else
        firstTime = false;
}

File SettingsFolder::getXmlFile()
{
    //get the file config.xml from the users documents folder
    File appDir = File::getSpecialLocation(File::userDocumentsDirectory);
    File xmlFile = appDir.getChildFile("PLC/ClipConnect/config.xml");
    return xmlFile;
}
