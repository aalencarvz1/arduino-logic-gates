#ifndef GATES_H
#define GATES_H

#include "Gate.h"
#include "BaseContainerComponent.h"

struct Gates{

  static const char* gateNames[];
  static const int gateNamesCount;
  static const char* getNext(const char* gateName);
  static const char* getPrev(const char* gateName);
  static Gate* createGateByName(
    const BaseContainerComponent* pParent,
    const char* gateName,
    const double& pX                = 150.0, 
    const double& pY                = 250.0,
    const double& pSize             = DEFAULT_GATE_SIZE,
    const int& pConnectorCount      = DEFAULT_GATE_INPUT_CONNECTOR_COUNT,	
    const bool& pVertical           = DEFAULT_GATE_VERTICAL_DIRECTION,
    const int& pLineColor           = DEFAULT_GATE_LINE_COLOR,
    const double& pLineWidth        = DEFAULT_GATE_LINE_WIDTH,
    const double& pAspectRatio      = DEFAULT_GATE_ASPECT_RATIO,
    const double& pBaseSizePerc     = DEFAULT_GATE_BASE_SIZE_PERC,
    const double& pConnectorSize    = DEFAULT_GATE_INPUT_CONNECTOR_SIZE,
    const double& pWidth            = DEFAULT_GATE_WIDTH,
    const double& pConnectorMargin  = DEFAULT_GATE_INPUT_CONNECTOR_MARGIN
  );
};

#endif //GATES_H