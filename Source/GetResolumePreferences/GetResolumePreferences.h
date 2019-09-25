/*
  ==============================================================================

    GetResolumePreferences.h
    Created: 24 Sep 2019 1:08:03pm
    Author:  Sem Shimla

  ==============================================================================
*/

#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"
using namespace std;

//==============================================================================
/*
*/
class GetResolumePreferences
{
public:
    
    GetResolumePreferences ();
    ~GetResolumePreferences ();
    bool save ();
    void load();
    XmlElement* createElementFromFile(File inputFile);
    
    
private:
    File getXmlFile ();
    ScopedPointer<XmlElement> configXML;
    std::unique_ptr<XmlElement> loadedConfigXml;
    
    
    
    
};
