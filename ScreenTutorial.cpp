#include "ScreenTutorial.h"
#include "Screens.h"
#include "ScreenTutorialGate.h"
#include "Gates.h"
#include "Gate.h"
#include "AndGate.h"


const byte ScreenTutorial::SCREEN_ID = 1;


void ScreenTutorial::drawGateButton(
  const double& pX,
  const double& pY,
  const double& pR,
  const int& col,
  const int& lin,
  const double& hSupSpace,
  const int& pColor,
  const char* pGateName
) {
  auto f = [pGateName](){
    char* params[] = {pGateName, nullptr};
    Screens::goTo(ScreenTutorialGate::SCREEN_ID,params);
  };
  BaseScreen::drawOption(
    pX + (col * (pX*2.0)), 
    pY + hSupSpace + (lin * (pY * 2.0)), 
    pR,
    pColor,
    false,   
    pGateName,
    nullptr,
    new LambdaCallback<decltype(f)>(f)
  );
  /*Button* b = new Button(this,pX + (col * (pX*2.0)), pY + hSupSpace + (lin * (pY * 2.0)), pR);
  b->color = pColor;
  //b->createBorder(2,pColor);
  //b->getBorder()->setPadding(2);
  auto f = [pGateName](){
    char* params[] = {pGateName, nullptr};
    Screens::goTo(ScreenTutorialGate::SCREEN_ID,params);
  };
  b->setOnClick(new LambdaCallback<decltype(f)>(f));
  b->draw();

  //draw button border
  TouchScreenController::tft.drawCircle(pX + (col * (pX*2.0)), pY + hSupSpace + (lin * (pY * 2.0)), pR+5, pColor);
  TouchScreenController::tft.drawCircle(pX + (col * (pX*2.0)), pY + hSupSpace + (lin * (pY * 2.0)), pR+6, pColor);

  //cotinuar implementacao aqui, comecar a recriar as portas, atencao com destrutores para serem virtuais nas classes bases*/
  if (pGateName != nullptr) {
    Gate* g = Gates::createGateByName(this,pGateName,pX+(col*(pX*2.0))-(pR*0.35),pY+hSupSpace+(lin*(pY*2.0))+(pR*0.35),pR*0.7);    
    if (g != nullptr) {
      g->hasInputButtons = false;   
      g->visibleInputs = false;
      g->draw();
      children->remove(g);
    };  
    //TouchScreenController::drawCenteredText(pGateName,pY + hSupSpace + (lin * (pY * 2.0))+pR+20,pX + (col * (pX*2.0))+5);
  };

}

void ScreenTutorial::draw(const char* params[]){
  BaseScreen::draw(params);

  //linha 1, 3 colunas
  int cols = 3;
  int lins = 2;
  double pX = m1 / cols;
  pX = pX / 2.0;
  double pY = m2 / lins;
  pY = pY / 2.0;
  double pR = pX;
  if (pY < pX) {
    pR = pY;
  }
  pR = pR * 0.4;
  int col = 0;
  int lin = 0;
  double marginSup = 15;
  double hSpace = 0;

  drawGateButton(pX,pY,pR,col,lin,marginSup,TFT_DARKCYAN,"AND");
  drawGateButton(pX,pY,pR,col+1,lin,marginSup,TFT_DARKGREY,"OR");
  drawGateButton(pX,pY,pR,col+2,lin,marginSup,TFT_RED,"NOT");

  //linha 2, 4 colunas
  cols = 4;
  pX = m1 / cols;
  pX = pX / 2.0;
  col = 0;
  lin++;
  drawGateButton(pX,pY,pR,col,lin,hSpace,TFT_OLIVE,"NAND");
  drawGateButton(pX,pY,pR,col+1,lin,hSpace,TFT_ORANGE,"NOR");
  drawGateButton(pX,pY,pR,col+2,lin,hSpace,TFT_MAGENTA,"XOR");
  drawGateButton(pX,pY,pR,col+3,lin,hSpace,TFT_PURPLE,"XNOR");

}