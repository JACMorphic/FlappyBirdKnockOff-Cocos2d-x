#include "PromptBegin.h"
#include "GameScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* PromptBegin::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PromptBegin::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PromptBegin::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto s_visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    

    auto backgroundSprite = Sprite::create("Background.png");
    float scaleY = s_visibleRect.size.height/backgroundSprite->getContentSize().height;
    float scaleX = s_visibleRect.size.width/backgroundSprite->getContentSize().width;
    if(scaleX>scaleY)
    {
        backgroundSprite->setScale(scaleX);
    }
    else
    {
        backgroundSprite->setScale(scaleY);
    }
    backgroundSprite->setAnchorPoint(Point(0,0));
    this->addChild(backgroundSprite);

    auto button = Sprite::create("PauseBTN.png");
    button->setPosition(Point(visibleSize.width*0.1,visibleSize.height*0.85));
    this->addChild(button,10000);

    auto scoreLabel = Label::createWithTTF( "0", "fonts/Marker Felt.ttf", visibleSize.height/2 * SCORE_FONT_SIZE);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height*0.85+origin.y));

    auto listener = EventListenerTouchOneByOne::create();

    auto ball = Sprite::create("Fabby1.png");
    ball->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(ball);   

    auto tap = Sprite::create("FabbyTapToBegin.png");
    tap->setPosition(Point((visibleSize.width/2)*1.25,(visibleSize.height/2)*1.005));
    this->addChild(tap); 

    auto groundSprite = Sprite::create("Ground.png");
    groundSprite->setAnchorPoint(Point(0,0));
    this->addChild(groundSprite); 

    listener->onTouchBegan = [](Touch* touch, Event* event)
    {
        Director::getInstance()->replaceScene(GameScene::createScene());
        return true; // if you are consuming it
    };

    listener->onTouchMoved = [](Touch* touch, Event* event)
    {
        Director::getInstance()->replaceScene(GameScene::createScene());
    };

    listener->onTouchEnded = [=](Touch* touch, Event* event)
    {
        Director::getInstance()->replaceScene(GameScene::createScene());
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->addChild(scoreLabel, 10000);

    return true;
}
