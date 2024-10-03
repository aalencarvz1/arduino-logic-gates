#ifndef SCREENTUTORIALGATE_H
#define SCREENTUTORIALGATE_H

#include <Arduino.h>
#include "BaseScreen.h"
#include "Gate.h"

class ScreenTutorialGate : public BaseScreen{
  protected:
    Gate* currentGate = nullptr;
    Button* buttonPrev = nullptr;
    Button* buttonNext = nullptr;
    char* previousGateName = nullptr;
    char* currentGateName = nullptr;   

    double gateSize;
    double gateWidth;
    double gateX;
    double gateY;
  public: 
    using BaseScreen::BaseScreen;
    virtual ~ScreenTutorialGate();
    static const byte SCREEN_ID;
    virtual void drawPrevGate();
    virtual void drawNextGate();
    virtual void drawNavigationButtons();
    virtual void drawGate(const char* gateName);
    virtual void draw(const char* params[] = nullptr) override;
};

#endif // SCREENTUTORIALGATE_H