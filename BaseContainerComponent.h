#ifndef BASE_CONTAINER_COMPONENT_H
#define BASE_CONTAINER_COMPONENT_H

#include "BaseSingleComponent.h"
#include "DoubleLinkedList.h"


class BaseContainerComponent : public virtual BaseSingleComponent{
  protected:
    DoubleLinkedList<BaseSingleComponent>* children = nullptr;    
  public:
    using BaseSingleComponent::BaseSingleComponent;
    virtual ~BaseContainerComponent();    
    virtual void addChildren(const BaseSingleComponent* pComponent);
};

#endif // BASE_CONTAINER_COMPONENT_H