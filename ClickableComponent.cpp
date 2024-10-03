#include "ClickableComponent.h"

ClickableComponent::~ClickableComponent(){
  //Serial.print(F("INIT ClickableComponent::~ClickableComponent "));
  //Serial.println(String(id));
  removeOnClick();
  //Serial.println(F("END ClickableComponent::~ClickableComponent"));
}

void ClickableComponent::removeOnClick() {
  //Serial.println(F("INIT ClickableComponent::removeOnClick"));
  if (onClick != nullptr) {
    TouchScreenController::clickEvents->remove(onClick);    
    onClick = nullptr;
  }
  //Serial.println(F("END ClickableComponent::removeOnClick"));
}

void ClickableComponent::setOnClick(const void (*staticOnClick)()) {
  //Serial.println(F("INIT ClickableComponent::setOnClick"));
  removeOnClick();
  onClick = new ClickEvent(this,staticOnClick);
  //Serial.println(F("END ClickableComponent::setOnClick"));
}

void ClickableComponent::setOnClick(const ICallback* onClickCallback) {
  //Serial.println(F("INIT ClickableComponent::setOnClick"));
  removeOnClick();
  onClick = new ClickEvent(this,onClickCallback);
  //Serial.println(F("END ClickableComponent::setOnClick"));
}