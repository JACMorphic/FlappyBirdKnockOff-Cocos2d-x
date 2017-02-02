#include "MainMenu.h"
#include "PromptBegin.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //auto s_visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();

    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setAnchorPoint(Point(0,0));
    backgroundSprite = Sprite::create("Background.png");
    float scaleY1 = visibleSize.height/backgroundSprite->getContentSize().height;
    float scaleX1 = visibleSize.width/backgroundSprite->getContentSize().width;
    if(scaleX1>scaleY1)
    {
        backgroundSprite->setScale(scaleX1);
    }
    else
    {
        backgroundSprite->setScale(scaleY1);
    }
    backgroundSprite->setAnchorPoint(Point(0,0));
    this->addChild(backgroundSprite);

    auto titleSprite = Sprite::create("FlappyBirdTitle.png");
    titleSprite->setPosition(Point(visibleSize.width/2,(visibleSize.height/2)*1.40));
    this->addChild(titleSprite);

    auto groundSprite = Sprite::create("Ground.png");
    groundSprite->setAnchorPoint(Point(0,0));
    this->addChild(groundSprite);

    ui::Button* startButton = ui::Button::create("StartBTN.png");
    startButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
    {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                break;

            case ui::Widget::TouchEventType::ENDED:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                Director::getInstance()->replaceScene(PromptBegin::createScene());
                break;

            case ui::Widget::TouchEventType::CANCELED:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                Director::getInstance()->replaceScene(PromptBegin::createScene());
                break;

            case ui::Widget::TouchEventType::MOVED:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                Director::getInstance()->replaceScene(PromptBegin::createScene());
                break;

            default:
                break;
        }
    });
    startButton->setPosition(Point((visibleSize.width/2)-startButton->getContentSize().width,(groundSprite->getContentSize().height)*1.15));
    this->addChild(startButton);

    ui::Button* scoreButton = ui::Button::create("ScoreBTN.png");
    scoreButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
    {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                break;

            case ui::Widget::TouchEventType::ENDED:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                break;

            case ui::Widget::TouchEventType::CANCELED:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                break;

            case ui::Widget::TouchEventType::MOVED:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                break;

            default:
                break;
        }
    });
    scoreButton->setPosition(Point((visibleSize.width/2)+(scoreButton->getContentSize().width/2),(groundSprite->getContentSize().height)*1.15));
    this->addChild(scoreButton);

    ui::Button* rateButton = ui::Button::create("RateBTN.png");
    rateButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
    {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                break;

            case ui::Widget::TouchEventType::ENDED:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                break;

            case ui::Widget::TouchEventType::CANCELED:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                break;

            case ui::Widget::TouchEventType::MOVED:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                break;

            default:
                break;
        }
    });
    rateButton->setPosition(Point((visibleSize.width/2)+(rateButton->getContentSize().width/2),(groundSprite->getContentSize().height)*1.375));
    this->addChild(rateButton);

    // creating a keyboard event listener
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MainMenu::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(MainMenu::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// Implementation of the keyboard event callback function prototype
void MainMenu::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        Director::getInstance()->end();
        exit(0);
    }
}

void MainMenu::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        Director::getInstance()->end();
        exit(0);
    }
}
