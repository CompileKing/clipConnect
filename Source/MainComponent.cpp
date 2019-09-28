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
    settings.loadParseFeedA();
    float timecodeLabelSize = 100;
    float triggerLabelSize = 200;

    startTimerHz (30);
    // set timecode label
    timeCodeLabel1.setFont(Font ("Monaco", timecodeLabelSize/2.f, 0));
    timeCodeLabel1.setText("00:00:00:00", dontSendNotification);
    timeCodeLabel1.setJustificationType(Justification::centred);
    timeCodeLabel1.setColour(Label::textColourId, startColour);
    addAndMakeVisible(timeCodeLabel1);

    // set tcTriggerLabel1 label
    tcTriggerLabel1.setFont(Font ("Monaco", triggerLabelSize/2.f, 0));
    tcTriggerLabel1.setText("0", dontSendNotification);
    tcTriggerLabel1.setJustificationType(Justification::centred);
    tcTriggerLabel1.setColour(Label::textColourId, startColour);
    addAndMakeVisible(tcTriggerLabel1);
    
    //set timecode slider1
    timecodeSlider1.setRange(0.f, 1.f);
    timecodeSlider1.setSliderStyle(Slider::LinearHorizontal);
    timecodeSlider1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    timecodeSlider1.setInterceptsMouseClicks(false, false);
    timecodeSlider1.setColour(Slider::thumbColourId, startColour);
    timecodeSlider1.setColour(Slider::trackColourId , brightOrange);
    timecodeSlider1.setColour(Slider::backgroundColourId , arenaBottomGrey);
    addAndMakeVisible(timecodeSlider1);
    
    ///////////////////////////////////////////////////////////////////////

    // set timecode label2
    timeCodeLabel2.setFont(Font ("Monaco", timecodeLabelSize/2.f, 0));
    timeCodeLabel2.setText("00:00:00:00", dontSendNotification);
    timeCodeLabel2.setJustificationType(Justification::centred);
    timeCodeLabel2.setColour(Label::textColourId, startColour);
    addAndMakeVisible(timeCodeLabel2);
    
    // set tcTriggerLabel label2
    tcTriggerLabel2.setFont(Font ("Monaco", triggerLabelSize/2.f, 0));
    tcTriggerLabel2.setText("0", dontSendNotification);
    tcTriggerLabel2.setJustificationType(Justification::centred);
    tcTriggerLabel2.setColour(Label::textColourId, startColour);
    addAndMakeVisible(tcTriggerLabel2);
    
    //set timecode slider1
    timecodeSlider2.setRange(0.f, 1.f);
    timecodeSlider2.setSliderStyle(Slider::LinearHorizontal);
    timecodeSlider2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    timecodeSlider2.setScrollWheelEnabled(false);
    timecodeSlider2.setInterceptsMouseClicks(false, false);
    timecodeSlider2.setColour(Slider::thumbColourId, startColour);
    timecodeSlider2.setColour(Slider::trackColourId , brightOrange);
    timecodeSlider2.setColour(Slider::backgroundColourId , arenaBottomGrey);
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
        layerButtonsA[i]->setColour(TextButton::buttonOnColourId,startColour);
        layerButtonsA[i]->setColour(TextButton::textColourOnId,arenaBottomGrey);
        layerButtonsA[i]->setColour(TextButton::textColourOffId,Colours::white);
        layerButtonsA[i]->setButtonText(buttonLabel);
        layerButtonsA[i]->setLookAndFeel(&LAFvar);
        
        layerButtonsB[i]->setColour(TextButton::buttonColourId,arenaMidGrey.withAlpha(0.4f));
        layerButtonsB[i]->setColour(TextButton::buttonOnColourId,startColour);
        layerButtonsB[i]->setColour(TextButton::textColourOnId,arenaBottomGrey);
        layerButtonsB[i]->setColour(TextButton::textColourOffId,Colours::white);
        layerButtonsB[i]->setButtonText(buttonLabel);
        layerButtonsB[i]->setLookAndFeel(&LAFvar);
    }
    
    // OSC send connecter
    sender.connect("127.0.0.1", 7000);
    
    // OSC Receive connecter
    if (! connect(7001))
    {
        cout << "couldn't connect" << endl;
    }

    addListener(this, tcInputAddress1.c_str());
    addListener(this, tcInputAddress2.c_str());
    
    setSize (1030, 160);
    addToDesktop(ComponentPeer::windowIsTemporary);
    setVisible(false);
    setAlwaysOnTop( true );
    
    getPrefRes6.parseInject(6);
    getPrefRes7.parseInject(7);
    
    buttonLoad();
    
}

