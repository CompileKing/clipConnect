/*
  ==============================================================================

    StoreSettings.cpp
    Created: 24 Sep 2019 10:08:02am
    Author:  Sem Shimla

  ==============================================================================
*/

#include "StoreSettings.h"

Settings::Settings()
{
    //defaults
    settingsData = new XmlElement("SETTINGS");
}

Settings::~Settings()
{
    settingsData = nullptr;
}

void Settings::setUserPrefs(int buttonStateArrayA[],int buttonStateArrayB[])
{
    //out with the old
    settingsData->deleteAllChildElementsWithTagName( "UserPreferences") ;
    //in with the new
    XmlElement* userPrefs = new XmlElement("UserPreferences");
    
    String buttonStateAString = "";
    for (int i=0;i<16;i++)
    {
        buttonStateAString += buttonStateArrayA[i];
    }
    XmlElement* buttonStateAelement = new XmlElement ("ButtonStateA");
    buttonStateAelement->setAttribute("ButtonStateA", buttonStateAString);
    userPrefs->addChildElement( buttonStateAelement );
    
    String buttonStateBString = "";
    for (int i=0;i<16;i++)
    {
        buttonStateBString += buttonStateArrayB[i];
    }
    XmlElement* buttonStateBelement = new XmlElement ("ButtonStateB");
    buttonStateBelement->setAttribute("ButtonStateB", buttonStateBString);
    userPrefs->addChildElement( buttonStateBelement );

    settingsData->addChildElement( userPrefs );
}

bool Settings::save ()
{
    //save everything into an XML file
    File f = getXmlFile();
    if (! f.exists() )
        f.create();
    
    if (settingsData->writeToFile(f, "") )
        return true;
    else
    {
        DBG("SAVE ERROR!");
        return false;
    }
}

File Settings::getXmlFile ()
{
    //get the file config.xml from the users documents folder
    File appDir = File::getSpecialLocation(File::userDocumentsDirectory);
    File xmlFile = appDir.getChildFile("PLC/ClipConnect/config.xml");
    return xmlFile;
}

