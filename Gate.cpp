#include "Gate.h"

void GateInput::setState(const bool& newState, const bool& pDraw) {
  on = newState;
  if (pDraw) {
    draw();
  }
  if (connector != nullptr) {
    if (!connector->isOutput) {
      if (connector->gate != nullptr) {
        connector->gate->calcOutputState();      
      }      
    } else {
      connector->updateOuputInpusState();
    }
  }
}

void GateInput::invertState() {
  setState(!on);
}

void GateInput::draw(const char* params[]){
  color = on ? DEFAULT_GATE_INPUT_ON_COLOR : DEFAULT_GATE_INPUT_OFF_COLOR;
  Button::draw(params);  
}

void GateConnector::initInput(const bool& hasEvent = true){
  if (input == nullptr) {    
    double gcX = x;
    double gcY = getY2();
    if (!isOutput) {
      if (gate->vertical) {        
        if (gate->getLineWidth() > 1) {
          gcY += y;
          gcX += gate->getLineWidth() / 2;
        }
      } else {
        if (gate->getLineWidth() > 1) {
          gcY += y - gate->getLineWidth() / 2;
        }
      }
    } else {
      if (gate->vertical) {
        gcY = y;
        if (gate->getLineWidth() > 1) {
          gcX += gate->getLineWidth() / 2;
        }
      } else {       
        gcX = getX2();
        if (gate->getLineWidth() > 1) {
           gcX += x;
           gcY += y - gate->getLineWidth() / 2;
        }
      }
    }
    input = new GateInput(this,gcX,gcY,gate->getInputRadius());
    input->connector = this;
    input->color = DEFAULT_GATE_INPUT_ON_COLOR;
    input->asCircle();

    if (hasEvent) {
      auto f = [&](){
        input->invertState();
      };
      input->setOnClick(new LambdaCallback<decltype(f)>(f));  
    }
  }
}

void GateConnector::addConnector(GateConnector* pGateConnector,bool addOnDestiny){
  //Serial.println(F("INIT GateConnector::addConnector"));
  //Serial.println(boolToString(isOutput));
  if (connectors == nullptr) {
    //Serial.println("created connectors");
    connectors = new DoubleLinkedList<GateConnector>("Connector");    
  }
  if (pGateConnector != nullptr) {
    //Serial.println("has destiny connector, addeding...");
    connectors->add(pGateConnector);
    if (addOnDestiny) {
      //Serial.println("has destiny-origin connector, addeding...");
      pGateConnector->addConnector(this,false);
    }
  }
  //Serial.println(F("END GateConnector::addConnector"));
}

void GateConnector::draw(const char* params[]) {

  if (isOutput && gate->hasNot) {
    if (gate->vertical) {
      m2 = m2 - (gate->notRadius * 2);
    } else {
      x = x + (gate->notRadius * 2);
    }
  }

  Container::draw(params);


  //draw connector between this output and output input gate
  if (isOutput && connectors != nullptr) {
    Node<GateConnector>* current = connectors->head;
    double x1 = 0;
    double y1 = 0;
    double x2 = 0;
    double y2 = 0;
    if (gate->vertical) {
      x1 = x;
      y1 = y;
    } 
    while(current != nullptr) {
      x2 = x1;
      y2 = y1 - ((y1 - current->data->m2) / 2);
      TouchScreenController::tft.drawLine(
        x1,
        y1,
        x2,
        y2,
        color
      );
      TouchScreenController::tft.drawLine(
        current->data->x,
        current->data->m2,
        current->data->x,
        current->data->m2 + ((y1 - current->data->m2) / 2),
        color
      );
      TouchScreenController::tft.drawLine(
        x1,
        y2,
        current->data->x,
        current->data->m2 + ((y1 - current->data->m2) / 2),
        color
      );
      if (current == current->next) break;
      current = current->next;
    }
  }

  if (input != nullptr) {
    input->draw();    
  } 
}

/**
* To use in circuits, setting output of current gate to connectors connecteds to this output
*/
void GateConnector::updateOuputInpusState(){
  //Serial.println(F("INIT GateConnector::updateOuputInpusState"));
  ///Serial.println(boolToString(isOutput)+","+boolToString(gate != nullptr)+","+boolToString(connectors != nullptr));
  if (gate != nullptr && connectors != nullptr) {
    //Serial.println("has connectors");
    Node<GateConnector>* current = connectors->head;
    while(current != nullptr) {
      if (current->data != nullptr) {
        //Serial.println("passing connector " + String(current->data->id));
        if (current->data->input != nullptr) {
          current->data->input->setState(gate->outputState);
        }
      }
      if (current == current->next) break;
      current = current->next;  
    }
  }
  //Serial.p*rintln(F("END GateConnector::updateOuputInpusState"));
}

