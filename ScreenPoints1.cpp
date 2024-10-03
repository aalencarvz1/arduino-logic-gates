#include "ScreenPoints1.h"
#include "TouchScreenController.h"
#include "Gates.h"
#include "Button.h"
#include "Colors.h"

const byte ScreenPoints1::SCREEN_ID = 11;

void ScreenPoints1::clearLeftSide(){
  //Serial.println(F("INIT ScreenPoints1::clearLeftSide"));
  double topMargin = 42;
  double sideSapces = 150;
  //left side space
  TouchScreenController::tft.fillRect(
    x+DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_WIDTH,
    y+DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_WIDTH + topMargin,
    sideSapces,
    m2 - DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_WIDTH * 2 - topMargin,
    DEFAULT_BACKGROUND_COLOR
  );
  //Serial.println(F("END ScreenPoints1::clearLeftSide"));
};

void ScreenPoints1::clearRightSide(){
  //Serial.println(F("INIT ScreenPoints1::clearRightSide"));
  double topMargin = 42;
  double sideSapces = 150;
  //right side space
  TouchScreenController::tft.fillRect(
    x + m1 - DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_WIDTH - sideSapces,
    y+DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_WIDTH + topMargin,
    sideSapces,
    m2 - DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_WIDTH * 2 - topMargin,
    DEFAULT_BACKGROUND_COLOR
  );
  //Serial.println(F("END ScreenPoints1::clearRightSide"));
};

void ScreenPoints1::clearCenterSpace(){
  //Serial.println(F("INIT ScreenPoints1::clearCenterSpace"));
  double topMargin = 42;
  double sideSapces = 150;
  //center space
  TouchScreenController::tft.fillRect(
    x + DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_WIDTH + sideSapces,
    y+DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_WIDTH + topMargin,
    m1 - sideSapces * 2,
    m2 - DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_WIDTH * 2 - topMargin,
    DEFAULT_BACKGROUND_COLOR
  );
  //Serial.println(F("END ScreenPoints1::clearCenterSpace"));
};

void ScreenPoints1::clearTopTextSpace(){
  //Serial.println(F("INIT ScreenPoints1::clearTopTextSpace"));
  double topMargin = 42;
  double sideSapces = 150;
  //center top text space
  TouchScreenController::tft.fillRect(
    x + DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_WIDTH + sideSapces - 40,
    y+DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_WIDTH,
    m1 - sideSapces * 2 + 70,
    topMargin,
    DEFAULT_BACKGROUND_COLOR
  );
  //Serial.println(F("END ScreenPoints1::clearTopTextSpace"));
};

void ScreenPoints1::clearGateSpace(Gate* pGate, bool pDelete){
  //Serial.println(F("INIT ScreenPoints1::clearGateSpace"));
  if (pGate != nullptr) {
    TouchScreenController::tft.fillRect(
      pGate->x-DEFAULT_GATE_MAX_INPUT_RADIUS,
      y +  25,//pGate->y-pGate->size-pGate->connectorSize,
      pGate->getWidth()+DEFAULT_GATE_MAX_INPUT_RADIUS*2,
      y + m2 - 55, //pGate->size+2*pGate->connectorSize
      DEFAULT_BACKGROUND_COLOR
    );
    if (pDelete) {
      delete pGate;
      pGate = nullptr;
    }
  } else {
    clearCenterSpace();
  }
  //Serial.println(F("END ScreenPoints1::clearGateSpace"));
};

void ScreenPoints1::drawLevelAndPhaseText(){
  //Serial.println(F("INIT ScreenPoints1::drawLevelAndPhaseText"));
  TouchScreenController::tft.fillRect(
    x+5,
    y+5,
    100,
    50,
    DEFAULT_BACKGROUND_COLOR
  );
  TouchScreenController::tft.setCursor(x+5,y+5);
  TouchScreenController::tft.setTextSize(2);
  TouchScreenController::tft.setTextColor(TFT_CYAN);
  TouchScreenController::tft.print("Nivel " + String(currentDificultyLevel));

  TouchScreenController::tft.setCursor(x+5,y+25);
  TouchScreenController::tft.setTextSize(2);
  TouchScreenController::tft.setTextColor(TFT_DARKGREY);
  TouchScreenController::tft.print("Fase  " + String(currentPhase));
  //Serial.println(F("END ScreenPoints1::drawLevelAndPhaseText"));
}

