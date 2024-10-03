#include "TouchScreenController.h"
#include <math.h>
#include "ClickEvent.h"


//STATIC INITIALIZATIONS
int TouchScreenController::nextEventId = -1;
MCUFRIEND_kbv TouchScreenController::tft;
TouchScreen TouchScreenController::ts = TouchScreen(TouchScreenController::TS_XP, TouchScreenController::TS_YP, TouchScreenController::TS_XM, TouchScreenController::TS_YM, 300);
DoubleLinkedList<ClickEvent>* TouchScreenController::clickEvents = nullptr;


/**
* TouchScreenController
*/
void TouchScreenController::init(){
    // Configuração do touchscreen
    // Inicializa o TFT    
    int identifier = tft.readID();
    //Serial.println("TFT SHIELD IDENTIFIER: "+String(identifier));
    if (identifier == 0x9325 || identifier == 0x9341 || identifier == 0x9486 || identifier == 0x7796) {
      tft.begin(identifier);
    } else {
      tft.begin(0x9486);  // Força o uso de um controlador comum, se necessário
    }
    tft.setRotation(1);  // Ajuste a rotação conforme necessário
    clickEvents = new DoubleLinkedList<ClickEvent>("ClickEvent");
};

int TouchScreenController::getNextEventId(){
  nextEventId++;
  return nextEventId;
}

TextInfo TouchScreenController::drawCenteredText(
  const char* text, 
  const double& y = 0, 
  const double& centerX = TouchScreenController::tft.width() * 1.0 / 2.0, 
  const double& textSize = 2, 
  const int& color = TFT_WHITE
) {
    // Defina o tamanho da fonte
    tft.setTextSize(textSize);
    tft.setTextColor(color);

    // Calcule a largura e altura do texto com base no tamanho da fonte
    double textWidth = strlen(text) * 6.0 * textSize;  // Cada caractere tem aproximadamente 6px de largura na fonte padrão
    double textHeight = 8.0 * textSize;  // A altura da fonte padrão é de aproximadamente 8px

    // Calcule as coordenadas para centralizar o texto
    double x = centerX - (textWidth / 2.0);
    
    // Desenhe o texto no TFT
    tft.setCursor(x, y-3*textSize); //3 = half vertical size character at text size = 1
    tft.print(text);

    // Retorne as informações do texto
    TextInfo result;
    result.x = x;
    result.y = y;
    result.w = textWidth;
    result.h = textHeight;
    return result;
};

/*void TouchScreenController::drawRoundButton(
  const double& x,
  const double& y,
  const double& r,
  const int& color,
  const char* text, 
  const bool& hasCenterPlay,
  const bool& hasBorder,
  const double& textDistance,
  void (*onClick)()
) {
  if (hasBorder) {
    tft.drawCircle(x,y,r,color);
    tft.drawCircle(x,y,r-1.0,color);
    tft.fillCircle(x,y,r*0.8,color);
  } else {
    tft.fillCircle(x,y,r,color);
  }

  DPoint p1;
  double playR = r * 0.3;
  p1.x = (x - playR) + (r * 0.1);
  if (hasCenterPlay) {
    int playColor = TFT_BLACK;    
    double arred = r * 0.05;

    //define os pontos do triangulo do play
    DPoint p2,p3;    
    p1.y = y - playR;
    p2.x = p1.x;
    p2.y = y + playR;
    p3.x = x + playR + (r * 0.1);
    p3.y = y;

    //desenha o play
    tft.fillTriangle(p1.x,p1.y, p2.x,p2.y, p3.x,p3.y , playColor);

    //desenha os cantos arredondados
    tft.fillCircle(p1.x,p1.y,arred*2.0, color);
    tft.fillCircle(p1.x+arred*0.8,p1.y+arred*1.70,arred, playColor);
    tft.fillCircle(p2.x,p2.y,arred*2.0, color);
    tft.fillCircle(p2.x+arred*0.8,p2.y-arred*2,arred, playColor);
    tft.fillCircle(p3.x,p3.y,arred*2.0, color);
    tft.fillCircle(p3.x-arred*2.3,p3.y,arred, playColor);
  }
  if (text != "") {
    drawCenteredText(text,y+r+textDistance,x);
  }
  if (onClick != nullptr) {
    //FREERAM_PRINT;
    new ClickEvent(nullptr,onClick);
    //FREERAM_PRINT;
  }
};*/

