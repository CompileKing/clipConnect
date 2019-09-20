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
    timeCodeLabel.setText("TIMECODE LABEL", dontSendNotification);
    timeCodeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(timeCodeLabel);
    
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
    
    timeCodeLabel.setBounds((getWidth()/2)-(objectSize/2), (getHeight()/2)-(objectSize/2), objectSize, objectSize);
}
