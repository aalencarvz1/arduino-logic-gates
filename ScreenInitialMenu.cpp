#include "ScreenInitialMenu.h"
#include "TouchScreenController.h"
#include "Screens.h"
#include "ScreenTutorial.h"
#include "ScreenPoints.h"
/*#include "ScreenTime.h"
#include "ScreenMake.h"*/
#include "Colors.h"
#include "Button.h"

const byte ScreenInitialMenu::SCREEN_ID = 0;

void ScreenInitialMenu::draw(const char* params[]) {
  BaseScreen::draw(params);
  TouchScreenController::drawCenteredText("Modos de jogo",titleInfo.h+20);
  double _4Div = TouchScreenController::tft.width() / 4.0;
  double itemMenuXPos = _4Div / 2.0;
  double itemMenuYPos = TouchScreenController::tft.height() / 2.0;
  double itemR = itemMenuXPos * 0.5;  
  drawOption(itemMenuXPos, itemMenuYPos, itemR, TFT_YELLOW,true,"Tutorial",[](){    
    Screens::goTo(ScreenTutorial::SCREEN_ID);
  });
  drawOption(
    itemMenuXPos + _4Div , 
    itemMenuYPos, 
    itemR, 
    Colors::BLUE,
    true,
    "Pontuacao",
    [](){    
      Screens::goTo(ScreenPoints::SCREEN_ID);
    }
  );
  drawOption(itemMenuXPos + _4Div * 2, itemMenuYPos, itemR, Colors::GREEN,true,"Tempo",[](){    
    //Screens::goTo(ScreenTime::SCREEN_ID);
  });
  drawOption(itemMenuXPos + _4Div * 3, itemMenuYPos, itemR, TFT_RED,true,"Construa",[](){    
    //Screens::goTo(ScreenMake::SCREEN_ID);
  });
};