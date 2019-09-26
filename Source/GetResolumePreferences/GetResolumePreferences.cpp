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
}

void GetResolumePreferences::parseInject()
{
    cout << "" << endl;
    cout << "//////////////////////////////////////////////////////////////" << endl;
    cout << "" << endl;
    File f = getXmlFile();
    if (f.exists())
    {
        injection->setAttribute ("name","OSCSMPTEOutEnabled");
        injection->setAttribute("default", 0);
        injection->setAttribute("value", 1);
        String injectionString = injection->toString();
        
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
                int attrCounter = 0;
                
                for (auto* thirdChild = secondChild->getFirstChildElement(); \
                     thirdChild != nullptr; \
                     thirdChild = thirdChild->getNextElement())
                {
                    String checkStorage = "storage";
                    if (thirdChild->getAttributeName(0)==checkStorage)
                    {
                        attrCounter++;
                    }
                }
                if (attrCounter == 5)
                {
                    secondChild->insertChildElement(injection, 6);
                    attrCounter = 0;
                }
            }
        }
        cout << loadedConfigXml->toString() << endl;
    }
    cout << "" << endl;
    cout << "//////////////////////////////////////////////////////////////" << endl;
    cout << "" << endl;
}

File GetResolumePreferences::getXmlFile ()
{
    //get the file config.xml from the users documents folder
    File appDir = File::getSpecialLocation(File::userDocumentsDirectory);
    File xmlFile = appDir.getChildFile("Resolume Arena 6/Preferences/config.xml");
    return xmlFile;
}

bool GetResolumePreferences::save ()
{
    //save everything into an XML file
    File file = getXmlFile();
    if (! file.exists() )
        file.create();
        
    if (loadedConfigXml->writeToFile(file, "") )
        return true;
    else
    {
        DBG("SAVE ERROR!");
        return false;
    }
}