void ScreenPoints1::drawResult(bool isCorrect, double centerX, double centerY, double size, bool onlyClean) {
  //Serial.println(F("INIT ScreenPoints1::drawResult"));
  int halfSize = size / 2;

  // Limpa a área onde o símbolo será desenhado
  TouchScreenController::tft.fillRect(centerX - halfSize - 2, centerY - halfSize - 2, size + 4, size + 4, DEFAULT_BACKGROUND_COLOR);
  if (!onlyClean) {
    if (isCorrect) {
      // Desenha o símbolo de check verde
      TouchScreenController::tft.drawLine(centerX - halfSize, centerY, centerX - halfSize / 2, centerY + halfSize, TFT_GREEN);
      TouchScreenController::tft.drawLine(centerX - halfSize / 2, centerY + halfSize, centerX + halfSize, centerY - halfSize, TFT_GREEN);
    } else {
      // Desenha o símbolo de X vermelho
      TouchScreenController::tft.drawLine(centerX - halfSize, centerY - halfSize, centerX + halfSize, centerY + halfSize, TFT_RED);
      TouchScreenController::tft.drawLine(centerX + halfSize, centerY - halfSize, centerX - halfSize, centerY + halfSize, TFT_RED);
    }
  }
  //Serial.println(F("END ScreenPoints1::drawResult"));
}

void ScreenPoints1::drawGate(char* gateName, double x, double y, double size, int pConnectorCount, double pGateWidth){
  //Serial.println(F("INIT ScreenPoints1::drawGate"));
  previousGateName = currentGateName;
  currentGateName = gateName;
  clearGateSpace(currentGate);
  drawResult(false,resultX,resultY,resultSize,true);
  currentGate = Gates::createGateByName(
    this,
    gateName,
    x,
    y,
    size,
    pConnectorCount,
    DEFAULT_GATE_VERTICAL_DIRECTION,
    DEFAULT_GATE_LINE_COLOR,
    DEFAULT_GATE_LINE_WIDTH,
    DEFAULT_GATE_ASPECT_RATIO,
    DEFAULT_GATE_BASE_SIZE_PERC,
    DEFAULT_GATE_INPUT_CONNECTOR_SIZE,
    pGateWidth
  );
  if (currentGate != nullptr) {
    currentGate->hasInputButtons = true;
    currentGate->visibleOutput = false;
    currentGate->draw();
  }

  if (gateName != Gates::gateNames[0]) {

  }
  //Serial.println(F("END ScreenPoints1::drawGate"));
}

void ScreenPoints1::drawGateLevel(){
  //Serial.println(F("INIT ScreenPoints1::drawGateLevel"));
  if (currentDificultyLevel <= 4) { //gates

  //clear nivel and phase text
    drawLevelAndPhaseText();

    int idGateName = currentPhase-1;
    int connectorCount = DEFAULT_GATE_INPUT_CONNECTOR_COUNT;
    double gateWidth = DEFAULT_GATE_WIDTH;
    if (currentDificultyLevel == 2) {
      idGateName = random(3,7);
    } else if (currentDificultyLevel > 2) {
      idGateName = random(0,7);
    } 
    if (currentDificultyLevel == 4) {
      connectorCount = random(2,5);
    }
    TouchScreenController::drawCenteredText("Ative a porta",y+10);
    if (idGateName == Gates::gateNames[2]) { //NOT
      connectorCount = 1;
    }
    if (connectorCount > DEFAULT_GATE_INPUT_CONNECTOR_COUNT) {
      gateWidth = gateSize * DEFAULT_GATE_ASPECT_RATIO;
      gateWidth = gateWidth * (1 + ((connectorCount - DEFAULT_GATE_INPUT_CONNECTOR_COUNT) / connectorCount));
    }
    drawGate(Gates::gateNames[idGateName],gateX,gateY,gateSize,connectorCount,gateWidth);
    if (currentDificultyLevel < 3) {
      TouchScreenController::drawCenteredText(Gates::gateNames[idGateName],currentGate->y-currentGate->getHeight()/2);
    }
  }
  //Serial.println(F("END ScreenPoints1::drawGateLevel"));
}

void ScreenPoints1::drawCurrentPontuation(){
  //Serial.println(F("INIT ScreenPoints1::drawCurrentPontuation"));
  TouchScreenController::tft.fillRect(x + m1 - 110, y + DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN + 17,109,19,DEFAULT_BACKGROUND_COLOR);
  char buffer[10]; // Array de char para armazenar o resultado
  itoa(currentPontuation, buffer, 10);
  TouchScreenController::drawCenteredText(buffer,y + DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN + 25,x + m1 - 110 / 2,2,TFT_CYAN);
  //Serial.println(F("END ScreenPoints1::drawCurrentPontuation"));
}

