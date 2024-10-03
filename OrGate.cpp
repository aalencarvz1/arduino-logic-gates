#include "OrGate.h"
#include "TouchScreenController.h"
#include "Utils.h"


OrGate::OrGate(
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
  if (pBaseSizePerc < DEFAULT_GATE_MIN_OR_BASE_SIZE_PERC) {
    baseSizePerc = DEFAULT_GATE_MIN_OR_BASE_SIZE_PERC;
  } else if (pBaseSizePerc > DEFAULT_GATE_MAX_OR_BASE_SIZE_PERC) {
    baseSizePerc = DEFAULT_GATE_MAX_OR_BASE_SIZE_PERC;
  } else if (pBaseSizePerc == DEFAULT_GATE_BASE_SIZE_PERC) {
    baseSizePerc = DEFAULT_GATE_MIN_OR_BASE_SIZE_PERC;
  }
};


void OrGate::drawBody() {
  //Serial.println(F("INIT OrGate::drawBody"));
  double arcHeightPerc = 1.0-baseSizePerc;
  if (baseSizePerc == DEFAULT_GATE_BASE_SIZE_PERC) {    
    //arcHeightPerc = 1.0/connectorCount;
  }  
  double arcHeight = m2 * arcHeightPerc;
  double baseAdjust = 0;

  double baseArcHeight = m1 * DEFAULT_GATE_BASE_ARC_HEIGHT_ASPECT_RATIO;
  CircleInfo baseArc;
  if (vertical) {  

    //draw curved base  
    baseArc = TouchScreenController::drawArcFromArrow(x,y,x+m1,y,baseArcHeight,color);
    if (lineWidth > 1) {
      for (int i = 1; i < lineWidth ; i++) {
        TouchScreenController::drawArcFromArrow(x+i,y,x+m1-i,y,baseArcHeight-i,color);
      }
    }

    if (exclusive) {
      TouchScreenController::drawArcFromArrow(x,y+m2 * DEFAULT_GATE_EXCLUSIVE_SPACE_PERC,x+m1,y+m2 * DEFAULT_GATE_EXCLUSIVE_SPACE_PERC,baseArcHeight,color);
    }

    //draw laterals
    if (lineWidth > 1) {
      TouchScreenController::tft.fillRect(x,y-m2+arcHeight-baseAdjust,lineWidth,m2-arcHeight+baseAdjust,color); //left line
      TouchScreenController::tft.fillRect(x+m1-lineWidth,y-m2+arcHeight-baseAdjust,lineWidth,m2-arcHeight+baseAdjust,color); //rigth line 
    } else {
      TouchScreenController::tft.drawLine(x,y-m2+arcHeight-baseAdjust,x,y,color); //left line
      TouchScreenController::tft.drawLine(x+m1,y-m2+arcHeight-baseAdjust,x+m1,y,color); //rigth line 
    }

    //draw connectors
    double connMargin = inputConnectorMargin;
    if (lineWidth > 1) {
      connMargin = connMargin - lineWidth / 2;
    }
    for(int i = 0; i < inputConnectorCount * 1.0 / 2; i++) {      
      connMargin = connMargin + (i * (m1 - (connMargin * 2)) / (inputConnectorCount - 1));
      double newConnectorSize = getCatetoFromPitagoras(baseArc.r,baseArc.x-(x+connMargin)); 
      double newPos = baseArc.y-newConnectorSize;
      newConnectorSize = newConnectorSize - (baseArc.y - (y + inputConnectorSize));
      
      GateConnector* gc = findGateConnectorByPos(i);
      if (gc != nullptr) {
        //drawConnector(i,newPos, newConnectorSize);
        gc->y = newPos;
        if (lineWidth > 1) {
          gc->setY2(newConnectorSize);//line do implement rectangle
        } else {
          gc->setY2(newPos+newConnectorSize);//line do implement rectangle
        }
      }
      if ((i+1)>inputConnectorCount*1.0/2) break;
      //drawConnector(inputConnectorCount-(i+1),newPos, newConnectorSize);
      gc = findGateConnectorByPos(inputConnectorCount-(i+1));
      if (gc != nullptr) {
        //drawConnector(i,newPos, newConnectorSize);
        gc->y = newPos;
        if (lineWidth > 1) {
          gc->setY2(newConnectorSize);//line do implement rectangle
        } else {
          gc->setY2(newPos+newConnectorSize);//line do implement rectangle
        }
      }

    }
    

    //draw top curved arcs
    double arcHeight2 = sqrt(pow((x+(m1/2.0)) - x, 2.0) + pow((y-m2+arcHeight-baseAdjust) - (y-m2-baseAdjust), 2.0));  // Distância entre P1 e P2 (lado a)
    arcHeight2 = arcHeight2 / 15; //divide o circulo em 15 partes, 
    for (int i = 0; i < lineWidth ; i++) {
      TouchScreenController::drawArcFromArrow(x+i,y-m2+arcHeight-baseAdjust,x+(m1/2.0)-i,y-m2-baseAdjust,arcHeight2-i,color);
      TouchScreenController::drawArcFromArrow(x+(m1/2.0)-i,y-m2-baseAdjust,x+m1-i,y-m2+arcHeight-baseAdjust,arcHeight2-i,color);
    }
  } else {

    //draw base arc
    baseArc = TouchScreenController::drawArcFromArrow(x,y,x,y+m1,baseArcHeight,color);
    if (lineWidth > 1) {
      for (int i = 1; i < lineWidth ; i++) {
        TouchScreenController::drawArcFromArrow(x,y+i,x,y+m1-i,baseArcHeight-i,color);
      }
    }

    //draw exclusive curved bar
    if (exclusive) {
      baseArc = TouchScreenController::drawArcFromArrow(x-m2 * DEFAULT_GATE_EXCLUSIVE_SPACE_PERC,y,x-m2 * DEFAULT_GATE_EXCLUSIVE_SPACE_PERC,y+m1,baseArcHeight,color);
    }

    //draw laterals
    if (lineWidth > 1) {
      TouchScreenController::tft.fillRect(x,y,m2-arcHeight+baseAdjust,lineWidth,color); //left line
      TouchScreenController::tft.fillRect(x,y+m1-lineWidth,m2-arcHeight+baseAdjust,lineWidth,color); //rigth line
    } else {
      TouchScreenController::tft.drawLine(x,y,x+m2-arcHeight+baseAdjust,y,color); //left line
      TouchScreenController::tft.drawLine(x,y+m1,x+m2-arcHeight+baseAdjust,y+m1,color); //rigth line
    }

    //draw conectors
    double connMargin = inputConnectorMargin;
    if (lineWidth > 1) {
      connMargin = connMargin - lineWidth / 2;
    }
    //for(int i = 0; i < inputConnectorCount ; i++) {  
    for(int i = 0; i < inputConnectorCount * 1.0 / 2; i++) {         
      connMargin = connMargin + (i * (m1 - (connMargin * 2)) / (inputConnectorCount - 1));
      double newConnectorSize = getCatetoFromPitagoras(baseArc.r,baseArc.y-(y+connMargin)); 
      double newPos = baseArc.x+newConnectorSize;
      newConnectorSize = newConnectorSize - (x - baseArc.x - inputConnectorSize);
      


      
      //drawConnector(i,newPos, newConnectorSize);
      GateConnector* gc = findGateConnectorByPos(i);
      if (gc != nullptr) {
        //drawConnector(i,newPos, newConnectorSize);
        //gc->setY(newPos);
        if (lineWidth > 1) {
          gc->setX2(newConnectorSize);//line do implement rectangle
        } else {
          gc->setX2(newPos+newConnectorSize);//line do implement rectangle
        }
      }
      if ((i+1)>inputConnectorCount*1.0/2) break;
      //drawConnector(inputConnectorCount-(i+1),newPos, newConnectorSize);      
      gc = findGateConnectorByPos(inputConnectorCount-(i+1));
      if (gc != nullptr) {
        //drawConnector(i,newPos, newConnectorSize);
        //gc->setY(newPos);
        if (lineWidth > 1) {
          gc->setX2(newConnectorSize);//line do implement rectangle
        } else {
          gc->setX2(newPos+newConnectorSize);//line do implement rectangle
        }
      }
    }    

    //draw top curved arcs
    double arcHeight2 = sqrt(pow((x+m2-baseAdjust) - (x+m2-arcHeight-baseAdjust), 2.0) + pow((y+m1/2) - (y), 2.0));  // Distância entre P1 e P2 (lado a)
    arcHeight2 = arcHeight2 / 15; //divide o circulo em 15 partes para obter uma curva suave (raio grande), 
    for (int i = 0; i < lineWidth ; i++) {
      //Serial.println("x1="+String(x+(m1/2.0)-i)+",y1="+String(y-m2-baseAdjust)+"x2="+String(x+m1-i)+",y2="+String(y-m2+arcHeight-baseAdjust));
      TouchScreenController::drawArcFromArrow(x+m2-arcHeight-baseAdjust,y+i,x+m2-baseAdjust,y+m1/2+i,arcHeight2-i,color);
      TouchScreenController::drawArcFromArrow(x+m2-baseAdjust,y+m1/2-i,x+m2-arcHeight-baseAdjust,y+m1-i,arcHeight2-i,color);
    }
  }
  //Serial.println(F("END OrGate::drawBody"));
};

bool OrGate::calcOutputState() {
  //Serial.println(F("INIT OrGate::calcOutputState"));
  outputState = false;
  if (inputConnectors != nullptr) {
    Node<GateConnector>* current = inputConnectors->head;
    while (current != nullptr) {
      if (current->data != nullptr) {
        if (current->data->input != nullptr) {
          if (outputState) {
            if (exclusive) {
              if (current->data->input->getState()) {
                outputState = false;
                break;
              }
            } else {
              break;
            }
          } else {
            outputState = current->data->input->getState();
          }
        }        
      }
      if (current == current->next) break;
      current = current->next;  
    }
    outputState =  hasNot ? !outputState : outputState;
    if (outputConnector != nullptr) {
      if (outputConnector->input != nullptr) {
        outputConnector->input->setState(outputState); 
      }
    }
  };
  //Serial.println(F("END OrGate::calcOutputState"));
  return outputState;
};

