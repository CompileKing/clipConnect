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

}

Settings::~Settings()
{
    settingsData = nullptr;
}

void Settings::loadParseSettings()
{
    File loadedXML = getXmlFile();
    if (loadedXML.exists())
    {
        settingsData = juce::parseXML (loadedXML);
        
        indexFeedbackA = 0;
        indexFeedbackB = 0;
        
        for (auto* settingsElement = settingsData->getFirstChildElement(); \
             settingsElement != nullptr; \
             settingsElement = settingsElement->getNextElement())
        {
            for (auto* buttonElement = settingsElement->getChildByName("buttonA"); \
                 buttonElement != nullptr; \
                 buttonElement = buttonElement->getNextElementWithTagName("buttonA"))
            {
                feedbackArrayA[indexFeedbackA] = buttonElement->getAttributeValue(0).getIntValue();
                indexFeedbackA++;
            }
            for (auto* buttonElement = settingsElement->getChildByName("buttonB"); \
                 buttonElement != nullptr; \
                 buttonElement = buttonElement->getNextElementWithTagName("buttonB"))
            {
                feedbackArrayB[indexFeedbackB] = buttonElement->getAttributeValue(0).getIntValue();
                indexFeedbackB++;
            }
        }
        
        for (auto* portElement = settingsData->getChildByName("userPort"); \
        portElement != nullptr; \
        portElement = portElement->getNextElementWithTagName("userPort"))
        {
            int portInt = portElement->getAttributeValue(0).getIntValue();
            storedUserPort = portInt;
        }
    }
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
        XmlElement* buttonElement = new XmlElement("buttonA");
        String buttonIndex = "button" + to_string(i);
        buttonElement->setAttribute(buttonIndex, buttonStateArrayA[i]);
        userPrefs->addChildElement(buttonElement);
    }

    String buttonStateBString = "";
    for (int i=0;i<16;i++)
    {
        XmlElement* buttonElement = new XmlElement("buttonB");
        String buttonIndex = "button" + to_string(i);
        buttonElement->setAttribute(buttonIndex, buttonStateArrayB[i]);
        userPrefs->addChildElement(buttonElement);
    }
    settingsData->addChildElement( userPrefs );
}

void Settings::setUserPort(int port)
{
    settingsData->deleteAllChildElementsWithTagName( "userPort") ;
    XmlElement* portNumber = new XmlElement("userPort");
    String portString = "portNumber";
    portNumber->setAttribute(portString, to_string(port));
    settingsData->addChildElement(portNumber);
}

bool Settings::save ()
{
    File f = getXmlFile();
    if (! f.exists() )
        f.create();
    
    if (settingsData->writeTo(f))
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

