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
    timeCodeLabel1.setFont(Font ("Monaco", 130.f/2.f, 0));
    timeCodeLabel1.setText("00:00:00", dontSendNotification);
    timeCodeLabel1.setJustificationType(Justification::centred);
    addAndMakeVisible(timeCodeLabel1);
    
    // set tcTriggerLabel1 label
    tcTriggerLabel1.setFont(Font ("Monaco", 58.f/2.f, 0));
    tcTriggerLabel1.setText("tcTriggerLabel1", dontSendNotification);
    tcTriggerLabel1.setJustificationType(Justification::centred);
    addAndMakeVisible(tcTriggerLabel1);
    
    //set timecode slider1
    timecodeSlider1.setRange(0.f, 1.f);
    timecodeSlider1.setSliderStyle(Slider::LinearHorizontal);
    timecodeSlider1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(timecodeSlider1);
    
    ///////////////////////////////////////////////////////////////////////
    
    // set timecode label2
    timeCodeLabel2.setFont(Font ("Monaco", 130.f/2.f, 0));
    timeCodeLabel2.setText("00:00:00", dontSendNotification);
    timeCodeLabel2.setJustificationType(Justification::centred);
    addAndMakeVisible(timeCodeLabel2);
    
    // set tcTriggerLabel label2
    tcTriggerLabel2.setFont(Font ("Monaco", 58.f/2.f, 0));
    tcTriggerLabel2.setText("tcTriggerLabel2", dontSendNotification);
    tcTriggerLabel2.setJustificationType(Justification::centred);
    addAndMakeVisible(tcTriggerLabel2);
    
    //set timecode slider1
    timecodeSlider2.setRange(0.f, 1.f);
    timecodeSlider2.setSliderStyle(Slider::LinearHorizontal);
    timecodeSlider2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(timecodeSlider2);
    
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
    setSize (900, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour(Colours::black);
    g.drawLine(getWidth()/2.f, 0, getWidth()/2.f, getHeight());
    //g.fillAll (Colour::fromHSV(0.3f, 0.2f, 0.2, 1.f));
}

void MainComponent::resized()
{
    int distance = 50;
    int objectSize = getWidth()-320;
    int sliderSize = getWidth()/4;
    int edgeDistance = getWidth()/4;
    
    timeCodeLabel1.setBounds    ((getWidth()/2)-(objectSize/2)-(getWidth()/2.f)+edgeDistance,
                                (getHeight()/2)-(objectSize/2)-distance,
                                objectSize, objectSize);
    
    tcTriggerLabel1.setBounds   ((getWidth()/2)-(objectSize/2)-(getWidth()/2.f)+edgeDistance,
                                (getHeight()/2)-(objectSize/2)+100,
                                objectSize, objectSize);
    
    timecodeSlider1.setBounds   ((getWidth()/2)-(sliderSize/2)-(getWidth()/2.f)+edgeDistance,
                                (getHeight()/2)-(sliderSize/2)+25,
                                sliderSize, sliderSize);
    
 
    ////////////////////////////////////////////////////////////////////////////////////////
    
 
    timeCodeLabel2.setBounds    ((getWidth()/2)-(objectSize/2)+(getWidth()/2.f)-edgeDistance,
                                (getHeight()/2)-(objectSize/2)-distance,
                                objectSize, objectSize);
    tcTriggerLabel2.setBounds   ((getWidth()/2)-(objectSize/2)+(getWidth()/2.f)-edgeDistance,
                                (getHeight()/2)-(objectSize/2)+100,
                                objectSize, objectSize);
    
    timecodeSlider2.setBounds   ((getWidth()/2)-(sliderSize/2)+(getWidth()/2.f)-edgeDistance,
                                (getHeight()/2)-(sliderSize/2)+25,
                                sliderSize, sliderSize);
    
    repaint();
     
    
    
}
