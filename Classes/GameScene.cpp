#include "GameScene.h"
#include "Definitions.h"
#include "MainMenu.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    // scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    auto screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();

    isGameOver = 0;
    isGamePaused = 1;

    backgroundSprite1 = Sprite::create("Background.png");
    float scaleY1 = visibleSize.height/backgroundSprite1->getContentSize().height;
    float scaleX1 = visibleSize.width/backgroundSprite1->getContentSize().width;
    if(scaleX1>scaleY1)
    {
        backgroundSprite1->setScale(scaleX1);
    }
    else
    {
        backgroundSprite1->setScale(scaleY1);
    }
    backgroundSprite1->setAnchorPoint(Point(0,0));

    backgroundSprite2 = Sprite::create("Background.png");
    backgroundSprite2->setAnchorPoint(Point(0,0));
    backgroundSprite2->setPosition(Point(backgroundSprite1->getPositionX() + screenSize.width,0));
    float scaleY2 = visibleSize.height/backgroundSprite2->getContentSize().height;
    float scaleX2 = visibleSize.width/backgroundSprite2->getContentSize().width;
    if(scaleX2>scaleY2)
    {
        backgroundSprite2->setScale(scaleX2);
    }
    else
    {
        backgroundSprite2->setScale(scaleY2);
    }

    this->addChild(backgroundSprite1);
    this->addChild(backgroundSprite2);

    backgroundSpriteAction1 = CCRepeatForever::create(CCMoveBy::create(10.0,Point(-visibleSize.width,0)));
    backgroundSprite1->runAction(backgroundSpriteAction1);

    backgroundSpriteAction2 = CCRepeatForever::create(CCMoveBy::create(10.0,Point(-visibleSize.width,0)));
    backgroundSprite2->runAction(backgroundSpriteAction2);


    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));

    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    fabby = new Fabby(this);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    pause = true;
    button = MenuItemImage::create("PauseBTN.png","PlayBTN.png", CC_CALLBACK_0(GameScene::PauseOnClicked, this));
    button->setPosition(Point(visibleSize.width*0.1,visibleSize.height*0.85));

    Menu* menu = Menu::create(button, NULL); // add created button on Menu
    menu ->setPosition(0,0);
    this->addChild(menu,10000);

    score = 0;

    __String *tempScore = __String::createWithFormat("%i", score);

    scoreLabel = Label::createWithTTF( tempScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height/2 * SCORE_FONT_SIZE);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height*0.85+origin.y));

    groundSprite1 = Sprite::create("Ground.png");
    groundSprite1->setAnchorPoint(Point(0,0));


    groundSprite2 = Sprite::create("Ground.png");
    groundSprite2->setAnchorPoint(Point(0,0));
    groundSprite2->setPosition(Point(visibleSize.width,0));


    this->addChild(groundSprite1,10000);
    this->addChild(groundSprite2,10000);


    groundAction1 = CCRepeatForever::create(CCMoveBy::create(10.0,Point(-visibleSize.width,0)));
    groundSprite1->runAction(groundAction1);

    groundAction2 = CCRepeatForever::create(CCMoveBy::create(10.0,Point(-visibleSize.width,0)));
    groundSprite2->runAction(groundAction2);

    auto groundBody1 = PhysicsBody::createBox(groundSprite1->getContentSize());
    groundBody1->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    groundBody1->setContactTestBitmask(true);
    groundBody1->setDynamic(false);
    groundSprite1->setPhysicsBody(groundBody1);

    auto groundBody2 = PhysicsBody::createBox(groundSprite2->getContentSize());
    groundBody2->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    groundBody2->setContactTestBitmask(true);
    groundBody2->setDynamic(false);
    groundSprite2->setPhysicsBody(groundBody2);

    this->addChild(scoreLabel, 10000);

    this->scheduleUpdate();


    //OBSTACLE
    topObstacle1 = Sprite::create("PipeTop.png");
    topObstacle2 = Sprite::create("PipeTop.png");
    bottomObstacle1 = Sprite::create("PipeBottom.png");
    bottomObstacle2 = Sprite::create("PipeBottom.png");

    auto topObstacleBody1 = PhysicsBody::createBox(topObstacle1->getContentSize());
    auto topObstacleBody2 = PhysicsBody::createBox(topObstacle2->getContentSize());
    auto bottomObstacleBody1 = PhysicsBody::createBox(bottomObstacle1->getContentSize());
    auto bottomObstacleBody2 = PhysicsBody::createBox(bottomObstacle2->getContentSize());

    topObstacleBody1->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    bottomObstacleBody1->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    topObstacleBody1->setContactTestBitmask(true);
    bottomObstacleBody1->setContactTestBitmask(true);

    topObstacleBody2->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    bottomObstacleBody2->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    topObstacleBody2->setContactTestBitmask(true);
    bottomObstacleBody2->setContactTestBitmask(true);

    auto random = CCRANDOM_0_1();

    if (random < LOWER_SCREEN_OBSTACLE_THRESHOLD)
    {
        random = LOWER_SCREEN_OBSTACLE_THRESHOLD;
    }
    else if (random > UPPER_SCREEN_OBSTACLE_THRESHOLD)
    {
        random = UPPER_SCREEN_OBSTACLE_THRESHOLD;
    }

    bottomObstaclePosition = ((random+1) * Sprite::create("Ground.png")->getContentSize().height) - (bottomObstacle1->getContentSize().height/2);

    topObstacleBody1->setDynamic(false);
    topObstacleBody2->setDynamic(false);
    bottomObstacleBody1->setDynamic(false);
    bottomObstacleBody2->setDynamic(false);

    topObstacle1->setPhysicsBody(topObstacleBody1);
    topObstacle2->setPhysicsBody(topObstacleBody2);
    bottomObstacle1->setPhysicsBody(bottomObstacleBody1);
    bottomObstacle2->setPhysicsBody(bottomObstacleBody2);


    bottomObstacle1->setPosition(Point(visibleSize.width+topObstacle1->getContentSize().width, bottomObstaclePosition));
    topObstacle1->setPosition(Point(bottomObstacle1->getPositionX(), bottomObstaclePosition + (Sprite::create( "Fabby1.png" )->getContentSize().height * OBSTACLE_GAP)+bottomObstacle1->getContentSize().height));

    bottomObstacle2->setPosition(Point(bottomObstacle1->getContentSize().width+bottomObstacle1->getPositionX()+visibleSize.width/2, bottomObstacle1->getPositionY()));
    topObstacle2->setPosition(Point(topObstacle1->getContentSize().width+topObstacle1->getPositionX()+visibleSize.width/2,topObstacle1->getPositionY()));

    this->addChild(topObstacle1);
    this->addChild(bottomObstacle1);
    this->addChild(topObstacle2);
    this->addChild(bottomObstacle2);

    //OBSTACLE_SPAWN_FREQUENCY * visibleSize.width-OBSTACLE_MOVEMENT_SPEED * visibleSize.width
    bottomObstacleAction1 = CCRepeatForever::create(MoveBy::create(OBSTACLE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0)));
    topObstacleAction1 = CCRepeatForever::create(MoveBy::create(OBSTACLE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0)));

    bottomObstacleAction2= CCRepeatForever::create(MoveBy::create(OBSTACLE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0)));
    topObstacleAction2 = CCRepeatForever::create(MoveBy::create(OBSTACLE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0)));

    topObstacle1->runAction(topObstacleAction1);
    bottomObstacle1->runAction(bottomObstacleAction1);
    topObstacle2->runAction(topObstacleAction2);
    bottomObstacle2->runAction(bottomObstacleAction2);


    pointNode1 = Node::create();
    auto pointBody1 = PhysicsBody::createBox( Size( 1, Sprite::create("Fabby1.png")->getContentSize().height * OBSTACLE_GAP));

    pointBody1->setDynamic( false );
    pointBody1->setCollisionBitmask(POINT_COLLISION_BITMASK);
    pointBody1->setContactTestBitmask( true );

    pointNode1->setPhysicsBody(pointBody1);
    pointNode1->setPosition( Point(topObstacle1->getPositionX(), topObstacle1->getPositionY() - (topObstacle1->getContentSize().height/2) - ((Sprite::create("Fabby1.png")->getContentSize().height * OBSTACLE_GAP)/2)));

    this->addChild(pointNode1);


    pointNode2 = Node::create();
    auto pointBody2 = PhysicsBody::createBox( Size( 1, Sprite::create("Fabby1.png")->getContentSize().height * OBSTACLE_GAP));

    pointBody2->setDynamic( false );
    pointBody2->setCollisionBitmask(POINT_COLLISION_BITMASK);
    pointBody2->setContactTestBitmask( true );

    pointNode2->setPhysicsBody(pointBody2);
    pointNode2->setPosition( Point(topObstacle2->getPositionX(), topObstacle2->getPositionY() - (topObstacle2->getContentSize().height/2) - ((Sprite::create("Fabby1.png")->getContentSize().height * OBSTACLE_GAP)/2)));

    this->addChild(pointNode2);


    pointNodeAction1 = CCRepeatForever::create(MoveBy::create(OBSTACLE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0 )));
    pointNode1->runAction(pointNodeAction1);

    pointNodeAction2 = CCRepeatForever::create(MoveBy::create(OBSTACLE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0 )));
    pointNode2->runAction(pointNodeAction2);

    this->scheduleUpdate();

    return true;
}
void GameScene::PauseOnClicked()
{
    if(pause)
    {
        pause = 0;
        std::cout<<"Pause"<<std::endl;
        button->setNormalImage(Sprite::create("PlayBTN.png"));
        button->setSelectedImage(Sprite::create("PlayBTN.png"));
        backgroundSprite1->stopAction(backgroundSpriteAction1);
        backgroundSprite2->stopAction(backgroundSpriteAction2);
        groundSprite1->stopAction(groundAction1);
        groundSprite2->stopAction(groundAction2);

        topObstacle1->stopAction(topObstacleAction1);
        bottomObstacle1->stopAction(bottomObstacleAction1);
        topObstacle2->stopAction(topObstacleAction2);
        bottomObstacle2->stopAction(bottomObstacleAction2);

        pointNode1->stopAction(pointNodeAction1);
        pointNode2->stopAction(pointNodeAction2);

        audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
    }
    else
    {
        pause = 1;
        std::cout<<"Play"<<std::endl;
        button->setNormalImage(Sprite::create("PauseBTN.png"));
        button->setSelectedImage(Sprite::create("PauseBTN.png"));
        backgroundSpriteAction1 = CCRepeatForever::create(CCMoveBy::create(10.0,Point(-visibleSize.width,0)));
        backgroundSprite1->runAction(backgroundSpriteAction1);

        backgroundSpriteAction2 = CCRepeatForever::create(CCMoveBy::create(10.0,Point(-visibleSize.width,0)));
        backgroundSprite2->runAction(backgroundSpriteAction2);

        groundAction1 = CCRepeatForever::create(CCMoveBy::create(10.0,Point(-visibleSize.width,0)));
        groundSprite1->runAction(groundAction1);

        groundAction2 = CCRepeatForever::create(CCMoveBy::create(10.0,Point(-visibleSize.width,0)));
        groundSprite2->runAction(groundAction2);

        bottomObstacleAction1 = CCRepeatForever::create(MoveBy::create(OBSTACLE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0)));
        topObstacleAction1 = CCRepeatForever::create(MoveBy::create(OBSTACLE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0)));

        bottomObstacleAction2= CCRepeatForever::create(MoveBy::create(OBSTACLE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0)));
        topObstacleAction2 = CCRepeatForever::create(MoveBy::create(OBSTACLE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0)));

        topObstacle1->runAction(topObstacleAction1);
        bottomObstacle1->runAction(bottomObstacleAction1);
        topObstacle2->runAction(topObstacleAction2);
        bottomObstacle2->runAction(bottomObstacleAction2);
        pointNodeAction1 = CCRepeatForever::create(MoveBy::create(OBSTACLE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0 )));
        pointNode1->runAction(pointNodeAction1);

        pointNodeAction2 = CCRepeatForever::create(MoveBy::create(OBSTACLE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0 )));
        pointNode2->runAction(pointNodeAction2);

        audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
    }
}


