#ifndef GATE_H
#define GATE_H

#include "Container.h"
#include "DoubleLinkedList.h"
#include "Button.h"


#define DEFAULT_GATE_SIZE 150.0
#define DEFAULT_GATE_INPUT_CONNECTOR_COUNT 2
#define DEFAULT_GATE_VERTICAL_DIRECTION true
#define DEFAULT_GATE_LINE_COLOR TFT_WHITE
#define DEFAULT_GATE_LINE_WIDTH 1.0
#define DEFAULT_GATE_ASPECT_RATIO 1.0
#define DEFAULT_GATE_BASE_SIZE_PERC 0.5
#define DEFAULT_GATE_BASE_CURVE_PERC 0.3

#define DEFAULT_GATE_INPUT_CONNECTOR_MARGIN_PERC 0.1
#define DEFAULT_GATE_INPUT_CONNECTOR_SIZE_PERC 0.3
#define DEFAULT_GATE_WIDTH DEFAULT_GATE_SIZE * DEFAULT_GATE_ASPECT_RATIO
#define DEFAULT_GATE_INPUT_CONNECTOR_SIZE DEFAULT_GATE_SIZE * DEFAULT_GATE_INPUT_CONNECTOR_SIZE_PERC
#define DEFAULT_GATE_INPUT_CONNECTOR_MARGIN DEFAULT_GATE_WIDTH * DEFAULT_GATE_INPUT_CONNECTOR_MARGIN_PERC

#define DEFAULT_GATE_MIN_ARC_HEIGHT_PERC 0.2
#define DEFAULT_GATE_BASE_ARC_HEIGHT_ASPECT_RATIO 0.3
#define DEFAULT_GATE_MIN_OR_BASE_SIZE_PERC 0.3
#define DEFAULT_GATE_MAX_OR_BASE_SIZE_PERC 0.6
#define DEFAULT_GATE_NOT_RADIUS_PERC 0.12
#define DEFAULT_GATE_MAX_NOT_RADIUS 8.0
#define DEFAULT_GATE_EXCLUSIVE_SPACE_PERC 0.1

#define DEFAULT_GATE_INPUT_OFF_COLOR TFT_RED
#define DEFAULT_GATE_INPUT_ON_COLOR TFT_GREEN
#define DEFAULT_GATE_INPUT_RADIUS_PERC 0.15
#define DEFAULT_GATE_MIN_INPUT_RADIUS 8.0
#define DEFAULT_GATE_MAX_INPUT_RADIUS 30.0

class GateConnector; //forward declaration

class GateInput : public Button {
  protected:
    bool on = false;
  public:
    using Button::Button;    
    int offColor = DEFAULT_GATE_INPUT_OFF_COLOR;
    GateConnector* connector = nullptr;
    virtual void setState(const bool& newState, const bool& pDraw = true);
    virtual const bool& getState() const {return on;};    
    virtual void invertState();   
    virtual void draw(const char* params[] = nullptr) override; 
};

class Gate; //forward declaration

class GateConnector : public Container {  
 public:
    using Container::Container;
    bool isOutput = false;
    int pos = 0;
    Gate* gate = nullptr;
    GateInput* input = nullptr;
    DoubleLinkedList<GateConnector>* connectors = nullptr;
    virtual void initInput(const bool& hasEvent = true);
    virtual void draw(const char* params[] = nullptr) override;
    virtual void updateOuputInpusState();
    virtual void addConnector(GateConnector* pGateConnector, bool addOnDestiny = true);
};

class Gate : public Container{
  public:
    using Container::Container;
    int inputConnectorCount = DEFAULT_GATE_INPUT_CONNECTOR_COUNT;    
    double lineWidth = DEFAULT_GATE_LINE_WIDTH;
    double aspectRatio = DEFAULT_GATE_ASPECT_RATIO;
    double baseSizePerc = DEFAULT_GATE_BASE_SIZE_PERC;

