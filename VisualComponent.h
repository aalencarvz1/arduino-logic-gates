#ifndef VISUAL_COMPONENT_H
#define VISUAL_COMPONENT_H

#include "BaseSingleComponent.h"
#include "TouchScreenController.h"
#include <stdint.h>

#ifndef DEFAULT_BACKGROUND_COLOR
#define DEFAULT_BACKGROUND_COLOR TFT_BLACK
#endif 

class VisualComponent : public virtual BaseSingleComponent{
  protected:
    /*
    packedFlags = 
      0 = bool visible = true;
      1 = bool filled = true;        
      2 = bool isLn = true;
      3 = bool isCirc = false;
      4 = bool isRect = false;
      5 = bool isTriang = false;    
      6 = free
      7 = free
    */
    
    int m1 = 0;//measurement 1 [x2 for line and triangle, widrh for rectangle]
    int m2 = 0;//measurement 2 [y2 for line and triangle, height for rectangle or triangle]            
  public:
    using BaseSingleComponent::BaseSingleComponent;
    /*
    packedFlags = 
      0 = bool visible = true;
      1 = bool filled = true;        
      2 = bool isLn = true;
      3 = bool isCirc = false;
      4 = bool isRect = false;
      5 = bool isTriang = false;  
      6 free
      7 free
    */
    uint8_t packedFlags = 0b00000111;  
    int x = 0;
    int y = 0;
    int r1 = 0; //circle radius or component radius abrangence
    int r2 = 0; //rounded radius
    int color = TFT_WHITE;
    VisualComponent(
      const BaseContainerComponent* pParent,
      const int& pX,
      const int& pY
    ) : 
      BaseSingleComponent(pParent), 
      x(pX), 
      y(pY) 
    {
      init(pParent);
    };
    VisualComponent(
      const BaseContainerComponent* pParent,
      const int& pX,
      const int& pY, 
      const int& pR
    );
    VisualComponent(
      const BaseContainerComponent* pParent,
      const int& pX,
      const int& pY, 
      const int& pWidth,
      const int& pHeight
    );
    VisualComponent(
      const BaseContainerComponent* pParent,
      const int& pX,
      const int& pY, 
      const int& pWidth,
      const int& pHeight,
      const int& pRoundRadius
    );
    
    virtual void draw(const char* params[] = nullptr);
    virtual void setX2(const int& pX2) {m1=pX2;};
    virtual void setY2(const int& pY2) {m2=pY2;};
    virtual void setWidth(const int& pWidth) {m1=pWidth;};
    virtual void setHeight(const int& pHeight) {m2=pHeight;};
    virtual void clearTypeFlags();
    virtual void setVisible(const bool& pVisible, const bool& pDraw = true);
    virtual void asLine();
    virtual void asCircle();
    virtual void asRectangle();
    virtual void asTriangle();
    virtual const int& getX2() const {return m1;};
    virtual const int& getY2() const {return m2;};
    virtual const int& getWidth() const {return m1;};
    virtual const int& getHeight() const {return m2;};
};

#endif // VISUAL_COMPONENT_H