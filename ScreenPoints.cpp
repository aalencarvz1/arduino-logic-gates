#include "ScreenPoints.h"
#include "TouchScreenController.h"
#include "Gates.h"
#include "Button.h"
#include "Colors.h"
#include "Screens.h"
#include "ScreenPoints1.h"

const byte ScreenPoints::SCREEN_ID = 10;


void ScreenPoints::draw(const char* params[]){
  //Serial.println(F("INIT ScreenPoints::draw"));
  BaseScreen::draw(params);

  double pX = x + m1 / 2;
  pX = pX /2;
  double pY = y + m2 / 2 - 10;
  double pR = pY;
  if (pY > pX) {
    pR = pX;
  }
  pR = pR * 0.4;

  drawOption(
    pX,
    pY,
    pR,
    Colors::BLUE,
    true,
    "Jogar",
    []{
      char* params[] = {"AND", nullptr};
      Screens::goTo(ScreenPoints1::SCREEN_ID,params);
    }
  );
  
};
