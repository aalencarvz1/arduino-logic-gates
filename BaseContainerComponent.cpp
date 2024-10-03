#include "BaseContainerComponent.h"


BaseContainerComponent::~BaseContainerComponent() {
  //Serial.println(F("INIT BaseContainerComponent::~BaseContainerComponent"));
  if (children != nullptr) {
    //Serial.println("has children, deleting...");
    delete children;
    children = nullptr;
  }
  //Serial.println(F("END BaseContainerComponent::~BaseContainerComponent"));
};

void BaseContainerComponent::addChildren(const BaseSingleComponent* pComponent) {
  //Serial.println(F("INIT BaseContainerComponent::addChildren"));
  //Serial.println(String(id)+" addeded children " + String(pComponent->id));
  if (children == nullptr) {
    children = new DoubleLinkedList<BaseSingleComponent>("BaseSingleComponent");
  }
  children->add(pComponent);
  //Serial.println(F("END BaseContainerComponent::addChildren"));
}