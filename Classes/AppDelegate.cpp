#include "AppDelegate.h"
#include "SplashScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 854);

static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2560, 1600);

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{

}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("FlappyBird KnockOff", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("FlappyBird KnockOff");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    auto screenSize = glview->getFrameSize();
    auto fileUtils = FileUtils::getInstance();
    std::vector<std::string> resDirOrders;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

    if ( 1600 == screenSize.width && 2560 == screenSize.height )
    {
        designResolutionSize = cocos2d::Size(1600, 2560);
        resDirOrders.push_back("large screen");
    }
    if ( 1920 == screenSize.width && 2560 == screenSize.height )
    {
        designResolutionSize = cocos2d::Size(1920, 2560);
        resDirOrders.push_back("large screen");
    }
    if ( 1536 == screenSize.width && 2048 == screenSize.height )
    {
        designResolutionSize = cocos2d::Size(1536, 2048);
        resDirOrders.push_back("large screen");
    }
    if ( 1440 == screenSize.width && 2560 == screenSize.height )
    {
        designResolutionSize = cocos2d::Size(1440, 2560);
        resDirOrders.push_back("1440p x 2560p");
        resDirOrders.push_back("large screen");
    }
    if ( 1200 == screenSize.width && 1920 == screenSize.height )
    {
        designResolutionSize = cocos2d::Size(1200, 1920);
        resDirOrders.push_back("large screen");
    }
    if ( 1080 == screenSize.width && 1400 == screenSize.height )
    {
        designResolutionSize = cocos2d::Size(900, 1400);
        resDirOrders.push_back("large screen");
    }
    else if ( 540 == screenSize.width && 960 == screenSize.height )
    {
        designResolutionSize = cocos2d::Size(540, 960);
        resDirOrders.push_back("large screen");
    }
    else if ( 960 == screenSize.width && 540 == screenSize.height )
    {
        designResolutionSize = cocos2d::Size(800, 1280);
        resDirOrders.push_back("large screen");
    }
    else if ( 800 == screenSize.width && 1280 == screenSize.height )
    {
        designResolutionSize = cocos2d::Size(800, 1280);
        resDirOrders.push_back("large screen");
    }
    else if ( 720 == screenSize.width && 1280 == screenSize.height )
    {
        designResolutionSize = cocos2d::Size(720, 1280);
        resDirOrders.push_back("large screen");
    }
    else if ( 768 == screenSize.width && 1024 == screenSize.height )
    {
        designResolutionSize = cocos2d::Size(768, 1024);
        resDirOrders.push_back("large screen");
    }
    else if ( 640 == screenSize.width && 1136 == screenSize.height )
    {
        designResolutionSize = cocos2d::Size(640, 1136);
        resDirOrders.push_back("large screen");
    }
    else if ( 640 == screenSize.width && 960 == screenSize.height )
    {
        resDirOrders.push_back("large screen");
        designResolutionSize = cocos2d::Size(640, 960);
    }
    else if ( 600 == screenSize.width && 1024 == screenSize.height )
    {
        designResolutionSize = cocos2d::Size(600, 1024);
        resDirOrders.push_back("large screen");
    }
    else if ( 480 == screenSize.width && 854 == screenSize.height )
    {
        resDirOrders.push_back("480p x 800p");
        resDirOrders.push_back("large screen");
        designResolutionSize = cocos2d::Size(480, 854);
    }
    else if ( 480 == screenSize.width && 800 == screenSize.height )
    {
        resDirOrders.push_back("480p x 800p");
        resDirOrders.push_back("large screen");
        designResolutionSize = cocos2d::Size(480, 800);
    }
    else if ( 240 == screenSize.width && 432 == screenSize.height )
    {
        resDirOrders.push_back("small screen");
        designResolutionSize = cocos2d::Size(240, 432);
    }
    else if ( 240 == screenSize.width && 400 == screenSize.height )
    {
        resDirOrders.push_back("small screen");
        designResolutionSize = cocos2d::Size(240, 400);
    }
    else if ( 240 == screenSize.width && 320 == screenSize.height )
    {
        resDirOrders.push_back("small screen");
        designResolutionSize = cocos2d::Size(240, 320);
    }
    else //320 == screenSize.width && 480 == screenSize.height
    {
        resDirOrders.push_back("small screen");
        designResolutionSize = cocos2d::Size(320, 480);
    }
#endif

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    fileUtils->setSearchPaths(resDirOrders);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = SplashScene::createScene();

    fileUtils->setSearchPaths(resDirOrders);

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
