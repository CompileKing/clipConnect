/*
  ==============================================================================

    GetResolumePreferences.cpp
    Created: 24 Sep 2019 1:08:03pm
    Author:  Sem Shimla

  ==============================================================================
*/


#include "GetResolumePreferences.h"

GetResolumePreferences::GetResolumePreferences()
{
    //defaults
    configXML = new XmlElement("SETTINGS");
}

GetResolumePreferences::~GetResolumePreferences()
{
    configXML = nullptr;
}

void GetResolumePreferences::load()
{

}

bool GetResolumePreferences::save ()
{
    //save everything into an XML file
    File file = getXmlFile();
    if (! file.exists() )
        file.create();
    
    
    if (configXML->writeToFile(file, "") )
        return true;
    else
    {
        DBG("SAVE ERROR!");
        return false;
    }
}

File GetResolumePreferences::getXmlFile ()
{
    //get the file config.xml from the users documents folder
    File appDir = File::getSpecialLocation(File::userDocumentsDirectory);
    File xmlFile = appDir.getChildFile("Resolume Arena 6/Preferences/config.xml");
    return xmlFile;
}






