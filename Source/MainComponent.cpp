/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
using namespace std;

//==============================================================================
MainComponent::MainComponent()
{
    

    // set timecode label
    timeCodeLabel.setFont(Font (130.f,Font::bold));
    timeCodeLabel.setText("00:00:00", dontSendNotification);
    timeCodeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(timeCodeLabel);
    
    currentColumn.setFont(Font(80.f,Font::bold));
    currentColumn.setText("currentColumn", dontSendNotification);
    currentColumn.setJustificationType(Justification::centred);
    addAndMakeVisible(currentColumn);
    
    // OSC send connecter
    sender.connect("127.0.0.1", 7000);
    
    // OSC Receive connecter
    if (! connect(7002))
    {
        cout << "couldn't connect" << endl;
    }
    
    // add OSC listener
    // addListener(this, "/juce/knopjeReceive");
    addListener(this, "/fake/resolume/adress");
    
    // other juce stuff
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    int objectSize = getWidth()-100;
    
    timeCodeLabel.setBounds((getWidth()/2)-(objectSize/2),
                            (getHeight()/2)-(objectSize/2)-50,
                            objectSize, objectSize);
    currentColumn.setBounds((getWidth()/2)-(objectSize/2),
                            (getHeight()/2)-(objectSize/2)+50,
                            objectSize, objectSize);
    
}
