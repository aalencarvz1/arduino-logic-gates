#ifndef SCREENPOINTS1_H
#define SCREENPOINTS1_H

#include <Arduino.h>
#include "BaseScreen.h"
#include "Gate.h"
#include "GatesCircuit.h"

class ScreenPoints1 : public BaseScreen{
  public: 
    using BaseScreen::BaseScreen;
    static const byte SCREEN_ID;  

    Gate* currentGate = nullptr;
    GatesCircuit* currentCircuit = nullptr;
    //TouchScreenClickEvent* evNext = nullptr;
    //TouchScreenClickEvent* evPrev = nullptr;
    char* previousGateName = nullptr;
    char* currentGateName = nullptr;
    int currentDificultyLevel = 5;
    int currentPhase = 1;
    int currentPontuation = 0;
    int** phasesByLevel[7] = {3,5,5,5,5,5,5};

    double gateSize = 0;
    double gateWidth = 0;
    double gateX = 0;
    double gateY = 0;
    double resultX = 0;
    double resultY = 0;
    double resultSize = 50;
    void clearLeftSide();
    void clearRightSide();
    void clearCenterSpace();
    void clearTopTextSpace();
    void clearGateSpace(Gate* pGate, bool pDelete = true);
    void drawResult(bool isCorrect, double centerX, double centerY, double size = 50, bool onlyClean = false);
    void drawGate(char* gateName, double x, double y, double size, int pConnectorCount = DEFAULT_GATE_INPUT_CONNECTOR_COUNT, double pGateWidth = DEFAULT_GATE_WIDTH);
    void drawLevelAndPhaseText();
    void drawGateLevel();
    void drawCircuitLevel();
    void drawCurrentPontuation();
    void drawNextPhase();
    void confirm();
    virtual void draw(const char* params[] = nullptr) override;
};

#endif // SCREENPOINTS1_H