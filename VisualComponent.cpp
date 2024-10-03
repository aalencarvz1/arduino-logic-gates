#include "VisualComponent.h"



VisualComponent::VisualComponent(
  const BaseContainerComponent* pParent,
  const int& pX,
  const int& pY, 
  const int& pR
) : 
  BaseSingleComponent(pParent), 
  x(pX), 
  y(pY), 
  r1(pR) 
{
  //Serial.println(F("INIT VisualComponent::VisualComponent"));
  init(pParent);
  //Serial.println(String(id));
  asCircle();
  //Serial.println(F("END VisualComponent::VisualComponent"));
};

VisualComponent::VisualComponent(
  const BaseContainerComponent* pParent,
  const int& pX,
  const int& pY, 
  const int& pWidth,
  const int& pHeight
) : 
  BaseSingleComponent(pParent), 
  x(pX), 
  y(pY), 
  m1(pWidth),
  m2(pHeight)
{
  //Serial.println(F("INIT VisualComponent::VisualComponent"));
  init(pParent);
  //Serial.println(String(id));
  //Serial.println("parent " + boolToString(parent != nullptr) + "," +  boolToString(pParent != nullptr));
  asRectangle();
  //Serial.println(F("END VisualComponent::VisualComponent"));
};

VisualComponent::VisualComponent(
  const BaseContainerComponent* pParent,
  const int& pX,
  const int& pY, 
  const int& pWidth,
  const int& pHeight,
  const int& pRoundRadius
) : 
  BaseSingleComponent(pParent), 
  x(pX), 
  y(pY), 
  m1(pWidth),
  m2(pHeight),
  r2(pRoundRadius)
{
  //Serial.println(F("INIT VisualComponent::VisualComponent"));
  init(pParent);
  //Serial.println(String(id));
  //Serial.println("parent " + boolToString(parent != nullptr) + "," +  boolToString(pParent != nullptr));
  asRectangle();  
  //Serial.println(F("END VisualComponent::VisualComponent"));
};

void VisualComponent::clearTypeFlags() {
  setBit(packedFlags,2,false);//line
  setBit(packedFlags,3,false);//circle
  setBit(packedFlags,4,false);//rect
  setBit(packedFlags,5,false);//triangle
};

void VisualComponent::asLine() {
  clearTypeFlags();
  setBit(packedFlags,2,true);
};
void VisualComponent::asCircle() {
  clearTypeFlags();
  setBit(packedFlags,3,true);
};
void VisualComponent::asRectangle() {
  clearTypeFlags();
  setBit(packedFlags,4,true);
};
void VisualComponent::asTriangle() {
  clearTypeFlags();
  setBit(packedFlags,5,true);
};

void VisualComponent::setVisible(const bool& pVisible, const bool& pDraw) {
  bool previousVisible = getBit(packedFlags,0);
  setBit(packedFlags,0,pVisible);
  if (pDraw) {
    if (getBit(packedFlags,0)) {
      if (!previousVisible) {
        draw();
      }
    } else {
      if (previousVisible) {
        int previousColor = color;
        color = DEFAULT_BACKGROUND_COLOR;
        setBit(packedFlags,0,!getBit(packedFlags,0));
        draw();
        setBit(packedFlags,0,!getBit(packedFlags,0));
        color = previousColor;
      }
    }
  }
}


void VisualComponent::draw(const char* params[]){
  if (getBit(packedFlags,0)) {//0-visible
    if (getBit(packedFlags,2)) {//2-line
      TouchScreenController::tft.drawLine(x, y, m1, m2, color);
    } else if (getBit(packedFlags,4)) {//4-rectangle
      if (getBit(packedFlags,1)) {//1-filled
        if (r2 != 0) {
          TouchScreenController::tft.fillRoundRect(x, y, m1, m2, r2, color);
        } else {
          TouchScreenController::tft.fillRect(x, y, m1, m2, color);
        }
      } else {
        if (r2 != 0) {
          TouchScreenController::tft.drawRoundRect(x, y, m1, m2, r2, color);
        } else {
          TouchScreenController::tft.drawRect(x, y, m1, m2, color);
        }
      }
    } else if (getBit(packedFlags,3)) {//3-circle
      if (getBit(packedFlags,1)) {//1-filled
        TouchScreenController::tft.fillCircle(x, y, r1, color);
      } else {
        TouchScreenController::tft.drawCircle(x, y, r1, color);
      }
    } else if (getBit(packedFlags,5)) { //5-triangle   
      double x2 = 0;
      double y2 = 0;
      if (x == m1) {
        y2 = min(m2,y) + abs(m2-y)/2.0;
        x2 = x + sqrt(3.0) * (m2*1.0-y*1.0) / 2.0;
        r1 = abs(m2-y) / 2; //to use in circular click event to convenience
        //Serial.println("seted r1 "+String(r1));
      } else if (y == m2) {
        x2 = min(m1,x) + abs(m1-x)/2.0;
        y2 = y + sqrt(3.0) * (m1*1.0-x*1.0) / 2.0;
        r1 = abs(m1-x) / 2;
      } else {
        DPoint p1;
        DPoint p2;
        p1.x = x;
        p1.y = y;
        p2.x = m1;
        p2.y = m2;  
        double d = sqrt(pow(m1 - x, 2.0) + pow(m2 - y, 2.0));  // Distância entre P1 e P2 (lado a)    
        DPoint p3 = calcularP3(d,d,d,p1,p2);
        x2 = p3.x;
        y2 = p3.y;
        r1 = d / 2;
      }    
      if (getBit(packedFlags,1)) {//1-filled
        TouchScreenController::tft.fillTriangle(x, y, m1,m2,x2,y2, color);
        if (r2 != 0) {
          //desenha os cantos arredondados
          double multiplier = x < x2 ? 1 : -1;
          TouchScreenController::tft.fillCircle(x,y,r2*1.5, DEFAULT_BACKGROUND_COLOR);        
          TouchScreenController::tft.fillCircle(m1,m2,r2*1.5, DEFAULT_BACKGROUND_COLOR);        
          
          
          if (multiplier > 0) {
            TouchScreenController::tft.fillCircle(x2-r2*0.5,y2,r2*1.5, DEFAULT_BACKGROUND_COLOR);
            TouchScreenController::tft.fillCircle(x+r2,y+r2*1.75,r2, color);
            TouchScreenController::tft.fillCircle(m1+r2,m2-r2*1.75,r2, color);
            TouchScreenController::tft.fillCircle(x2-r2*2,y2,r2, color);
          } else {
            TouchScreenController::tft.fillCircle(x2-r2*0.5*multiplier,y2,r2*1.5, DEFAULT_BACKGROUND_COLOR);
            TouchScreenController::tft.fillCircle(x+r2*multiplier,y+r2*1.75*multiplier,r2, color);
            TouchScreenController::tft.fillCircle(m1+r2*multiplier,m2-r2*1.75*multiplier,r2, color);
            TouchScreenController::tft.fillCircle(x2-r2*2*multiplier,y2,r2, color);
          }
        }
      } else {
        TouchScreenController::tft.drawTriangle(x, y, m1,m2,x2,y2, color);
      }    
    }
  }
}

