#include "SplashScene.h"
#include "MainMenu.h"
#include "Definitions.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if(!LayerColor::initWithColor(Color4B(255,255,255,255)))
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    cocos2d::Sprite *backgroundSprite;

    backgroundSprite = Sprite::create( "HelloWorld.png" );

    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );

    this->setColor(Color3B(255, 255, 255));
    this->addChild( backgroundSprite );

    this->scheduleOnce( schedule_selector(SplashScene::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE );

    return true;
}

void SplashScene::GoToMainMenuScene(float dt)
{
    auto scene = MainMenu::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
