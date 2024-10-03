#include "BaseScreen.h"


#include "TouchScreenController.h"
#include "Screens.h"

BaseScreen::BaseScreen(const char* pTitle = nullptr, const bool& pHasBack = true) : 
  Container(
    nullptr,
    DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN,
    DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN,
    TouchScreenController::tft.width() - DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN * 2,
    TouchScreenController::tft.height() - (DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN*2),
    DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_RADIUS
  ),
  title(pTitle), 
  hasBack(pHasBack) 
{
  //filled = false;  
  filled = false;
  asRectangle(); 
};

BaseScreen::~BaseScreen() {
  //Serial.println("INIT BaseScreen::~BaseScreen()");
  if (title != nullptr) {
    //delete title;
  }
  //Serial.println("END BaseScreen::~BaseScreen()");
}

void BaseScreen::drawOption(
  const double& pX,
  const double& pY, 
  const double& pR, 
  const int& pColor, 
  const bool& hasPlay, 
  const char* pText, 
  const void (*pStaticOnClick)(), 
  const ICallback* pOnClick
){
  Button* b = new Button(this,pX, pY, pR);
  b->color = pColor;
  if (pStaticOnClick != nullptr) {
    b->setOnClick(pStaticOnClick);
  } else if (pOnClick != nullptr) {
    b->setOnClick(pOnClick);
  }
  b->draw();

  //draw button border
  TouchScreenController::tft.drawCircle(pX, pY, pR+5, pColor);
  TouchScreenController::tft.drawCircle(pX, pY, pR+6, pColor);

  if (hasPlay) {
    TouchScreenController::drawRoundedPlay(pX, pY, pR*0.5,pR*0.05,pColor,TFT_BLACK);
  }

  if (pText != nullptr) {
    TouchScreenController::drawCenteredText(pText,pY+pR+20,pX);
  }
}

void BaseScreen::draw(const char* params[]) {
  //Serial.println("INIT BaseScreen::draw");
  TouchScreenController::tft.fillScreen(DEFAULT_BACKGROUND_COLOR);   
  if (title != nullptr) {
    titleInfo = TouchScreenController::drawCenteredText(title,DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN,TouchScreenController::tft.width()/2,DEFAULT_WINDOW_TITLE_TEXT_SIZE,DEFAULT_TEXT_COLOR);
  }

  //container measurements
  x = DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN;
  y = titleInfo.h+DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN+5;
  m1 = TouchScreenController::tft.width() - DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN * 2;
  m2 = TouchScreenController::tft.height() - (titleInfo.h+DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN*2);
  r2 = DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_RADIUS;

  Container::draw(params);  
  if (hasBack) {
    if (backButton == nullptr) {
      //Serial.println("creating back button");
      backButton = new Button(this,DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN,DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN,30,20);         
      backButton->color = TFT_DARKGREY;
      backButton->r2 = 3;
      backButton->setOnClick([](){
        Screens::goBack();    
      });
      backButton->text ="<";
    }    
    backButton->draw();
  }    
  //Serial.println("END BaseScreen::draw");
};


