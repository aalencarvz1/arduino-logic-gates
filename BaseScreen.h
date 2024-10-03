#ifndef BASESCREEN_H
#define BASESCREEN_H

#include "TouchScreenController.h"
#include "Container.h"
#include "Button.h"
#include "LambdaCallback.h"

#ifndef DEFAULT_BACKGROUND_COLOR
#define DEFAULT_BACKGROUND_COLOR TFT_BLACK
#endif 

#define DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_WIDTH 1
#define DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_COLOR TFT_WHITE
#define DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN 5
#define DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_RADIUS 10
#define DEFAULT_WINDOW_TITLE_TEXT_SIZE 2
#define DEFAULT_TEXT_COLOR TFT_WHITE

class BaseScreen : public Container{
  protected:
    const char* title = nullptr;
    TextInfo titleInfo;
    bool hasBack = true;
    Button* backButton = nullptr;    
  public: 
    using Container::Container;
    BaseScreen(const char* pTitle = nullptr, const bool& pHasBack = true);
    virtual ~BaseScreen();
    void drawOption(
      const double& pX,
      const double& pY, 
      const double& pR, 
      const int& pColor = TFT_WHITE, 
      const bool& hasPlay = true, 
      const char* pText = nullptr, 
      const void (*pStaticOnClick)() = nullptr, 
      const ICallback* pOnClick = nullptr
    );
    virtual void draw(const char* params[] = nullptr) override;
};

#endif //BASESCREEN_H