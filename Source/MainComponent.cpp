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
    float timecodeLabelSize = 100;
    float triggerLabelSize = 200;

    startTimerHz (30);
    // set timecode label
    timeCodeLabel1.setFont(Font ("Monaco", timecodeLabelSize/2.f, 0));
    timeCodeLabel1.setText("00:00:00:00", dontSendNotification);
    timeCodeLabel1.setJustificationType(Justification::centred);
    addAndMakeVisible(timeCodeLabel1);

    // set tcTriggerLabel1 label
    tcTriggerLabel1.setFont(Font ("Monaco", triggerLabelSize/2.f, 0));
    tcTriggerLabel1.setText("0", dontSendNotification);
    tcTriggerLabel1.setJustificationType(Justification::centred);
    addAndMakeVisible(tcTriggerLabel1);
    
    //set timecode slider1
    timecodeSlider1.setRange(0.f, 1.f);
    timecodeSlider1.setSliderStyle(Slider::LinearHorizontal);
    timecodeSlider1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    timecodeSlider1.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(timecodeSlider1);
    
    ///////////////////////////////////////////////////////////////////////

    // set timecode label2
    timeCodeLabel2.setFont(Font ("Monaco", timecodeLabelSize/2.f, 0));
    timeCodeLabel2.setText("00:00:00:00", dontSendNotification);
    timeCodeLabel2.setJustificationType(Justification::centred);
    addAndMakeVisible(timeCodeLabel2);
    
    // set tcTriggerLabel label2
    tcTriggerLabel2.setFont(Font ("Monaco", triggerLabelSize/2.f, 0));
    tcTriggerLabel2.setText("0", dontSendNotification);
    tcTriggerLabel2.setJustificationType(Justification::centred);
    addAndMakeVisible(tcTriggerLabel2);
    
    //set timecode slider1
    timecodeSlider2.setRange(0.f, 1.f);
    timecodeSlider2.setSliderStyle(Slider::LinearHorizontal);
    timecodeSlider2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    timecodeSlider2.setScrollWheelEnabled(false);
    timecodeSlider2.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(timecodeSlider2);
    
    ///////////////////////////////////////////////////////////////////////
                
    for(int i = 0; i < 16; i++)
    {
        TextButton* layer = new TextButton();
        layer->setClickingTogglesState(true);
        layer->addListener(this);
        addAndMakeVisible(layer);
        layerButtonsA.add(layer);
        
    }
    
    for(int i = 0; i < 16; i++)
    {
        TextButton* layer = new TextButton();
        layer->setClickingTogglesState(true);
        layer->addListener(this);
        addAndMakeVisible(layer);
        layerButtonsB.add(layer);
    }
     
    for ( int i = 0; i < layerButtonsA.size(); i++ )
    {
        string buttonLabel = to_string(i+1);
        layerButtonsA[i]->setColour(TextButton::buttonColourId,arenaMidGrey.withAlpha(0.4f));
        layerButtonsA[i]->setColour(TextButton::buttonOnColourId,brightOrange);
        layerButtonsA[i]->setColour(TextButton::textColourOnId,arenaBottomGrey);
        layerButtonsA[i]->setColour(TextButton::textColourOffId,Colours::white);
        layerButtonsA[i]->setButtonText(buttonLabel);
        layerButtonsA[i]->setLookAndFeel(&LAFvar);
        
        layerButtonsB[i]->setColour(TextButton::buttonColourId,arenaMidGrey.withAlpha(0.4f));
        layerButtonsB[i]->setColour(TextButton::buttonOnColourId,brightOrange);
        layerButtonsB[i]->setColour(TextButton::textColourOnId,arenaBottomGrey);
        layerButtonsB[i]->setColour(TextButton::textColourOffId,Colours::white);
        layerButtonsB[i]->setButtonText(buttonLabel);
        layerButtonsB[i]->setLookAndFeel(&LAFvar);
    }
    
    // OSC send connecter
    sender.connect("127.0.0.1", 7000);
    
    // OSC Receive connecter
    if (! connect(7002))
    {
        cout << "couldn't connect" << endl;
    }

    addListener(this, tcInputAddress1.c_str());
    addListener(this, tcInputAddress2.c_str());
    
    setSize (1030, 160);
    
    getPref.parseInject();
    getPref.save();
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //g.fillAll(backgroundGrey);
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour(Colour::fromRGBA(0, 0, 0, 80));
    g.drawLine(getWidth()/2.f, 0, getWidth()/2.f, getHeight(),5.f);
    
    int yOffset = -50;
    int xOffset = -40;
    int imageOffset = 32;
    int imageXoffset = -180;
    int objectSize = 60;
    int edgeDistance = getWidth()/4;

    Rectangle<float> smpteImageRect1 ((getWidth()/2)-(objectSize/2)-(getWidth()/2.f)+edgeDistance+xOffset+imageXoffset,
                                    (getHeight()/2)-(objectSize/2)+yOffset+imageOffset,
                                    objectSize,
                                    objectSize);
    g.setColour(Colour::fromRGBA(0, 0, 0, 255)); //abs(sin(elapsed))*255
    g.drawImage(smpte1image, smpteImageRect1);
    
    Rectangle<float> smpteImageRect2 ((getWidth()/2)-(objectSize/2)+(getWidth()/2.f)-edgeDistance+xOffset+imageXoffset,
                                      (getHeight()/2)-(objectSize/2)+yOffset+imageOffset,
                                      objectSize,
                                      objectSize);
    g.drawImage(smpte2image, smpteImageRect2);
}

