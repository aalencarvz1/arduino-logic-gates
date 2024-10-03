#include "TouchScreenController.h"
#include "ClickEvent.h"
#include "Screens.h"
#include "ScreenInitialMenu.h"
#include "ScreenTutorialGate.h"
#include "ScreenPoints1.h"

bool inClick = false; //AVOID LOOP ON DISPATH MULTIPLE CLICKS AT SOME TIME

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  TouchScreenController::init(); 
  TouchScreenController::tft.fillScreen(TFT_BLACK);
  Screens::goTo(ScreenInitialMenu::SCREEN_ID);
  //Screens::goTo(ScreenTutorialGate::SCREEN_ID);
  //Screens::goTo(ScreenPoints1::SCREEN_ID);
}

void loop() {
  TSPoint p = TouchScreenController::ts.getPoint();

  //stackoverflow credits: restore status of shared pins to avoid not responding tft call functions
  pinMode(TouchScreenController::TS_XM,OUTPUT);
  pinMode(TouchScreenController::TS_YP,OUTPUT);

  //clicked
  if (p.z > 0 && !inClick) {
    inClick = true;
    /*DPoint uiP;
    int px2 = p.x;
    int py2 = p.y;*/
    int px2 = map(p.y, TouchScreenController::TS_MINX, TouchScreenController::TS_MAXX, TouchScreenController::tft.width(),0);
    int py2 = map(p.x, TouchScreenController::TS_MINY, TouchScreenController::TS_MAXY, TouchScreenController::tft.height(),0);
    //Serial.println("clicked on " + String(p.x) + "," + String(p.y) + " > " +String(px2) + "," + String(py2) + " " + String(inClick));

    //loop troght event receptors array, checking if is point in area of element
    Node<ClickEvent>* current = TouchScreenController::clickEvents->tail;  // Começa pelo último nó (tail)
    
    while (current != nullptr) {
      if (current->data != nullptr) {
        //Serial.println("checking event id "+String(current->data->id));
        if (current->data->checkClickEvent(px2,py2) == true) {
          break;//not bubble event
        }
      }
      if (current == current->prev) break;
      current = current->prev;
    }
    inClick = false;
  }  
  ////FREERAM_PRINT; //show free memory
  delay(100); //to preserve resources, disable in production
}
