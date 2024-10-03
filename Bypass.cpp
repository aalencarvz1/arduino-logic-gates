#include "BypassGate.h"
#include "TouchScreenController.h"
#include "Utils.h"

//construtor com parametros tem que reser implementado também nas classes derivadas
BypassGate::BypassGate(
  const BaseContainerComponent* pParent,
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
) :
  AndGate(pParent, pX,pY,pSize,pConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pConnectorSize,pWidth,pConnectorMargin) 
{
  m2 = pSize;
  inputConnectorCount = 1;
};

void BypassGate::drawBody() {
  if (vertical) {
    if (lineWidth > 1) {
      TouchScreenController::tft.fillRect(x + m1 / 2 - lineWidth,y-m2,m1,m2,color); //base line
    } else {
      TouchScreenController::tft.drawLine(x + m1 / 2,y-m2,x+m1/2,y,color); //base line
    }
  } else {
    if (lineWidth > 1) {
      TouchScreenController::tft.fillRect(x,y+m1/2-lineWidth,m2,m1,color);
    } else {
      TouchScreenController::tft.drawLine(x,y+m1/2,x+m2,y+m1/2,color);
    }
  }
};