void MainComponent::resized()
{
    int yOffset = -50;
    int xOffset = -40;
    int timecodeLabelOffset = 20;
    int triggerLabelOffset = 33;
    int triggerLabelXOffset = 210;
    int timecodeSliderOffset = 60;
    int objectSize = getWidth()-320;
    int edgeDistance = getWidth()/4;
    int sliderSize = 280;
        
    timeCodeLabel1.setBounds    ((getWidth()/2)-(objectSize/2)-(getWidth()/2.f)+edgeDistance+xOffset,
                                (getHeight()/2)-(objectSize/2)+yOffset+timecodeLabelOffset,
                                objectSize, objectSize);
    
    tcTriggerLabel1.setBounds   ((getWidth()/2)-(objectSize/2)-(getWidth()/2.f)+edgeDistance+xOffset+triggerLabelXOffset,
                                (getHeight()/2)-(objectSize/2)+yOffset+triggerLabelOffset,
                                objectSize, objectSize);
    
    timecodeSlider1.setBounds   ((getWidth()/2)-(sliderSize/2)-(getWidth()/2.f)+edgeDistance+xOffset,
                                (getHeight()/2)-(sliderSize/2)+yOffset+timecodeSliderOffset,
                                sliderSize, sliderSize);
    
    ///////////////////////////////////////////////////////////////////////
        
    timeCodeLabel2.setBounds    ((getWidth()/2)-(objectSize/2)+(getWidth()/2.f)-edgeDistance+xOffset,
                                (getHeight()/2)-(objectSize/2)+yOffset+timecodeLabelOffset,
                                objectSize, objectSize);
    tcTriggerLabel2.setBounds   ((getWidth()/2)-(objectSize/2)+(getWidth()/2.f)-edgeDistance+xOffset+triggerLabelXOffset,
                                (getHeight()/2)-(objectSize/2)+yOffset+triggerLabelOffset,
                                objectSize, objectSize);
    
    timecodeSlider2.setBounds   ((getWidth()/2)-(sliderSize/2)+(getWidth()/2.f)-edgeDistance+xOffset,
                                (getHeight()/2)-(sliderSize/2)+yOffset+timecodeSliderOffset,
                                sliderSize, sliderSize);
    
    ///////////////////////////////////////////////////////////////////////

    int size = 30;
    int x = getWidth()/4-200;
    int x2 = getWidth()/4*3-200;
    int y = getHeight()/2+80;

    for ( int i = 0; i < layerButtonsA.size(); i ++)
    {
        layerButtonsA[i]->setBounds(x + i * size + xOffset,y + yOffset, size, size);
        layerButtonsB[i]->setBounds(x2 + i * size + xOffset,y + yOffset, size, size);
    }
}
