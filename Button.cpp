#include "Button.h"

void Button::draw(const char* params[]) {
  ClickableComponent::draw(params);
  if (text != nullptr) {
    TouchScreenController::drawCenteredText(text,y+m2/2,x+m1/2);
  }
}