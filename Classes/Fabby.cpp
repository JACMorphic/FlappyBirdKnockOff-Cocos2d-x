#include "Fabby.h"
#include "Definitions.h"

USING_NS_CC;

Fabby::Fabby(cocos2d::Layer *layer)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    fabby = Sprite::create("Fabby1.png");
    fabby->setPosition(Point(visibleSize.width/2, visibleSize.height/2));

    auto fabbyBody = PhysicsBody::createCircle(fabby->getContentSize().width/2);
    fabbyBody->setDynamic(true);
    fabbyBody->setCollisionBitmask(FABBY_COLLISION_BITMASK);
    fabbyBody->setContactTestBitmask(true);

    fabby->setPhysicsBody(fabbyBody);

    layer->addChild(fabby);

    isFalling = true;
}

void Fabby::Fall()
{
    if (isFalling == true)
    {
        fabby->setRotation(45);
        //ball->setRotation(90);
        fabby->setPositionX(visibleSize.width/2 + origin.x);
        fabby->setPositionY(fabby->getPositionY() - (FABBY_FALLING_SPEED * visibleSize.height));
    }
    else
    {
        fabby->setRotation(-45);
        fabby->setPositionX(visibleSize.width/2 + origin.x);
        fabby->setPositionY(fabby->getPositionY() + (FABBY_FALLING_SPEED * visibleSize.height));
    }
}
void Fabby::GameOver()
{
    fabby->setRotation(90);
}
