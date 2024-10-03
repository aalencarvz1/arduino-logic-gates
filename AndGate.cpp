#include "AndGate.h"
#include "TouchScreenController.h"
#include "Utils.h"

void AndGate::drawBody() {
  //Serial.println(F("INIT AndGate::drawBody"));
  double arcHeightPerc = 1.0-baseSizePerc;
  if (baseSizePerc == DEFAULT_GATE_BASE_SIZE_PERC) {
    //arcHeightPerc = 1.0/inputConnectorCount;
  }  
  if (arcHeightPerc < DEFAULT_GATE_MIN_ARC_HEIGHT_PERC) {
    arcHeightPerc = DEFAULT_GATE_MIN_ARC_HEIGHT_PERC;
  }
  arcHeight = m2 * arcHeightPerc;
  baseAdjust = 0.0;
  if (arcHeight >= m1/2.0) {
    baseAdjust = arcHeight - (m1 / 2.0);
  }   
    
  if (getBit(gatePackedFlags,0)) {//0-vertical
    if (lineWidth > 1) {
      TouchScreenController::tft.fillRect(x,y-lineWidth,m1,lineWidth,color); //base line
      TouchScreenController::tft.fillRect(x,y-m2+arcHeight-baseAdjust,lineWidth,m2-arcHeight+baseAdjust,color); //left line
      TouchScreenController::tft.fillRect(x+m1-lineWidth,y-m2+arcHeight-baseAdjust,lineWidth,m2-arcHeight+baseAdjust,color); //rigth line        
      for (int i = 0; i < lineWidth ; i++) {
        TouchScreenController::drawArcFromArrow(x+i,y-m2+arcHeight-baseAdjust,x+m1-i,y-m2+arcHeight-baseAdjust,arcHeight-i,color);
      }
    } else {
      TouchScreenController::tft.drawLine(x,y,x+m1,y,color); //base line
      TouchScreenController::tft.drawLine(x,y-m2+arcHeight-baseAdjust,x,y,color); //left line
      TouchScreenController::tft.drawLine(x+m1,y-m2+arcHeight-baseAdjust,x+m1,y,color); //rigth line        
      TouchScreenController::drawArcFromArrow(x,y-m2+arcHeight-baseAdjust,x+m1,y-m2+arcHeight-baseAdjust,arcHeight,color);
    }
  } else {
    if (lineWidth > 1) {
      TouchScreenController::tft.fillRect(x,y,lineWidth,m1,color);
      TouchScreenController::tft.fillRect(x,y,m2-arcHeight+baseAdjust,lineWidth,color); //left line
      TouchScreenController::tft.fillRect(x,y+m1-lineWidth,m2-arcHeight+baseAdjust,lineWidth,color); //rigth line
      for (int i = 0; i < lineWidth ; i++) {
        TouchScreenController::drawArcFromArrow(x+m2-arcHeight+baseAdjust,y+i,x+m2-arcHeight+baseAdjust,y+m1-i,arcHeight,color);
      }
    } else {
      TouchScreenController::tft.drawLine(x,y,x,y+m1,color);
      TouchScreenController::tft.drawLine(x,y,x+m2-arcHeight+baseAdjust,y,color); //left line
      TouchScreenController::tft.drawLine(x,y+m1,x+m2-arcHeight+baseAdjust,y+m1,color); //rigth line
      TouchScreenController::drawArcFromArrow(x+m2-arcHeight+baseAdjust,y,x+m2-arcHeight+baseAdjust,y+m1,arcHeight,color);
    }
  }
  //Serial.println(F("END AndGate::drawBody"));
};

bool AndGate::calcOutputState() {
  //Serial.println(F("INIT AndGate::calcOutputState"));
  outputState = false;
  if (inputConnectors != nullptr) {
    outputState = true;
    Node<GateConnector>* current = inputConnectors->head;
    while (current != nullptr) {
      if (current->data != nullptr) {
        if (current->data->input != nullptr) {
          outputState = outputState && current->data->input->getState();         
        }
        if (!outputState) {
          break;
        };
      }
      if (current == current->next) break;
      current = current->next;  
    }
    outputState = getBit(gatePackedFlags,8) ? !outputState : outputState; //8-hasNot
    if (outputConnector != nullptr) {
      if (outputConnector->input != nullptr) {
        outputConnector->input->setState(outputState); 
      }
    }
  };
  //Serial.println(F("END AndGate::calcOutputState"));
  return outputState;
};

