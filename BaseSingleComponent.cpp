#include "BaseSingleComponent.h"
#include <MemoryUsage.h>
#include "BaseContainerComponent.h"

int currentComponentId = 0;

BaseSingleComponent::BaseSingleComponent(const BaseContainerComponent* pParent) {
  //Serial.print(F("INIT BaseSingleComponent::BaseSingleComponent "));
  //Serial.println("has p xxxxxxxx " + boolToString(pParent != nullptr));
  init(pParent);
  //Serial.println(F("END BaseSingleComponent::BaseSingleComponent"));
};

void BaseSingleComponent::init(const BaseContainerComponent* pParent){
  //Serial.print(F("INIT BaseSingleComponent::init "));
  if (id == 0) {
    id = currentComponentId;    
    currentComponentId++;
  }
  //Serial.println(String(id));
  if (pParent != nullptr && parent == nullptr) {      
    parent = pParent;
  }
  if (!addedToParent) {
    if (parent != nullptr) {      
      //Serial.println("has parent " + parent->id);
      parent->addChildren(this);
      addedToParent = true;
    } else {
      //Serial.println("not has parent");
    }
  }
  FREERAM_PRINT;
  //Serial.println(F("END BaseSingleComponent::init"));
}

BaseSingleComponent::~BaseSingleComponent() {
  //Serial.print(F("INIT BaseSingleComponent::~BaseSingleComponent "));
  //Serial.println(String(id));
  FREERAM_PRINT;
  //Serial.println(F("END BaseSingleComponent::~BaseSingleComponent"));
}


