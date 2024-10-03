#include "XorGate.h"

XorGate::XorGate(
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
  OrGate(pParent,pX,pY,pSize,pInputConnectorCount,pVertical,pLineColor,pLineWidth,pAspectRatio,pBaseSizePerc,pInputConnectorSize,pWidth,pInputConnectorMargin) 
{
  setBit(gatePackedFlags,9,true);//9-exclusive
};


