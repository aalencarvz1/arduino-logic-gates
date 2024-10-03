#ifndef NANDGATE_H
#define NANDGATE_H

#include "AndGate.h"

class NandGate : public AndGate {
  public: 
    using AndGate::AndGate;
    NandGate(
      const BaseContainerComponent* pParent,
      const double& pX                = 150.0, 
      const double& pY                = 250.0,
      const double& pSize             = DEFAULT_GATE_SIZE,
      const int& pInputConnectorCount = DEFAULT_GATE_INPUT_CONNECTOR_COUNT,	
      const bool& pVertical           = DEFAULT_GATE_VERTICAL_DIRECTION,
      const int& pLineColor           = DEFAULT_GATE_LINE_COLOR,
      const double& pLineWidth        = DEFAULT_GATE_LINE_WIDTH,
      const double& pAspectRatio      = DEFAULT_GATE_ASPECT_RATIO,
      const double& pBaseSizePerc     = DEFAULT_GATE_BASE_SIZE_PERC,
      const double& pInputConnectorSize    = DEFAULT_GATE_INPUT_CONNECTOR_SIZE,
      const double& pWidth            = DEFAULT_GATE_WIDTH,
      const double& pInputConnectorMargin  = DEFAULT_GATE_INPUT_CONNECTOR_MARGIN
    );
};

#endif //NANDGATE_H