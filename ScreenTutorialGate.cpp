#include "ScreenTutorialGate.h"
#include "TouchScreenController.h"
#include "Gates.h"

const byte ScreenTutorialGate::SCREEN_ID = 3;


ScreenTutorialGate::~ScreenTutorialGate(){
}

void ScreenTutorialGate::drawGate(const char* gateName){

  //clear gate name
  TouchScreenController::tft.fillRect(
    x+5,
    y+5,
    100,
    20,
    DEFAULT_BACKGROUND_COLOR
  );
  
  //clear previous gate space
  if (currentGate != nullptr) {
    TouchScreenController::tft.fillRect(
      currentGate->x-DEFAULT_GATE_MAX_INPUT_RADIUS,
      y + 1,//currentGate->y-currentGate->size-currentGate->connectorSize,
      currentGate->getWidth()+DEFAULT_GATE_MAX_INPUT_RADIUS*2,
      y + m2 - 30, //currentGate->size+2*currentGate->connectorSize
      DEFAULT_BACKGROUND_COLOR
    );
    //delete currentGate;
    //Serial.println("removing current gate " + String(currentGate->id));
    children->remove(currentGate);
    currentGate = nullptr;

    
  }

  TouchScreenController::tft.setCursor(x+5,y+5);
  TouchScreenController::tft.setTextSize(2);
  TouchScreenController::tft.setTextColor(DEFAULT_TEXT_COLOR);
  TouchScreenController::tft.print(gateName);

  //tests
  //currentGate = Gates::createGateByName(this,gateName,gateX,gateY,gateSize,5,true,DEFAULT_GATE_LINE_COLOR,5);
  //currentGate = Gates::createGateByName(this,gateName,gateX-50,gateY-100,gateSize,2,false);
  //currentGate = Gates::createGateByName(this,gateName,gateX-50,gateY-100,gateSize,4,false,DEFAULT_GATE_LINE_COLOR,5);

  currentGate = Gates::createGateByName(this,gateName,gateX,gateY,gateSize);
  if (currentGate != nullptr) {

    currentGate->hasInputButtons = true;
    currentGate->draw();
  }
}

void ScreenTutorialGate::drawNavigationButtons(){
  //Serial.println(currentGateName);
  bool prevEnabled = currentGateName != Gates::gateNames[0];
  bool nextEnabled = currentGateName != Gates::gateNames[Gates::gateNamesCount-1];  
  //Serial.println(boolToString(prevEnabled)+","+boolToString(nextEnabled));
  if (buttonPrev == nullptr) {
    buttonPrev = new Button(this,x+50,y + m2 /2+25,x+50,y + m2 /2-25,5);
    buttonPrev->asTriangle();    
    buttonPrev->color = TFT_YELLOW;    
    buttonPrev->setVisible(prevEnabled);     
    buttonPrev->draw();
    auto f = [this](){
      this->drawPrevGate();
      Serial.println("clicked x");
    };
    buttonPrev->setOnClick(new LambdaCallback<decltype(f)>(f));
    buttonPrev->onClick->setArea(buttonPrev->x-buttonPrev->r1,buttonPrev->y-buttonPrev->r1,buttonPrev->r1);     
  } else {
    bool previousVisibleState = buttonPrev->visible;
    buttonPrev->setVisible(prevEnabled);          
    if (!previousVisibleState && prevEnabled) {
      buttonPrev->onClick->setArea(buttonPrev->x-buttonPrev->r1,buttonPrev->y-buttonPrev->r1,buttonPrev->r1);     
    }
  }
  buttonPrev->onClick->enabled = prevEnabled;
  
  if (buttonNext == nullptr) {
    buttonNext = new Button(this,x+m1-50,y + m2 /2-25,x+m1-50,y + m2 /2+25,5);
    buttonNext->asTriangle();   
    buttonNext->color = TFT_YELLOW;     
    buttonNext->setVisible(nextEnabled);     
    buttonNext->draw();
    auto f = [this](){
      this->drawNextGate();
      //Serial.println("clicked x");
    };
    buttonNext->setOnClick(new LambdaCallback<decltype(f)>(f));
    buttonNext->onClick->setArea(buttonNext->x+buttonNext->r1,buttonNext->y+buttonNext->r1,buttonNext->r1);     
  } else {
    bool previousVisibleState = buttonNext->visible;
    buttonNext->setVisible(nextEnabled);          
    if (!previousVisibleState && nextEnabled) {
      buttonNext->onClick->setArea(buttonNext->x+buttonNext->r1,buttonNext->y+buttonNext->r1,buttonNext->r1);     
    }
  }
  buttonNext->onClick->enabled = nextEnabled;
}

void ScreenTutorialGate::drawNextGate(){
  currentGateName = Gates::getNext(currentGateName);
  drawNavigationButtons();
  drawGate(currentGateName);
}

void ScreenTutorialGate::drawPrevGate(){
  currentGateName = Gates::getPrev(currentGateName);
  drawNavigationButtons();
  drawGate(currentGateName);
}

void ScreenTutorialGate::draw(const char* params[]){
  //Serial.println(F("INIT ScreenTutorialGate::draw"));
  BaseScreen::draw(params);

  gateSize = m2 * 0.4;
  gateWidth = gateSize * DEFAULT_GATE_ASPECT_RATIO;
  gateX = x + m1 / 2 - gateWidth / 2;//TouchScreenController::tft.width() / 2 - gateWidth / 2;
  gateY = y + m2 - m2 * DEFAULT_GATE_INPUT_CONNECTOR_SIZE_PERC;//TouchScreenController::tft.height() - 75;

  if (params != nullptr) {      
    currentGateName = Gates::getPrev(params[0]);    
  } else {
    currentGateName = Gates::gateNames[Gates::gateNamesCount-1];    
  }
  drawNextGate();
  //Serial.println(F("END ScreenTutorialGate::draw"));
};
