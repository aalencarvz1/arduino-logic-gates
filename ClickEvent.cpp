#include "ClickEvent.h"
#include "TouchScreenController.h"
#include <Arduino.h>

/**
* ClickEvent
*/
ClickEvent::ClickEvent(
  const VisualComponent* pComponent,
  const void (*pStaticOnClick)()
) :
  component(pComponent),
  staticOnClick(pStaticOnClick)
{
  //Serial.println(F("INIT ClickEvent::ClickEvent"));
  initEvent();
  //Serial.println(F("END ClickEvent::ClickEvent"));
};

ClickEvent::ClickEvent(
  const VisualComponent* pComponent,
  const ICallback* pOnClickCallback
) :
  component(pComponent),
  onClickCallback(pOnClickCallback)
{
  //Serial.println(F("INIT ClickEvent::ClickEvent"));
  initEvent();
  //Serial.println(F("END ClickEvent::ClickEvent"));
};

void ClickEvent::initEvent() {
  //Serial.print(F("INIT ClickEvent::initEvent "));
  id = TouchScreenController::getNextEventId();
  //Serial.println(String(id));
  TouchScreenController::clickEvents->add(this);
  //Serial.println(F("END ClickEvent::initEvent"));
}

/*
* not call this directly, this is called on TouchScreenController::clickEvents->remove() because this is element of double lined list
*/
ClickEvent::~ClickEvent(){
  //Serial.print(F("INIT ClickEvent::~ClickEvent "));
  //Serial.println(String(id));
  if (onClickCallback != nullptr) {
    delete onClickCallback;
  }
  //Serial.println(F("END ClickEvent::~ClickEvent"));
}

//verifica se o elemento foi clicado com base no ponto central e raio definido
bool ClickEvent::checkClickEvent(const int& x,const int& y) {
  //Serial.println(F("INIT ClickEvent::checkClickEvent "));
  //Serial.println(String(id));
  bool result = false;
  if (enabled) {  
    //Serial.println("enabled "+String(x) + " " + String(y));
    if (component != nullptr) {
      //Serial.println("has component "+String(component->x)+","+String(component->y)+","+String(component->r1)+","+boolToString(component->isCircular())+","+String(component->r1)+ "," + String(component->getHeight())+","+String(abs(component->x - x))+","+String(abs(component->y - y)));      
      if (r != 0) {
        //Serial.println("checking by area");
        if (abs(xc - x) <= r && abs(yc - y) <= r) {
          result = true;
        }
      } else {
        if (component->isCirc) {
          if (abs(component->x - x) <= component->r1 && abs(component->y - y) <= component->r1) {
            result = true;
          }
        } else {
          if (x >= component->x && x <= component->x + component->getWidth()
            && y >= component->y && y <= component->y + component->getHeight()
          ) {
            result = true;
          }
        } 
      }
      if (result) {
        //Serial.println("clicked on conponent");
        if (onClickCallback != nullptr) {
          //Serial.println("calling lambda callback");
          onClickCallback->call();  // Chama a função encapsulada
        } else if (staticOnClick != nullptr) {
          //Serial.println("calling static callback");
          staticOnClick();
        }
      }
    }
  }
  //Serial.println(F("END ClickEvent::checkClickEvent"));
  return result;
};

void ClickEvent::setArea(const int& pXc, const int& pYc,const int& pR) {
  xc = pXc;
  yc = pYc;
  r=pR;
  //Serial.println("seted area " + String(r) + String(pR));
};
