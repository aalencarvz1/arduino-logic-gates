#ifndef TOUCHSCREENCONTROLLER_H
#define TOUCHSCREENCONTROLLER_H

#include <MCUFRIEND_kbv.h>  // Biblioteca MCUFRIEND_kbv
#include <TouchScreen.h>   // Biblioteca para touchscreen
#include "LambdaCallback.h"
#include "Utils.h"
#include "DoubleLinkedList.h"


//para armazenar informações referente ao dimensionmanto (bounds) de textos em tela
struct TextInfo{
  double x, y;  // Variáveis para armazenar a posição do canto superior esquerdo
  double w, h;  
};

class ClickEvent; //forward declaration to avoid circular dependency

struct TouchScreenController {
  static int nextEventId;

  // Definição dos pinos do touchscreen
  static const int TS_XP  = 8;  // Substitua pelo pino correto
  static const int TS_YP  = A3;//17;//A3;  // Substitua pelo pino correto
  static const int TS_XM  = A2;//16;//A2;  // Substitua pelo pino correto
  static const int TS_YM  = 9;  // Substitua pelo pino correto

  // Definição das variáveis de calibração do touchscreen
  static const int TS_MINX  = 80;
  static const int TS_MAXX  = 960;
  static const int TS_MINY  = 100;
  static const int TS_MAXY  = 930;

  // Configuração do touchscreen
  static TouchScreen ts;

  static MCUFRIEND_kbv tft;

  static DoubleLinkedList<ClickEvent>* clickEvents;


  static void init();
  static int getNextEventId();
  static TextInfo drawCenteredText(
    const char* text, 
    const double& y = 0, 
    const double& centerX = TouchScreenController::tft.width() * 1.0 / 2.0, 
    const double& textSize = 2, 
    const int& color = TFT_WHITE
  );
  /*static void drawRoundButton(
    const double& x,
    const double& y,
    const double& r,
    const int& color,
    const char* text="", 
    const bool& hasCenterPlay=true, 
    const bool& hasBorder=true, 
    const double& textDistance = 20, 
    void (*onClick)() = nullptr
  );*/
  static void drawSmoothArc(
    const double& x_center, 
    const double& y_center, 
    const double& radius, 
    const double& start_angle, 
    const double& end_angle, 
    const int& color = TFT_WHITE
  );
  static CircleInfo drawArcFromArrow(
    const double& x1, 
    const double& y1, 
    const double& x2, 
    const double& y2, 
    const double& arcHeight, 
    const int& color = TFT_WHITE
  );
  static void drawRoundedPlay(
    const double& cx,
    const double& cy,
    const double& r,
    const double& round = 0,
    const int& backgroundColor = TFT_BLACK,
    const int& color = TFT_WHITE,
    const double& multiplier = 1
  );

};

#endif // TOUCHSCREENCONTROLLER_H