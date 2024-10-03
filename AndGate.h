#ifndef ANDGATE_H
#define ANDGATE_H

#include "Gate.h"

class AndGate : public Gate {
  public: 
    using Gate::Gate;
    virtual void drawBody() override;
    virtual bool calcOutputState() override;
};

#endif //ANDGATE_H
