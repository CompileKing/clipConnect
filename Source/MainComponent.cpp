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
    
    /*
    // setKnob
    testSlider.setRange(0.f, 1.f);
    testSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    testSlider.addListener(this);
    addAndMakeVisible(testSlider);
     */
    
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
    /*
    testSlider.setBounds((getWidth()/2)-(sliderSize/2), (getHeight()/2)-(sliderSize/2), sliderSize, sliderSize);
    testSlider.setTextBoxStyle(Slider::TextBoxBelow, true, sliderSize*0.6, 30);
     */
    timeCodeLabel.setBounds((getWidth()/2)-(objectSize/2), (getHeight()/2)-(objectSize/2), objectSize, objectSize);
}
