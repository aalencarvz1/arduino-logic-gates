#ifndef SCREENPOINTSGATE_H
#define SCREENPOINTSGATE_H

#include <Arduino.h>
#include "BaseScreen.h"
#include "Gate.h"

class ScreenPoints : public BaseScreen{
  public: 
    using BaseScreen::BaseScreen;
    static const byte SCREEN_ID;    
    virtual void draw(const char* params[] = nullptr) override;
};

#endif // SCREENPOINTSGATE_H