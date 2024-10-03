#include "Gates.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "NandGate.h"
#include "NorGate.h"
#include "XorGate.h"
#include "XnorGate.h"
#include "BypassGate.h"

static const char* Gates::gateNames[] = {"AND", "OR", "NOT", "NAND", "NOR", "XOR", "XNOR"};
static const int Gates::gateNamesCount = sizeof(Gates::gateNames) / sizeof(Gates::gateNames[0]);


// Função para encontrar a próxima porta no array
static const char* Gates::getNext(const char* gateName) {
    for (int i = 0; i < gateNamesCount; i++) {
        if (strcmp(gateNames[i], gateName) == 0) {
            // Se for a última porta, retorna a primeira
            if (i == gateNamesCount - 1) {
                return gateNames[0];
            } else {
                // Senão, retorna a próxima porta
                return gateNames[i + 1];
            }
        }
    }
    // Caso o nome não seja encontrado, retorna NULL
    return NULL;
}

static const char* Gates::getPrev(const char* gateName) {
    for (int i = gateNamesCount-1; i >= 0; i--) {
        if (strcmp(gateNames[i], gateName) == 0) {
            // Se for a última porta, retorna a primeira
            if (i == 0) {
                return gateNames[gateNamesCount-1];
            } else {
                // Senão, retorna a anterior porta
                return gateNames[i - 1];
            }
        }
    }
    // Caso o nome não seja encontrado, retorna NULL
    return NULL;
}

static Gate* Gates::createGateByName(
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
) {
  Gate* result = nullptr;
  //toUpperCase(gateName);
  if (gateName == "AND") {
    result = new AndGate(pParent,pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  } else if (gateName == "OR") {
    result = new OrGate(pParent,pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  } else if (gateName == "NOT") {
    result = new NotGate(pParent,pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  } else if (gateName == "NAND") {
    result = new NandGate(pParent,pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  } else if (gateName == "NOR") {
    result = new NorGate(pParent,pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  } else if (gateName == "XOR") {
    result = new XorGate(pParent,pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  } else if (gateName == "XNOR") {
    result = new XnorGate(pParent,pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  } else if (gateName == "BYPASS") {
    result = new BypassGate(pParent,pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin);
  }
  return result;
}