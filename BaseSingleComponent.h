#ifndef BASE_SINGLE_COMPONENT_H
#define BASE_SINGLE_COMPONENT_H

extern int currentComponentId;

class BaseContainerComponent; 

class BaseSingleComponent{
  protected:
    bool addedToParent = false;
    BaseContainerComponent* parent = nullptr;
  public:
    int id = 0;
    BaseSingleComponent(const BaseContainerComponent* pParent = nullptr);
    virtual ~BaseSingleComponent();
    void init(const BaseContainerComponent* pParent);
};

#endif //BASE_SINGLE_COMPONENT_H