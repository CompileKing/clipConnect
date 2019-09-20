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
    
    testSlider.setRange(0.f, 1.f);
    testSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    testSlider.addListener(this);
    addAndMakeVisible(testSlider);
    
    sender.connect("127.0.0.1", 7002);
    
    if (! connect(7000))
    {
        cout << "couldn't connect" << endl;
    }
    addListener(this, "/juce/knopjeReceive");
    
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
    int sliderSize = 200;
    testSlider.setBounds((getWidth()/2)-(sliderSize/2), (getHeight()/2)-(sliderSize/2), sliderSize, sliderSize);
    testSlider.setTextBoxStyle(Slider::TextBoxBelow, true, sliderSize*0.6, 30);
}
