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
    //loadedConfigXml = new XmlElement("SETTINGS");
}

GetResolumePreferences::~GetResolumePreferences()
{
    loadedConfigXml = nullptr;
    injection = nullptr;
}

void GetResolumePreferences::parseInject(int versionNumber)
{
    cout << "" << endl;
    cout << "//////////////////////////////////////////////////////////////" << endl;
    cout << "" << endl;
    File f = getXmlFile(versionNumber);
    if (f.exists())
    {
        injection->setAttribute ("name","OSCSMPTEOutEnabled");
        injection->setAttribute("default", 0);
        injection->setAttribute("value", 1);
        
        // <Param name="OSCSMPTEOutEnabled" default="0" value="1"/>
        loadedConfigXml = juce::parseXML (f);
        
        for (auto* childElementVariableName = loadedConfigXml->getChildByName("Application"); \
             childElementVariableName != nullptr; \
             childElementVariableName = childElementVariableName->getNextElementWithTagName ("Application"))
        {
            for (auto* secondChild = childElementVariableName->getChildByName ("Params"); \
                 secondChild != nullptr; \
                 secondChild = secondChild->getNextElementWithTagName ("Params"))
            {
                bool injectSwitch = false;
                for (auto* thirdChild = secondChild->getFirstChildElement(); \
                     thirdChild != nullptr; \
                     thirdChild = thirdChild->getNextElement())
                {
                    //<Param name="DefaultColumnCount" default="8" value="8"/>
                    String injectTag = "DefaultColumnCount";
                    
                    if (thirdChild->getAttributeValue(1) == injectTag)
                        injectSwitch = true;

                    if (thirdChild->getAttributeValue(0) == injectTag)
                        injectSwitch = true;
                }
                if (injectSwitch == true)
                {
                    secondChild->insertChildElement(injection, 6);
                    injectSwitch = false;
                }
            }
        }
        // cout << loadedConfigXml->toString() << endl;
    }
    loadedConfigXml->writeTo(f);
    
    cout << "" << endl;
    cout << "//////////////////////////////////////////////////////////////" << endl;
    cout << "" << endl;
}

File GetResolumePreferences::getXmlFile (int versionNumber)
{
    //get the file config.xml from the users documents folder
    File appDir = File::getSpecialLocation(File::userDocumentsDirectory);
    File xmlFile;
    if (versionNumber == 6)
    {
        xmlFile = appDir.getChildFile("Resolume Arena 6/Preferences/config.xml");
    }
    if (versionNumber == 7)
    {
        xmlFile = appDir.getChildFile("Resolume Arena/Preferences/config.xml");
    }
    return xmlFile;
    
}












