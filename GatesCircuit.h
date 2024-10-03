#ifndef GATESCIRCUIT_H
#define GATESCIRCUIT_H

#include "Gate.h"
#include "DoubleLinkedList.h"
#include "TouchScreenController.h"
#include "BaseScreen.h"
#include "Container.h"

#define DEFAULT_CIRCUIT_HAS_INPUTS true
#define DEFAULT_CIRCUIT_INTERMEDIARY_INPUTS_IS_VISIBLE false
#define DEFAULT_CIRCUIT_INTERMEDIARY_OUTPUTS_IS_VISIBLE false
#define DEFAULT_CIRCUIT_TOP_OUTPUT_IS_VISIBLE true
#define DEFAULT_GATE_SPACING_PERC 0.3
#define DEFAULT_GATE_VERTICAL_SPACING_PERC 0.5
#define DEFAULT_GATE_LEVEL_SPACING_PERC 0.1
#define DEFAULT_GATE_HORIZONTAL_LEVEL_SPACING_PERC 0.4
#define DEFAULT_CIRCUIT_GATE_LEVEL_COUNT 2
#define DEFAULT_GATE_VERTICAL_SIZE_PERC 0.5
#define DEFAULT_GATE_HORIZONTAL_SIZE_PERC 0.4
#define DEFAULT_CIRCUIT_HORIZONTAL_GATE_ASPECT_RATIO DEFAULT_GATE_ASPECT_RATIO

class GatesCircuit : public Container{ 
  public:
    using Container::Container;
    Gate* topGate = nullptr;
    Gate* lastCreatedGate = nullptr;
    DoubleLinkedList<Gate>* gates;
    double gateSpacingPerc = DEFAULT_GATE_SPACING_PERC;
    double gateVerticalSpacingPerc = DEFAULT_GATE_VERTICAL_SPACING_PERC;
    double gateLevelSpacingPerc = DEFAULT_GATE_LEVEL_SPACING_PERC;
    double gateHorizontalLevelSpacingPerc = DEFAULT_GATE_HORIZONTAL_LEVEL_SPACING_PERC;
    double gateVerticalSizePerc = DEFAULT_GATE_VERTICAL_SIZE_PERC;
    double gateHorizontalSizePerc = DEFAULT_GATE_HORIZONTAL_SIZE_PERC;
    double gateHorizontalAspectRatio = DEFAULT_CIRCUIT_HORIZONTAL_GATE_ASPECT_RATIO;
    int gateLevelCount = DEFAULT_CIRCUIT_GATE_LEVEL_COUNT;
    bool vertical = true;
    bool hasInputs = DEFAULT_CIRCUIT_HAS_INPUTS;
    bool intermediaryInputsVisible = DEFAULT_CIRCUIT_INTERMEDIARY_INPUTS_IS_VISIBLE;
    bool intermediaryOutputsVisible = DEFAULT_CIRCUIT_INTERMEDIARY_OUTPUTS_IS_VISIBLE;
    bool topOutputVisible = DEFAULT_CIRCUIT_TOP_OUTPUT_IS_VISIBLE;
    GatesCircuit(
      const BaseContainerComponent* pParent,
      double pX = DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN,
      double pY = 50+DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN+5,
      double pM1 = TouchScreenController::tft.width() - DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN * 2,
      double pM2 = TouchScreenController::tft.height() - (50+DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN*2),
      int pGateLevelCount = DEFAULT_CIRCUIT_GATE_LEVEL_COUNT,
      char* gatesNames[] = nullptr,
      bool pIntermediaryOutputsVisible = DEFAULT_CIRCUIT_INTERMEDIARY_OUTPUTS_IS_VISIBLE
    );
    ~GatesCircuit();

    GateConnector* getNextInputConnector();

    Gate* createGate(
      char* gateName = nullptr, 
      GateInput* outputInput = nullptr,
      double pX                = -1, 
      double pY                = -1,
      double pSize             = DEFAULT_GATE_SIZE,
      int pConnectorCount      = DEFAULT_GATE_INPUT_CONNECTOR_COUNT,	
      bool pVertical           = DEFAULT_GATE_VERTICAL_DIRECTION,
      int pLineColor           = DEFAULT_GATE_LINE_COLOR,
      double pLineWidth        = DEFAULT_GATE_LINE_WIDTH,
      double pAspectRatio      = DEFAULT_GATE_ASPECT_RATIO,
      double pBaseSizePerc     = DEFAULT_GATE_BASE_SIZE_PERC,
      double pConnectorSize    = DEFAULT_GATE_INPUT_CONNECTOR_SIZE,
      double pWidth            = DEFAULT_GATE_WIDTH,
      double pConnectorMargin  = DEFAULT_GATE_INPUT_CONNECTOR_MARGIN
    );

    void createGates(char* pGatesNames[]);
};

#endif