    double inputConnectorSize = DEFAULT_GATE_SIZE * DEFAULT_GATE_INPUT_CONNECTOR_SIZE_PERC;   
    double outputConnectorSize = DEFAULT_GATE_SIZE * DEFAULT_GATE_INPUT_CONNECTOR_SIZE_PERC;   

    double arcHeight = DEFAULT_GATE_SIZE * (1.0-DEFAULT_GATE_BASE_SIZE_PERC);
    double baseAdjust = 0.0;

    bool vertical = DEFAULT_GATE_VERTICAL_DIRECTION;    
    bool hasInputConnectors = true;
    bool inputConnectorsIsVisibles = true;    
    bool hasOutputConnector = true;
    bool outputConnectorIsVisible = true;
    bool hasInputButtons = true;
    bool visibleInputs = true;
    bool visibleOutput = true;
    bool hasNot = false;
    bool exclusive = false;            
    bool outputState = false;
    

    double inputConnectorMargin;
    double notRadius = 0;    
    double inputRadius = DEFAULT_GATE_SIZE * DEFAULT_GATE_INPUT_RADIUS_PERC;    
    DoubleLinkedList<GateConnector>* inputConnectors = nullptr;
    GateConnector* outputConnector = nullptr;
    int currentCircuitLevel = 0;
    Gate(
      const BaseContainerComponent* pParent,
      const double& pX                = 150.0, 
      const double& pY                = 250.0,
      const double& pSize             = DEFAULT_GATE_SIZE,
      const int& pInputConnectorCount = DEFAULT_GATE_INPUT_CONNECTOR_COUNT,	
      const bool& pVertical           = DEFAULT_GATE_VERTICAL_DIRECTION,
      const int& pLineColor           = DEFAULT_GATE_LINE_COLOR,
      const double& pLineWidth        = DEFAULT_GATE_LINE_WIDTH,
      const double& pAspectRatio      = DEFAULT_GATE_ASPECT_RATIO,
      const double& pBaseSizePerc     = DEFAULT_GATE_BASE_SIZE_PERC,
      const double& pInputConnectorSize    = DEFAULT_GATE_INPUT_CONNECTOR_SIZE,
      const double& pWidth            = DEFAULT_GATE_WIDTH,
      const double& pInputConnectorMargin  = DEFAULT_GATE_INPUT_CONNECTOR_MARGIN
    );
    virtual ~Gate();
    virtual void initInputConnectors();
    virtual void initOutputConnector();
    //virtual void setHasInputConnectors(const bool& pHasInputConnectors) {hasInputConnectors=pHasInputConnectors;};
    //virtual void setHasInputButtons(const bool& pHasInputButtons) {hasInputButtons=pHasInputButtons;};
    //virtual void setIsVisibleInputs(const bool& pIsVisibleInputs) {visibleInputs=pIsVisibleInputs;};
    //virtual void setIsVisibleOutput(const bool& pIsVisibleOutput) {visibleOutput=pIsVisibleOutput;};
    //virtual void setHasNot(const bool& pHasNot);
    //virtual void setCurrentCircuitLevel(const int& pCurrentCircuitLevel) {currentCircuitLevel=pCurrentCircuitLevel;};
    //virtual const bool& isVisibleInputs() const {return visibleInputs;};
    //virtual const bool& isVertical() const {return vertical;};
    virtual const GateConnector* getOutputConnector() const {return outputConnector;};
    //virtual const bool& getOutputState() const {return outputState;};
    virtual const double& getInputRadius() const {return inputRadius;};
    virtual const double& getLineWidth() const {return lineWidth;};
    virtual const int& getInputConnectorCount() const {return inputConnectorCount;};
    virtual const int& getCurrentCircuitLevel() const {return currentCircuitLevel;};
    virtual const double& getInputConnectorSize() const {return inputConnectorSize;};
    virtual const GateConnector* findGateConnectorByPos(const int& pos);
    virtual void drawInputConnectors();
    virtual void drawOutputConnector();
    virtual void drawBody();     
    void drawNot(); 
    virtual void draw(const char* params[] = nullptr) override;
    virtual bool calcOutputState();
};

#endif //GATE_H