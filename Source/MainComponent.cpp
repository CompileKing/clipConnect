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
    timeCodeLabel.setFont(Font ("Monaco", 130.f, 0));
    timeCodeLabel.setText("00:00:00", dontSendNotification);
    timeCodeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(timeCodeLabel);
    
    // set currentColumn label
    currentColumn.setFont(Font ("Monaco", 58.f, 0));
    currentColumn.setText("currentColumn", dontSendNotification);
    currentColumn.setJustificationType(Justification::centred);
    addAndMakeVisible(currentColumn);
    
    testSlider.setRange(0.f, 1.f);
    testSlider.setSliderStyle(Slider::LinearHorizontal);
    testSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(testSlider);
    
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
    int distance = 50;
    int objectSize = getWidth()-200;
    
    timeCodeLabel.setBounds ((getWidth()/2)-(objectSize/2),
                            (getHeight()/2)-(objectSize/2)-distance,
                            objectSize, objectSize);
    currentColumn.setBounds ((getWidth()/2)-(objectSize/2),
                            (getHeight()/2)-(objectSize/2)+100,
                            objectSize, objectSize);
    testSlider.setBounds    ((getWidth()/2)-(objectSize/2),
                            (getHeight()/2)-(objectSize/2)+25,
                            objectSize, objectSize);
    
    
}
