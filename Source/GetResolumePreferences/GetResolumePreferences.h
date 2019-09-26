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
    void parseInject();
    XmlElement* createElementFromFile(File inputFile);
    
protected:
    String getElementName( XmlElement* element );
    
    
private:
    File getXmlFile ();
    std::unique_ptr<XmlElement> loadedConfigXml;
    XmlElement* injection = new XmlElement ("Param");
    
    
    
    
};
