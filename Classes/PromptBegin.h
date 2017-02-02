#ifndef __PROMPT_BEGIN_H__
#define __PROMPT_BEGIN_H__

#include "cocos2d.h"

class PromptBegin : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(PromptBegin);
};

#endif // __PROMPT_BEGIN_H__