void GameScene::update(float dt)
{
   Size visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 origin = Director::getInstance()->getVisibleOrigin();
   auto screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();

    if(backgroundSprite1->getPositionX() <= -visibleSize.width)
    {
        backgroundSprite1->setPositionX(backgroundSprite2->getPositionX() + screenSize.width);
    }
    if(backgroundSprite2->getPositionX() <= -visibleSize.width)
    {
      backgroundSprite2->setPositionX(backgroundSprite1->getPositionX() + screenSize.width);
    }

    if(groundSprite1->getPositionX() <= -visibleSize.width+5)
    {
        groundSprite1->setPosition(Point(visibleSize.width,0));
    }
    if(groundSprite2->getPositionX() <= -visibleSize.width+5)
    {
        groundSprite2->setPosition(Point(visibleSize.width,0));
    }




    auto random = CCRANDOM_0_1();

    if (random < LOWER_SCREEN_OBSTACLE_THRESHOLD)
    {
        random = LOWER_SCREEN_OBSTACLE_THRESHOLD;
    }
    else if (random > UPPER_SCREEN_OBSTACLE_THRESHOLD)
    {
        random = UPPER_SCREEN_OBSTACLE_THRESHOLD;
    }

    bottomObstaclePosition = ((random+1) * Sprite::create("Ground.png")->getContentSize().height) - (bottomObstacle1->getContentSize().height/2);
    if(bottomObstacle1->getPositionX() <= -bottomObstacle1->getContentSize().width)
    {
        bottomObstacle1->setPosition(Point(visibleSize.width+topObstacle1->getContentSize().width, bottomObstaclePosition));
    }
    if(topObstacle1->getPositionX() <= -topObstacle1->getContentSize().width)
    {
        topObstacle1->setPosition(Point(bottomObstacle1->getPositionX(), bottomObstaclePosition + (Sprite::create( "Fabby1.png" )->getContentSize().height * OBSTACLE_GAP)+bottomObstacle1->getContentSize().height));
    }

    if(bottomObstacle2->getPositionX() <= -bottomObstacle1->getContentSize().width)
    {
        bottomObstacle2->setPosition(Point(visibleSize.width+topObstacle2->getContentSize().width, bottomObstaclePosition));
    }
    if(topObstacle2->getPositionX() <= -topObstacle2->getContentSize().width)
    {
        topObstacle2->setPosition(Point(bottomObstacle2->getPositionX(), bottomObstaclePosition + (Sprite::create( "Fabby1.png" )->getContentSize().height * OBSTACLE_GAP)+bottomObstacle2->getContentSize().height));
    }

    if(pointNode1->getPositionX() <= -1)
    {
        pointNode1->setPosition(Point(topObstacle1->getPositionX(), topObstacle1->getPositionY() - (topObstacle1->getContentSize().height/2) - ((Sprite::create("Fabby1.png")->getContentSize().height * OBSTACLE_GAP)/2)));
    }
    if(pointNode2->getPositionX() <= -1)
    {
        pointNode2->setPosition(Point(topObstacle2->getPositionX(), topObstacle2->getPositionY() - (topObstacle2->getContentSize().height/2) - ((Sprite::create("Fabby1.png")->getContentSize().height * OBSTACLE_GAP)/2)));
    }

    if(pause)
    {
        fabby->Fall();
    }
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    if ((FABBY_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) || (FABBY_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        if(!isGameOver)
        {
            GameScene::GameOverUI();
            fabby->GameOver();
            isGameOver = 1;
            backgroundSprite1->stopAction(backgroundSpriteAction1);
            backgroundSprite2->stopAction(backgroundSpriteAction2);
            groundSprite1->stopAction(groundAction1);
            groundSprite2->stopAction(groundAction2);

            topObstacle1->stopAction(topObstacleAction1);
            bottomObstacle1->stopAction(bottomObstacleAction1);
            topObstacle2->stopAction(topObstacleAction2);
            bottomObstacle2->stopAction(bottomObstacleAction2);

            auto emptyBody1 = PhysicsBody::createBox(Size(0,0));
            auto emptyBody2 = PhysicsBody::createBox(Size(0,0));
            pointNode1->setPhysicsBody(emptyBody1);
            pointNode2->setPhysicsBody(emptyBody2);


            scoreLabel->setPosition(Point(visibleSize.width/2*1.425,visibleSize.height/2*1.05));

            UserDefault *def = UserDefault::getInstance();

            unsigned int highScore = def->getIntegerForKey("HIGHSCORE", 0);

            if (score > highScore)
            {
                highScore = score;

                def->setIntegerForKey("HIGHSCORE", highScore);
            }

            def->flush();

            __String *tempHighScore = __String::createWithFormat("%i", highScore);
            auto highScoreLabel = LabelTTF::create( tempHighScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height/2 * SCORE_FONT_SIZE);
            highScoreLabel->setColor( Color3B::WHITE );
            highScoreLabel->setPosition(Point(scoreLabel->getPositionX(),scoreLabel->getPositionY()*0.825));
            this->addChild(highScoreLabel);

            audio->playEffect("sound/hit.wav", false, 1.0f, 1.0f, 1.0f);
        }
    }
    else if ((FABBY_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask()) || (FABBY_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        score++;

        __String *tempScore = __String::createWithFormat("%i", score);

        scoreLabel->setString(tempScore->getCString());

        audio->playEffect("sound/point.wav", false, 1.0f, 1.0f, 1.0f);

    }

    return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event )
{
    if(!isGameOver)
    {
        fabby->Fly();

        this->scheduleOnce(schedule_selector(GameScene::StopFlying ), FABBY_FLY_DURATION);

        if(pause)
            audio->playEffect("sound/wing.wav", false, 1.0f, 1.0f, 1.0f);
    }

    return true;
}

void GameScene::StopFlying(float dt)
{
    fabby->StopFlying();
}

void GameScene::GameOverUI()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    button->removeFromParent();

    auto titleSprite = Sprite::create("GameOverTitle.png");
    titleSprite->setPosition(Point(visibleSize.width/2, visibleSize.height/2*1.40));
    this->addChild(titleSprite);

    scoreBoardSprite = Sprite::create("ScoreBoard.png");
    scoreBoardSprite->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    this->addChild(scoreBoardSprite);


    ui::Button *okButton = ui::Button::create("OkBTN.png");
    okButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
    {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,MainMenu::createScene()));
                break;

            case ui::Widget::TouchEventType::ENDED:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,MainMenu::createScene()));
                break;

            case ui::Widget::TouchEventType::CANCELED:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,MainMenu::createScene()));
                break;

            case ui::Widget::TouchEventType::MOVED:
                audio->playEffect("sound/swooshing.wav", false, 1.0f, 1.0f, 1.0f);
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,MainMenu::createScene()));
                break;

            default:
                break;
        }
    });
    okButton->setPosition(Point(visibleSize.width/2-scoreBoardSprite->getContentSize().height+okButton->getContentSize().width/2,visibleSize.height/2-scoreBoardSprite->getContentSize().height*0.75));
    this->addChild(okButton,10001);

    ui::Button *shareButton = ui::Button::create("ShareBTN.png");
    shareButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
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
    shareButton->setPosition(Point(visibleSize.width/2+scoreBoardSprite->getContentSize().height/2+shareButton->getContentSize().width/2,visibleSize.height/2-scoreBoardSprite->getContentSize().height*0.75));
    this->addChild(shareButton,10001);
}
