#include "GatesCircuit.h"
#include "Gates.h"

GatesCircuit::GatesCircuit(
  const BaseContainerComponent* pParent,
  double pX,
  double pY,
  double pM1,
  double pM2,
  int pGateLevelCount,
  char* gatesNames[],
  bool pIntermediaryOutputsVisible
) : 
  Container(pParent,pX,pY,pM1,pM2),
  gateLevelCount(pGateLevelCount),
  intermediaryOutputsVisible(pIntermediaryOutputsVisible)  
{
  FREERAM_PRINT;
  gates = new DoubleLinkedList<Gate>("Gate");
  gates->setDeleteData(false);
  createGates(gatesNames);
  FREERAM_PRINT;
};

GatesCircuit::~GatesCircuit() {
  Serial.println(F("INIT GatesCircuit::~GatesCircuit"));
  if (gates != nullptr) {
    delete gates;
    gates = nullptr;
  }
  Serial.println(F("END GatesCircuit::~GatesCircuit"));
};

GateConnector* GatesCircuit::getNextInputConnector() {
  GateConnector* result = nullptr;
  if (gates != nullptr) {
    Node<Gate>* currentGateNode = gates->head;
    while(currentGateNode != nullptr) {
      if (currentGateNode->data != nullptr) {
        if (currentGateNode->data->inputConnectors != nullptr) {
          Node<GateConnector>* currentConnectorNode = currentGateNode->data->inputConnectors->head;
          while(currentConnectorNode != nullptr) {
            if (currentConnectorNode->data != nullptr) {
              if (currentConnectorNode->data->connectors == nullptr) {
                result = currentConnectorNode->data;
                break;
              }
            }
            if (currentConnectorNode == currentConnectorNode->next) break;
            currentConnectorNode = currentConnectorNode->next;
          }
          if (result != nullptr) break;
        }
      }
      if (currentGateNode == currentGateNode->next) break;
      currentGateNode = currentGateNode->next;
    }
  }
  return result;
}

