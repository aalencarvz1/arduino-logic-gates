#ifndef CLICKABLE_COMPONENT_H
#define CLICKABLE_COMPONENT_H

#include "VisualComponent.h"
#include "ClickEvent.h"

class ClickableComponent : public VisualComponent{
  public:
    using VisualComponent::VisualComponent;  
    ClickEvent* onClick = nullptr;
    virtual ~ClickableComponent();
    virtual void setOnClick(const void (*staticOnClick)());
    virtual void setOnClick(const ICallback* onClickCallback);
    virtual void removeOnClick();  
};

#endif // CLICKABLE_COMPONENT_H