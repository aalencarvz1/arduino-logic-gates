#ifndef CLICKEVENT_H
#define CLICKEVENT_H

#include "VisualComponent.h"
#include "LambdaCallback.h"

class ClickEvent {  
  protected:     
    VisualComponent* component;
    int xc = 0;
    int yc = 0; 
    int r = 0;    
    void (*staticOnClick)() = nullptr;
    ICallback* onClickCallback = nullptr;  // Ponteiro para o callback
    virtual void initEvent();
  public:
    int id = -1;
    bool enabled = true;
    ClickEvent(
      const VisualComponent* pComponent,
      const void (*pStaticOnClick)() = nullptr
    );  
    ClickEvent(
      const VisualComponent* pComponent,
      const ICallback* pOnClickCallback = nullptr
    );  

    virtual ~ClickEvent();
    virtual bool checkClickEvent(const int& x,const int& y);
    virtual void setArea(const int& pXc, const int& pYc,const int& pR);
};

#endif //CLICKEVENT_H