void ScreenPoints1::drawCircuitLevel(){
  //Serial.println(F("INIT ScreenPoints1::drawCircuitLevel"));
  //clean areas
  clearLeftSide();
  clearRightSide();
  clearCenterSpace();
  clearTopTextSpace();
  drawLevelAndPhaseText();

  if (currentCircuit != nullptr) {
    delete currentCircuit;
    currentCircuit = nullptr;
  }
  FREERAM_PRINT;
  if (currentDificultyLevel == 5) {
    if (currentPhase == 1) {
      char* gatesNames[] = {"AND","NOT","BYPASS",nullptr};    
      currentCircuit = new GatesCircuit(
        this,
        x,
        y,
        m1,
        m2,
        2,
        gatesNames
      );
    } else if (currentPhase == 2) {
      char* gatesNames[] = {"NOT","AND",nullptr};  
      currentCircuit = new GatesCircuit(
        this,
        x,
        y,
        m1,
        m2,
        2,
        gatesNames
      );
      //Serial.println("ok2");
    } else if (currentPhase == 3) {
      char* gatesNames[] = {"OR","AND","NOT",nullptr};    
      currentCircuit = new GatesCircuit(
        this,
        x,
        y,
        m1,
        m2,
        2,
        gatesNames
      );
    } else if (currentPhase == 4) {
      char* gatesNames[] = {"AND","AND","XOR",nullptr};    
      currentCircuit = new GatesCircuit(
        this,
        x,
        y,
        m1,
        m2,
        2,
        gatesNames
      );
    } else if (currentPhase == 5) {
      char* gatesNames[] = {"AND","AND","OR",nullptr};    
      currentCircuit = new GatesCircuit(
        this,
        x,
        y,
        m1,
        m2,
        2,
        gatesNames
      );
    } 
  } if (currentDificultyLevel == 6) {
    if (currentPhase == 1) {
      char* gatesNames[] = {"AND","AND","XOR",nullptr};    
      currentCircuit = new GatesCircuit(
        this,
        x,
        y,
        m1,
        m2,
        3,
        gatesNames
      );
      Gate* g = currentCircuit->createGate("BYPASS",nullptr,-1,-1,30);
      g->draw();
      Gate* pg = currentCircuit->gates->tail->prev->data;
      Gate* pg1 = currentCircuit->gates->tail->prev->prev->data;
      g = currentCircuit->createGate("BYPASS",nullptr,pg1->x+(pg->x+30-pg1->x)/2,-1,30);
      //g->addOutputInput(pg->inputs[0]);
      g->initOutputConnector();
      g->outputConnector->addConnector(pg->inputConnectors->head->data);      
      g->draw();
      g = currentCircuit->createGate("BYPASS",nullptr,-1,-1,30);
      g->draw();
    } else if (currentPhase == 2) {
      char* gatesNames[] = {"AND","AND","OR",nullptr};    
      currentCircuit = new GatesCircuit(
        this,
        x,
        y,
        m1,
        m2,
        3,
        gatesNames
      );
      Gate* g = currentCircuit->createGate("BYPASS",nullptr,-1,-1,30);
      g->draw();
      Gate* pg = currentCircuit->gates->tail->prev->data;
      Gate* pg1 = currentCircuit->gates->tail->prev->prev->data;
      g = currentCircuit->createGate("BYPASS",nullptr,pg1->x+(pg->x+30-pg1->x)/2,-1,30);
      //g->addOutputInput(pg->inputs[0]);
      g->initOutputConnector();
      g->outputConnector->addConnector(pg->inputConnectors->head->data);      
      g->draw();
      g = currentCircuit->createGate("BYPASS",nullptr,-1,-1,30);
      g->draw();
    } else if (currentPhase == 3) {
      char* gatesNames[] = {"OR","NAND","AND",nullptr};    
      currentCircuit = new GatesCircuit(
        this,
        x,
        y,
        m1,
        m2,
        2,
        gatesNames
      );
    } else if (currentPhase == 4) {
      char* gatesNames[] = {"OR","NAND","OR",nullptr};    
      currentCircuit = new GatesCircuit(
        this,
        x,
        y,
        m1,
        m2,
        3,
        gatesNames
      );
      Gate* g = currentCircuit->createGate("BYPASS",nullptr,-1,-1,30);
      g->draw();
      Gate* pg = currentCircuit->gates->tail->prev->data;
      Gate* pg1 = currentCircuit->gates->tail->prev->prev->data;
      g = currentCircuit->createGate("BYPASS",nullptr,pg1->x+(pg->x+30-pg1->x)/2,-1,30);
      //g->addOutputInput(pg->inputs[0]);
      g->initOutputConnector();
      g->outputConnector->addConnector(pg->inputConnectors->head->data);      
      g->draw();
      g = currentCircuit->createGate("BYPASS",nullptr,-1,-1,30);
      g->draw();
    } else if (currentPhase == 5) {
      char* gatesNames[] = {"OR","AND","AND","NOT","BYPASS","BYPASS","BYPASS","BYPASS",nullptr};          
      currentCircuit = new GatesCircuit(
        this,
        x,
        y,
        m1,
        m2,
        4,
        gatesNames
      );

      Gate* pg = currentCircuit->gates->tail->prev->prev->data;
      Gate* pg1 = currentCircuit->gates->tail->prev->prev->prev->data;
      Gate* g = currentCircuit->createGate("BYPASS",nullptr,pg1->x+(pg->x-pg1->x)/2,-1);
      //g->addOutputInput(pg->inputs[0]);
      g->initOutputConnector();
      g->outputConnector->addConnector(pg->inputConnectors->head->data);      
      g->draw();
      g = currentCircuit->createGate("NOT");
      g->draw();    
    }
  }
  FREERAM_PRINT;
  //Serial.println(F("END ScreenPoints1::drawCircuitLevel"));
}

