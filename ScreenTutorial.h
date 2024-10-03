#ifndef SCREENTUTORIAL_H
#define SCREENTUTORIAL_H

#include <Arduino.h>
#include "BaseScreen.h"

class ScreenTutorial : public BaseScreen{
  public:
    using BaseScreen::BaseScreen;
    static const byte SCREEN_ID; 
    void drawGateButton(
      const double& pX,
      const double& pY,
      const double& pR,
      const int& col,
      const int& lin,
      const double& hSupSpace,
      const int& pColor,
      const char* pGateName
    );
    void draw(const char* params[] = nullptr) override;
};

#endif // SCREENTUTORIAL_H