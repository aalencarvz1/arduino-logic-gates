#ifndef BUTTON_H
#define BUTTON_H

#include "ClickableComponent.h"

class Button : public ClickableComponent {
  public:
    using ClickableComponent::ClickableComponent;    
    char* text = nullptr;
    virtual void draw(const char* params[] = nullptr) override;
};

#endif //BUTTON_H