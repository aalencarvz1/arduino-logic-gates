#ifndef CONTAINER_H
#define CONTAINER_H

#include "BaseContainerComponent.h"
#include "VisualComponent.h"

class Container : public BaseContainerComponent, public VisualComponent{
  public:
    using BaseContainerComponent::BaseContainerComponent;
    using VisualComponent::VisualComponent;
  
};

#endif // CONTAINER_H