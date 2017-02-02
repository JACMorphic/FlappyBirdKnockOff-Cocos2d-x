#ifndef __FABBY_H__
#define __FABBY_H__

#include "SimpleAudioEngine.h"
#include "cocos2d.h"

using namespace CocosDenshion;

class Fabby
{
  public:
    Fabby( cocos2d::Layer *layer );

    void Fall();
    void Fly(){isFalling = false;};
    void StopFlying(){isFalling = true;}
    void GameOver();

  private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite *fabby;

    bool isFalling;
};

#endif // __FABBY_H__
