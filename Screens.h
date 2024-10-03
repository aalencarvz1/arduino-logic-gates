#ifndef SCREENS_H
#define SCREENS_H

#include "BaseScreen.h"
#include <StackArray.h>

struct Screens {
  static StackArray <byte> stack;
  static BaseScreen* currentScreen;  
  static void goTo(const byte& screenId,const char* params[] = nullptr);    
  static void goBack(const char* params[] = nullptr);
};

#endif //SCREENS_H