/*
LEVELS:
DIFICULTY LEVEL 1 - PHASES 1-3 PORTS AND, OR, NOT WITH NAME
DIFICULTY LEVEL 2 - PHASES 1-4 PORTS NANT,NOR,XOR,XNOR IN RANDOMIC ORDER WITH NAME
DIFICULTY LEVEL 3 - PHASES 1-5 RANDOMIC PORTS WITHOUT NAME
DIFICULTY LEVEL 4 - PHASES 1-5 RANDOMIC PORTS (EXCEPT NOT) WITH 2 - 4 INPUTS 
DIFICULTY LEVEL 5 - PHASES 1-5 RANDOMIC PORTS WITH 2 LEVEL CIRCUIT (2 BASE PORTS + 1 OUTPUT PORT) WITH 2 INPUTS EACH
DIFICULTY LEVEL 6 - PHASES 1-5 RANDOMIC PORTS WITH 2 LEVEL CIRCUIT (2 BASE PORTS + 1 OUTPUT PORT) WITH 3-6 INPUTS EACH
DIFICULTY LEVEL 7+ - PHASES 1+ RANDOMIC PORTS WITH CURRENT LEVEL + 1 EACH 5 LEVELS LEVEL WITH 2-6 INPUTS EACH
*/
void ScreenPoints1::drawNextPhase(){
  //Serial.println(F("INIT ScreenPoints1::drawNextPhase"));
  //freeMemory();
  if (currentDificultyLevel <= 4) { //gates
    drawGateLevel();
  } else { //circuits  
    drawCircuitLevel();
  }
  //Serial.println(F("END ScreenPoints1::drawNextPhase"));
}

void ScreenPoints1::confirm(){
  //Serial.println(F("INIT ScreenPoints1::confirm"));
  if (currentGate != nullptr) {
    currentGate->getOutputConnector()->input->setVisible(true);
    if (currentGate->outputState) {
      currentPontuation++;
      drawCurrentPontuation();
    }
    drawResult(currentGate->outputState,resultX,resultY,resultSize);
    delay(500); //2000
  }
  if (currentPhase >= phasesByLevel[currentDificultyLevel-1]) {
    currentPhase = 1;
    currentDificultyLevel++;
  } else {
    currentPhase++;
  }  
  drawNextPhase();
  //Serial.println(F("END ScreenPoints1::confirm"));
}

void ScreenPoints1::draw(const char* params[]){
  //Serial.println(F("INIT ScreenPoints1::draw"));
  BaseScreen::draw(params); 
  gateSize = m2 * 0.4;
  gateWidth = gateSize * DEFAULT_GATE_ASPECT_RATIO;
  gateX = x + m1 / 2 - gateWidth / 2;//TouchScreenController::tft.width() / 2 - gateWidth / 2;
  gateY = y + m2 - m2 * DEFAULT_GATE_INPUT_CONNECTOR_SIZE_PERC + 15;//TouchScreenController::tft.height() - 75;   

  resultX = x+m1-100;
  resultY = y+m2/2;
  resultSize = 50;

  Button* confirmButton = new Button(this,x+m1-120,0,120,25,3);
  confirmButton->color = Colors::GREEN;
  confirmButton->text ="Confirmar";
  auto f = [this](){
    this->confirm();
  };
  confirmButton->setOnClick(new LambdaCallback<decltype(f)>(f));  
  confirmButton->draw();
  
  TouchScreenController::tft.setCursor(x + m1 - 110, y + 8);
  TouchScreenController::tft.setTextColor(TFT_CYAN);
  TouchScreenController::tft.print("Pontuacao");

  drawCurrentPontuation();

  drawNextPhase();
  //Serial.println(F("END ScreenPoints1::draw"));
};