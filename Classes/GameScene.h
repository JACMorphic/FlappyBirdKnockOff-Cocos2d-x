#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Fabby.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite *backgroundSprite1;
    cocos2d::Sprite *backgroundSprite2;
    cocos2d::Action *backgroundSpriteAction1;
    cocos2d::Action *backgroundSpriteAction2;

    void SetPhysicsWorld(cocos2d::PhysicsWorld *world) {sceneWorld = world;};

    bool onContactBegin(cocos2d::PhysicsContact &contact);

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

    void StopFlying(float dt);

    void GameOverUI();

    void update(float dt);

    void PauseOnClicked();

    cocos2d::PhysicsWorld *sceneWorld;

    Fabby *fabby;

    unsigned int score;

    unsigned int isGameOver;

    unsigned int isGamePaused;

    unsigned int pause;

    cocos2d::Label *scoreLabel;

    cocos2d::MenuItemImage *button;

    cocos2d::Sprite *groundSprite1;
    cocos2d::Sprite *groundSprite2;

    cocos2d::Action *groundAction1;
    cocos2d::Action *groundAction2;

    cocos2d::Sprite *topObstacle1;
    cocos2d::Sprite *topObstacle2 ;
    cocos2d::Sprite *bottomObstacle1;
    cocos2d::Sprite *bottomObstacle2;

    float bottomObstaclePosition;

    cocos2d::Action *bottomObstacleAction1;
    cocos2d::Action *bottomObstacleAction2;
    cocos2d::Action *topObstacleAction1;
    cocos2d::Action *topObstacleAction2;

    cocos2d::Sprite *scoreBoardSprite;

    cocos2d::Node *pointNode1;
    cocos2d::Action *pointNodeAction1;
    cocos2d::Node *pointNode2;
    cocos2d::Action *pointNodeAction2;

    SimpleAudioEngine *audio = SimpleAudioEngine::getInstance();
};

#endif // __GAME_SCENE_H__
