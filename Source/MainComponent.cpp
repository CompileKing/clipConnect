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
    
    timecodeSlider1.setRange(0.f, 1.f);
    timecodeSlider1.setSliderStyle(Slider::LinearHorizontal);
    timecodeSlider1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(timecodeSlider1);
    
    // OSC send connecter
    sender.connect("127.0.0.1", 7000);
    
    // OSC Receive connecter
    if (! connect(7002))
    {
        cout << "couldn't connect" << endl;
    }
    
    // add OSC listener
    // addListener(this, "/juce/knopjeReceive");
    
    addListener(this, "/fake/resolume/adress1");
    addListener(this, "/fake/resolume/adress2");
    
    // other juce stuff
    setSize (800, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    //g.fillAll (Colour::fromHSV(0.3f, 0.2f, 0.2, 1.f));
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
    timecodeSlider1.setBounds    ((getWidth()/2)-(objectSize/2),
                            (getHeight()/2)-(objectSize/2)+25,
                            objectSize, objectSize);
    
    
}