void TouchScreenController::drawSmoothArc(
  const double& x_center, 
  const double& y_center, 
  const double& radius, 
  const double& start_angle, 
  const double& end_angle, 
  const int& color
) {
  double angle;   // Ângulo atual em radianos
  double x_last = -1.0, y_last = -1.0;  // Últimas coordenadas desenhadas para garantir continuidade

  // Convertendo ângulos de graus para radianos
  double start_rad = start_angle * (PI / 180.0);
  double end_rad = end_angle * (PI / 180.0);

  // Caminhar ao longo do arco, aumentando o ângulo gradualmente
  for (angle = start_rad; angle <= end_rad; angle += 0.005) {
    double x = x_center + radius * cos(angle);  // Cálculo da coordenada X
    double y = y_center + radius * sin(angle);  // Cálculo da coordenada Y

    // Desenha o pixel apenas se for uma nova coordenada (evitar sobreposição)
    if (x != x_last || y != y_last) {
      tft.drawPixel(x, y, color);  // Desenha o pixel na posição (x, y)
      x_last = x;
      y_last = y;
    }
  }
};

CircleInfo TouchScreenController::drawArcFromArrow(
  const double& x1, 
  const double& y1, 
  const double& x2, 
  const double& y2, 
  const double& arcHeight, 
  const int& color
) {  
  DPoint p1,p2;
  p1.x = x1;
  p1.y = y1;
  p2.x = x2;
  p2.y = y2;

  double width = sqrt(pow(abs(x2-x1),2.0) + pow(abs(y2-y1),2.0));
  double r = 0.0;
  double baseAdjust = 0.0;
  double centralAngle = 270.0; //arco na horizontal, flexa na vertical y1 = y2 --- 
  if (y1 != y2) {
    if (x1 == x2) {// arco na vertical, flexa na horizontal |      
      centralAngle = 0.0;
      if (y1 > y2) {
        centralAngle = 180.0; //arco na vertical, flexa na horizontal, apontando para a esquerda
      }
    } else {
      double hT = abs(y1-y2); //cateto vertical
      double wT = abs(x1-x2); //cateto horizontal
      double a1 = atan(hT/wT) * (180.0 / M_PI); //angulo oposto ao cateto vertical
      //Serial.println("ht="+String(hT)+",wt="+String(wT)+",a1="+String(a1));
      if (x1 <= x2) { //flexa/arco para esquerda e para cima
        if (y1 <= y2) { //de 180 a 360
          centralAngle = 360.0 - (90-a1);
        } else {
          centralAngle = 180.0 + (90-a1);
        } 
      } else {//flexa do arco para esquerda
        if (y1 <= y2) {
          centralAngle = 90-a1;
        } else {
          centralAngle = 90.0 + (90-a1);
        }
      }
    }
  } else if (x1 > x2) {
    centralAngle = 90.0; //flexa apontando para baixo
  }
  if (arcHeight >= width/2.0) {
    r = width / 2.0;
    baseAdjust = arcHeight - r;
  } else {
    r = (arcHeight * arcHeight + pow(width/2.0,2.0)) / (2.0 * arcHeight);
  }
  double py2 = pow(r,2.0);
  py2 = pow(r,2.0) - pow(width /2.0,2.0);
  py2 = sqrt(py2);
  double arcAngle = getArcAngle(width,r);
  double startAngle = centralAngle-(arcAngle/2.0);

  DPoint pc = calcularP3(width,r,r,p1,p2);
  CircleInfo result;
  result.x = pc.x;
  result.y = pc.y;
  result.r = r;
  drawSmoothArc(pc.x,pc.y,r,startAngle,startAngle+arcAngle,color);    
  return result;
};

static void TouchScreenController::drawRoundedPlay(
  const double& cx,
  const double& cy,
  const double& r,
  const double& round,
  const int& backgroundColor,
  const int& color,
  const double& multiplier
) {
  double angulo1 = 0;  // Vértice apontando para a direita (ponta do play)
  double angulo2 = 2 * M_PI / 3;  // 120 graus (em radianos)
  double angulo3 = 4 * M_PI / 3;  // 240 graus (em radianos)

  //define os pontos do triangulo do play
  // Coordenadas dos três vértices (p1, p2, p3)
  double x1 = cx + r * cos(angulo1) * multiplier;
  double y1 = cy + r * sin(angulo1) * multiplier;
  
  double x2 = cx + r * cos(angulo2) * multiplier;
  double y2 = cy + r * sin(angulo2) * multiplier;
  
  double x3 = cx + r * cos(angulo3) * multiplier;
  double y3 = cy + r * sin(angulo3) * multiplier;
  

  //desenha o play
  tft.fillTriangle(x1,y1, x2,y2, x3,y3 , color);
  if (round > 0) {
    //desenha os cantos arredondados
    tft.fillCircle(x1,y1,round*1.5, backgroundColor);
    tft.fillCircle(x1-round*1.8*multiplier,y1,round, color);
    tft.fillCircle(x2,y2,round*1.5, backgroundColor);
    tft.fillCircle(x2+round*multiplier,y2-round*1.75*multiplier,round, color);
    tft.fillCircle(x3,y3,round*1.5, backgroundColor);
    tft.fillCircle(x3+round*multiplier,y3+round*1.75*multiplier,round, color);
  }
}



