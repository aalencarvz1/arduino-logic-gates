#include "NotGate.h"
#include "TouchScreenController.h"
#include "Utils.h"


NotGate::NotGate(
  const BaseContainerComponent* pParent,
  const double& pX,
  const double& pY,
  const double& pSize,
  const int& pInputConnectorCount,
  const bool& pVertical,
  const int& pLineColor,
  const double& pLineWidth,
  const double& pAspectRatio,
  const double& pBaseSizePerc,
  const double& pInputConnectorSize,
  const double& pWidth,
  const double& pInputConnectorMargin
) :
  Gate(pParent,pX,pY,pSize,pInputConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pInputConnectorSize,pWidth,pInputConnectorMargin) 
{
  inputConnectorCount = 1;
  m2 = pSize;
  setBit(gatePackedFlags,8,true);//8-hasNot
  outputState = true;
};

void NotGate::drawBody() {
  //Serial.println(F("INIT NotGate::drawBody"));
  if (outputState) {
    TouchScreenController::tft.drawLine(x,y,x+m1,y, color);
    TouchScreenController::tft.drawLine(x,y,x+m1/2,y-m2, color);
    TouchScreenController::tft.drawLine(x+m1,y,x+m1/2,y-m2, color);
  } else {
    TouchScreenController::tft.drawLine(x,y,x,y+m1, color);
    TouchScreenController::tft.drawLine(x,y,x+m2,y+m1/2, color);
    TouchScreenController::tft.drawLine(x,y+m1,x+m2,y+m1/2, color);
  } 
  //Serial.println(F("END NotGate::drawBody"));
};

bool NotGate::calcOutputState() {
  //Serial.println(F("INIT NotGate::calcOutputState"));
  outputState = true;
  if (inputConnectors != nullptr) {
    if (inputConnectors->tail != nullptr) {
      if (inputConnectors->tail->data != nullptr) {
        if (inputConnectors->tail->data->input!=nullptr) {
          outputState = !inputConnectors->tail->data->input->getState();      
        }
      }
    }    
    if (outputConnector != nullptr) {
      if (outputConnector->input != nullptr) {
        outputConnector->input->setState(outputState); 
      }
    }
  };
  //Serial.println(F("END NotGate::calcOutputState"));
  return outputState;
};