MainComponent::~MainComponent()
{
    for ( int i = 0; i < layerButtonsA.size(); i++ )
    {
        layerButtonsA[i]->deleteAllChildren();
        layerButtonsB[i]->deleteAllChildren();
    }
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll(backgroundGrey);
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour(Colour::fromRGBA(0, 0, 0, 80));
    g.drawLine(getWidth()/2.f, 0, getWidth()/2.f, getHeight(),5.f);
    
    int imageXoffset = -176;
    int imageYoffset = 32;
    int objectSize = 50;
    int edgeDistance = getWidth()/4;
    
    g.setColour(startColour);

    Rectangle<float> smpteImageRect1 ((getWidth()/2)-(objectSize/2)-(getWidth()/2.f)+edgeDistance+xOffset+imageXoffset,
                                    (getHeight()/2)-(objectSize/2)+yOffset+imageYoffset,
                                    objectSize,
                                    objectSize);
    g.drawImage(smpte1image, smpteImageRect1);
    
    Rectangle<float> smpteImageRect2 ((getWidth()/2)-(objectSize/2)+(getWidth()/2.f)-edgeDistance+xOffset+imageXoffset,
                                      (getHeight()/2)-(objectSize/2)+yOffset+imageYoffset,
                                      objectSize,
                                      objectSize);
    g.drawImage(smpte2image, smpteImageRect2);
}

void MainComponent::resized()
{
    
    
    int timecodeLabelYoffset = 20;
    int triggerLabelXoffset = 210;
    int triggerLabelYoffset = 33;
    int timecodeSliderYoffset = 60;
    int objectSize = getWidth()-320;
    int edgeDistance = getWidth()/4;
    int sliderSize = 280;
        
    timeCodeLabel1.setBounds    ((getWidth()/2)-(objectSize/2)-(getWidth()/2.f)+edgeDistance+xOffset,
                                (getHeight()/2)-(objectSize/2)+yOffset+timecodeLabelYoffset,
                                objectSize, objectSize);
    
    tcTriggerLabel1.setBounds   ((getWidth()/2)-(objectSize/2)-(getWidth()/2.f)+edgeDistance+xOffset+triggerLabelXoffset,
                                (getHeight()/2)-(objectSize/2)+yOffset+triggerLabelYoffset,
                                objectSize, objectSize);
    
    timecodeSlider1.setBounds   ((getWidth()/2)-(sliderSize/2)-(getWidth()/2.f)+edgeDistance+xOffset,
                                (getHeight()/2)-(sliderSize/2)+yOffset+timecodeSliderYoffset,
                                sliderSize, sliderSize);
    
    ///////////////////////////////////////////////////////////////////////
        
    timeCodeLabel2.setBounds    ((getWidth()/2)-(objectSize/2)+(getWidth()/2.f)-edgeDistance+xOffset,
                                (getHeight()/2)-(objectSize/2)+yOffset+timecodeLabelYoffset,
                                objectSize, objectSize);
    tcTriggerLabel2.setBounds   ((getWidth()/2)-(objectSize/2)+(getWidth()/2.f)-edgeDistance+xOffset+triggerLabelXoffset ,
                                (getHeight()/2)-(objectSize/2)+yOffset+triggerLabelYoffset,
                                objectSize, objectSize);
    
    timecodeSlider2.setBounds   ((getWidth()/2)-(sliderSize/2)+(getWidth()/2.f)-edgeDistance+xOffset,
                                (getHeight()/2)-(sliderSize/2)+yOffset+timecodeSliderYoffset,
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

void MainComponent::mouseDown (const MouseEvent& e)
{
    dragger.startDraggingComponent (this, e);
}

void MainComponent::mouseDrag (const MouseEvent& e)
{
    // as there's no titlebar we have to manage the dragging ourselves
    dragger.dragComponent (this, e, 0);
}