Gate::Gate(
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
  Container(pParent,pX,pY,pWidth,pSize),
  inputConnectorCount(pInputConnectorCount),  
  lineWidth(pLineWidth),
  aspectRatio(pAspectRatio),
  baseSizePerc(pBaseSizePerc),
  inputConnectorSize(pInputConnectorSize),  
  outputConnectorSize(pInputConnectorSize),  
  inputConnectorMargin(pInputConnectorMargin)  
{
  //Serial.println(F("INIT Gate::Gate"));
  vertical = pVertical;
  color = pLineColor;
  if (pSize != DEFAULT_GATE_SIZE) {
    if (pWidth == DEFAULT_GATE_WIDTH) {
      m1 = pSize * pAspectRatio;
      inputConnectorMargin = m1 * DEFAULT_GATE_INPUT_CONNECTOR_MARGIN_PERC;      
      notRadius = (m1 + pSize) / 2 * DEFAULT_GATE_NOT_RADIUS_PERC;
      if (notRadius > DEFAULT_GATE_MAX_NOT_RADIUS) {
        notRadius = DEFAULT_GATE_MAX_NOT_RADIUS;
      }
    } 
    if (pInputConnectorSize == DEFAULT_GATE_INPUT_CONNECTOR_SIZE) {
      inputConnectorSize = m2 * DEFAULT_GATE_INPUT_CONNECTOR_SIZE_PERC;   
      outputConnectorSize = inputConnectorSize;   
    }
  }
  if (pAspectRatio != DEFAULT_GATE_ASPECT_RATIO) {
    /*if (pBaseSizePerc == DEFAULT_GATE_BASE_SIZE_PERC) {
      baseSizePerc = pSize * DEFAULT_GATE_BASE_SIZE_PERC;
    }*/
    if (pWidth == DEFAULT_GATE_WIDTH) {      
      m1 = pSize * pAspectRatio;
      inputConnectorMargin = m1 * DEFAULT_GATE_INPUT_CONNECTOR_MARGIN_PERC;
      notRadius = (m1 + pSize) / 2 * DEFAULT_GATE_NOT_RADIUS_PERC;
      if (notRadius > DEFAULT_GATE_MAX_NOT_RADIUS) {
        notRadius = DEFAULT_GATE_MAX_NOT_RADIUS;
      }
    }
  }
  inputRadius = m2 * DEFAULT_GATE_INPUT_RADIUS_PERC;
  //Serial.println("yyyyyyyyy " + String(inputRadius)+"," + String(m2) + "," + String(DEFAULT_GATE_INPUT_RADIUS_PERC)+","+String(m2 * DEFAULT_GATE_INPUT_RADIUS_PERC));
  //Serial.println(F("END Gate::Gate"));
};


Gate::~Gate(){
  if (inputConnectors != nullptr) {
    delete inputConnectors;
    inputConnectors = nullptr;
  }
}

void Gate::initInputConnectors(){
  //Serial.println(F("INIT Gate::initInputConnectors"));
  if (hasInputConnectors && inputConnectorCount > 0 && inputConnectors == nullptr) {
    //Serial.println("ok1");
    inputConnectors = new DoubleLinkedList<GateConnector>("GateConnector");
    //Serial.println("ok2");
    inputConnectors->setDeleteData(false); // avoid double delete    
    //Serial.println("ok3"+String(x));

    double connSpace = 0;
    if (inputConnectorCount == 1) {
      inputConnectorMargin = m1 / 2;
    } else {
      connSpace = (m1 - inputConnectorMargin * 2) / (inputConnectorCount-1);
    }
    //Serial.println("ok4"+String(y));

    double connX = 0;    
    double connY = 0;    
    double connM1 = 0;    
    double connM2 = 0;    
    //Serial.println("ok5");
    for(int i = 0; i < inputConnectorCount; i++) { 
      //Serial.println("passing "+String(i));     
      if (vertical) {
        if (lineWidth > 1) {
          connX = x+inputConnectorMargin+i*connSpace-lineWidth/2;
          connY = y;
          connM1 = lineWidth;
          connM2 = inputConnectorSize;
        } else {
          connX = x+inputConnectorMargin+i*connSpace;
          connY = y;
          connM1 = connX;
          connM2 = y+inputConnectorSize;          
        }        
      } else {//horizontal
        if (lineWidth > 1) {
          connX = x-inputConnectorSize;
          connY = y+inputConnectorMargin+i*connSpace-lineWidth/2;
          connM1 = inputConnectorSize;
          connM2 = lineWidth;
        } else {
          connX = x-inputConnectorSize;
          connY = y+inputConnectorMargin+i*connSpace;
          connM1 = x;
          connM2 = connY;          
        }     
      }

      inputConnectors->add(new GateConnector(
        this,
        connX,
        connY,
        connM1,
        connM2
      )); 
      if (lineWidth > 1) {
        inputConnectors->tail->data->asRectangle();
      } else {
        inputConnectors->tail->data->asLine();
      }
      inputConnectors->tail->data->gate = this;
      inputConnectors->tail->data->pos = i;
      inputConnectors->tail->data->color = color;
      if (hasInputButtons) {
        inputConnectors->tail->data->initInput();
        inputConnectors->tail->data->input->visible = inputConnectors->tail->data->gate->visibleInputs;
      }
    }
  }
  //Serial.println(F("END Gate::initInputConnectors"));
}

void Gate::initOutputConnector(){
  if (inputConnectorsIsVisibles && outputConnector == nullptr) {
    double connX = 0;    
    double connY = 0;    
    double connM1 = 0;    
    double connM2 = 0; 
    if (vertical) {
      if (lineWidth > 1) {
        connX = x+m1/2-lineWidth/2;
        connY = y-m2-outputConnectorSize;
        connM1 = lineWidth;
        connM2 = outputConnectorSize;
      } else {
        connX = x+m1/2;
        connY = y-m2-outputConnectorSize;
        connM1 = connX;
        connM2 = y-m2;        
      }
      if (hasNot) {
        connM2 = connM2 - (notRadius * 2);
      }
    } else {
      if (lineWidth > 1) {
        connX = x+m2;
        connY = y+m1/2-lineWidth/2;
        connM1 = outputConnectorSize;
        connM2 = lineWidth;
      } else {
        connX = x+m2;
        connY = y+m1/2;
        connM1 = connX+outputConnectorSize;
        connM2 = connY;
      }
      if (hasNot) {
        connM1 = connM1 - (notRadius * 2);
      }
    }
    outputConnector = new GateConnector(
      this,
      connX,
      connY,
      connM1,
      connM2
    );
    if (lineWidth > 1) {
      outputConnector->asRectangle();  
    } else {
      outputConnector->asLine();
    }
    outputConnector->isOutput = true;
    outputConnector->color = color;
    outputConnector->gate = this;
    if (hasInputButtons) {
      outputConnector->initInput(false);
    }    
    if (outputConnector->input != nullptr) {
      outputConnector->input->visible = outputConnector->gate->visibleOutput;
      outputConnector->input->setState(outputState,false);//outputstate setted on constructor method, normaly true
    }    
  }
}

const GateConnector* Gate::findGateConnectorByPos(const int& pos) {
  GateConnector* result = nullptr;
  if (hasInputConnectors && inputConnectorCount > 0 && inputConnectors != nullptr) {
    Node<GateConnector>* current = inputConnectors->head;
    while (current != nullptr) {
      if (current->data != nullptr) {
        if (current->data->pos == pos) {
          result = current->data;
          break;
        }
      }
      if (current == current->next) break;
      current = current->next;  
    }
  }
  return result;
}

void Gate::drawInputConnectors() {
  if (hasInputConnectors && inputConnectorCount > 0 && inputConnectors != nullptr && inputConnectorsIsVisibles) {
    Node<GateConnector>* current = inputConnectors->head;
    while (current != nullptr) {
      if (current->data != nullptr) {
        current->data->draw();
      }
      if (current == current->next) break;
      current = current->next;  
    }
  }
}

void Gate::drawOutputConnector() {
  if (inputConnectorsIsVisibles && outputConnector != nullptr && outputConnectorIsVisible) {
    outputConnector->draw();
  }
}

void Gate::drawNot(){
  //Serial.println(F("INIT Gate::drawNot"));
  if (hasNot) {
    double cx = x+m1/2;
    double cy = y-m2-notRadius;
    if (!vertical) {
      cx = x+m2+notRadius;
      cy = y+m1/2;
    }
    TouchScreenController::tft.drawCircle(cx,cy,notRadius,color);
  }
  //Serial.println(F("END Gate::drawNot"));
}

void Gate::drawBody() {
};

void Gate::draw(const char* params[]) {
  //Serial.println(F("INIT Gate::draw"));
  if (hasNot) {
    notRadius = ((m2 + m2 * aspectRatio) / 2) * DEFAULT_GATE_NOT_RADIUS_PERC;
    if (notRadius > DEFAULT_GATE_MAX_NOT_RADIUS) {
      notRadius = DEFAULT_GATE_MAX_NOT_RADIUS;
    }
  }
  initInputConnectors();
  initOutputConnector();
  drawBody();    
  drawInputConnectors();
  drawNot();
  drawOutputConnector();
  //Serial.println(F("END Gate::draw"));
};

bool Gate::calcOutputState() {
  return outputState;
};
