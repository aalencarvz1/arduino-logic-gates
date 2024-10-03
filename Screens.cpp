#include "Screens.h"
#include <Arduino.h>
#include <StackArray.h>
#include "BaseScreen.h"

#include "ScreenInitialMenu.h"
#include "ScreenTutorial.h"
/*#include "ScreenPort.h"*/
#include "ScreenTutorialGate.h"
#include "ScreenPoints.h"
/*#include "ScreenTime.h"
#include "ScreenMake.h"*/
#include "ScreenPoints1.h"



//STATIC INITIALIZATIONS
BaseScreen* Screens::currentScreen = nullptr;
StackArray <byte> Screens::stack;


//navigate to screen by id
void Screens::goTo(const byte& screenId,const char* params[]) {      
  FREERAM_PRINT;
  if (currentScreen != nullptr) {
    delete currentScreen;
    currentScreen = nullptr;
  }
  //FREERAM_PRINT;

  if (screenId == ScreenInitialMenu::SCREEN_ID) {
    currentScreen = new ScreenInitialMenu("PORTAS LOGICAS E CIRCUITOS",false);
  } else if (screenId == ScreenTutorial::SCREEN_ID) {
    currentScreen = new ScreenTutorial("MODO TUTORIAL");
  } /*else if (screenId == ScreenPort::SCREEN_ID) {
    currentScreen = new ScreenPort();
  } */else if (screenId == ScreenTutorialGate::SCREEN_ID) {
    currentScreen = new ScreenTutorialGate("MODO TUTORIAL - PORTAS");
  } else if (screenId == ScreenPoints::SCREEN_ID) {
    currentScreen = new ScreenPoints("MODO PONTUACAO");
  } /*else if (screenId == ScreenTime::SCREEN_ID) {
    currentScreen = new ScreenTime();
  } else if (screenId == ScreenMake::SCREEN_ID) {
    currentScreen = new ScreenMake();
  } */else if (screenId == ScreenPoints1::SCREEN_ID) {
    currentScreen = new ScreenPoints1("MODO PONTUACAO");
  };
  //FREERAM_PRINT;

  if (currentScreen != nullptr) {    

    //add to stack if is not on top
    if (!stack.isEmpty()) {
      if (stack.peek() != screenId) {
        stack.push(screenId);
      }
    } else {
      stack.push(screenId);
    }

    //screen draw
    currentScreen->draw(params);
  } else {
    //Serial.println("screen not found: " + String(screenId));
  }
  FREERAM_PRINT;
};

//navigate to previous screen on stack
void Screens::goBack(const char* params[]) { 
  //Serial.println("goBack"); 
  stack.pop();
  Screens::goTo(stack.peek(),params);
}