Gate* GatesCircuit::createGate(
  char* gateName,
  GateInput* outputInput,
  double pX,
  double pY,
  double pSize,
  int pConnectorCount,
  bool pVertical,
  int pLineColor,
  double pLineWidth,
  double pAspectRatio,
  double pBaseSizePerc,
  double pConnectorSize,
  double pWidth,
  double pConnectorMargin
) {
  //Serial.println(F("INIT GatesCircuit::createGate"));
  int currentCircuitLevel = 0;
  //adjust creation gate values
  if (gateName == nullptr) {
    gateName = Gates::gateNames[0];
  };
  Gate* outputGate = nullptr;

  if (outputInput == nullptr) {
    GateConnector* gc = getNextInputConnector();
    if (gc != nullptr) {
      outputInput = gc->input;
    }
  }
  if (outputInput != nullptr) {
    if (outputInput->connector != nullptr) {
      outputGate = outputInput->connector->gate;
    }
  }

  if (outputGate != nullptr) {
    currentCircuitLevel = outputGate->currentCircuitLevel + 1;
  }

  if (pSize == DEFAULT_GATE_SIZE) {
    if (vertical) {
      pSize = (m2 / gateLevelCount) * gateVerticalSizePerc;
    } else {
      pSize = (m1 / gateLevelCount) * gateHorizontalSizePerc;
    }
  }
  if (pWidth == DEFAULT_GATE_WIDTH) {
    pWidth = pSize * (vertical ? DEFAULT_GATE_ASPECT_RATIO : gateHorizontalAspectRatio);
  }
  if (pConnectorSize == DEFAULT_GATE_INPUT_CONNECTOR_SIZE) {
    pConnectorSize = pSize * DEFAULT_GATE_INPUT_CONNECTOR_SIZE_PERC;
  }
  if (pConnectorMargin == DEFAULT_GATE_INPUT_CONNECTOR_MARGIN) {
    pConnectorMargin = pWidth * DEFAULT_GATE_INPUT_CONNECTOR_MARGIN_PERC;
  }
  double lastLevelWidth = (pow(2,gateLevelCount - 1) * pWidth) + ((pow(2,gateLevelCount - 1) - 1) * (pWidth * (vertical ? gateSpacingPerc : gateVerticalSpacingPerc)));
  double currentGateSapce = lastLevelWidth / pow(2,currentCircuitLevel);

  if (pX == -1) {
    if (topGate == nullptr) {
      if (vertical) {
        pX = x + m1 / 2 - pWidth / 2;
      } else {
        pX = x + m1 - pSize - pConnectorSize * 2 -10;
      }
    } else if (outputGate != nullptr) {            
      if (vertical) {
        double levelGateWidth = outputGate->getInputConnectorCount() * currentGateSapce;//pWidth + ((outputGate->getInputConnectorCount() - 1) * gateSpacing);
        double x1 = outputGate->x + outputGate->getWidth() / 2 - levelGateWidth / 2;
        x1 = x1 + currentGateSapce / 2 - pWidth / 2;
        pX = x1 + outputInput->connector->pos * currentGateSapce;//(pWidth + gateSpacing); 
      } else {
        pX = outputInput->x - (pSize + outputGate->getHeight() * gateHorizontalLevelSpacingPerc) - pConnectorSize;
      }
    }
  }

  if (pY == -1) {
    if (topGate == nullptr) {
      if (vertical) {
        pY = y + pSize;
      } else {
        pY = y + m2 / 2 - pWidth / 2;
      }
    } else if (outputGate != nullptr) {
      if (vertical) {
        pY = outputGate->y + pSize + outputGate->getHeight() * gateLevelSpacingPerc;  //@todo implement detect current input wich is connectec output this gate to calculate x, implement on set inputoutpu, set also gateoutput on inpu
      } else {

        double levelGateWidth = outputGate->getInputConnectorCount() * currentGateSapce;//pWidth + ((outputGate->getInputConnectorCount() - 1) * gateSpacing);
        double y1 = outputGate->y + outputGate->getWidth() / 2 - levelGateWidth / 2;
        y1 = y1 + currentGateSapce / 2 - pWidth / 2;
        pY = y1 + outputInput->connector->pos * currentGateSapce;//(pWidth + gateSpacing); 
      }
    }
  }

  lastCreatedGate = Gates::createGateByName(
    this,
    gateName,
    pX,
    pY,
    pSize,
    pConnectorCount,
    vertical,//pVertical,
    pLineColor,
    pLineWidth,
    pAspectRatio,
    pBaseSizePerc,
    pConnectorSize,
    pWidth,
    pConnectorMargin
  );
  if (lastCreatedGate != nullptr) {
    gates->add(lastCreatedGate);
    if (topGate == nullptr) {
      topGate = lastCreatedGate;                
      setBit(lastCreatedGate->gatePackedFlags,7,topOutputVisible); //7-visibleOutput, 4-outputConnectorIsVisible        
    } else {
      setBit(lastCreatedGate->gatePackedFlags,7,intermediaryOutputsVisible);//7-visibleOutput, 3-hasOutputConnector        
    };
    if (vertical) {
      lastCreatedGate->y = lastCreatedGate->y + lastCreatedGate->getInputConnectorSize() * 2;  //adjust top position, if vertical
    } else {
      //do implement
    }
    setBit(lastCreatedGate->gatePackedFlags,5,hasInputs);//5-hasInputButtons
    lastCreatedGate->currentCircuitLevel = currentCircuitLevel;
    if (lastCreatedGate->getCurrentCircuitLevel() == gateLevelCount-1) {
      setBit(lastCreatedGate->gatePackedFlags,6,true); //6-visibleInputs
    } else {
      setBit(lastCreatedGate->gatePackedFlags,6,intermediaryInputsVisible); //6-visibleInputs
    }
    lastCreatedGate->initInputConnectors();
    lastCreatedGate->initOutputConnector();
    if (outputInput != nullptr) {
      outputInput->setState(lastCreatedGate->outputState); //10-outputState
      if (outputInput->connector != nullptr) {        
        outputInput->connector->addConnector(lastCreatedGate->outputConnector);
      }
    };
  }
   //Serial.println(F("END GatesCircuit::createGate"));
  return lastCreatedGate;
};


void GatesCircuit::createGates(char* pGatesNames[]) {
  //Serial.println(F("INIT GatesCircuit::createGates"));
  if (pGatesNames != nullptr) {
    Gate* g = nullptr;
    for(int i = 0; pGatesNames[i] != nullptr; i++) {
      //Serial.println("creating " + String(i) + " " + pGatesNames[i]);
      g = createGate(pGatesNames[i]);
      if (g != nullptr) {
        g->draw();
      }
      //if (i==1) break;
    }
  }
  //Serial.println(F("END GatesCircuit::createGates"));
} 