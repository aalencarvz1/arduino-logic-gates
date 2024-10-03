#ifndef SCREENINITIALMENU_H
#define SCREENINITIALMENU_H

#include <Arduino.h>
#include "BaseScreen.h"

class ScreenInitialMenu : public BaseScreen{
  public: 
    using BaseScreen::BaseScreen;
    static const byte SCREEN_ID; 
    void draw(const char* params[] = nullptr) override;
};

#endif // SCREENINITIALMENU_H