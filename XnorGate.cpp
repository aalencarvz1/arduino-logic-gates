#include "XnorGate.h"

XnorGate::XnorGate(
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
  XorGate(pParent,pX,pY,pSize,pInputConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pInputConnectorSize,pWidth,pInputConnectorMargin) 
{
  m2 = pSize;  
  hasNot = true;
  outputState = true;
};


