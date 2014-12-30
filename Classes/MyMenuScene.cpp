#include "MyMenuScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameLoadingScene.h"

#define AboutScene           2

// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define EFFECT_FILE        "effect1.ogg"
#elif( CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
#define EFFECT_FILE        "effect1.raw"
#else
#define EFFECT_FILE        "effect1.wav"
#endif // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define MUSIC_FILE1        "startbg.mp3"
#define MUSIC_FILE2        "gamebgm.mp3"
#define LOADING_MUSIC   "loading.mp3"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX )
#define MUSIC_FILE        "background.ogg"
#define LOADING_MUSIC   "loading.ogg"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#define MUSIC_FILE        "background.wav"
#define LOADING_MUSIC   "loading.wav"
#else
#define MUSIC_FILE1        "startbg.mp3"
#define MUSIC_FILE2        "gamebgm.mp3"
#define LOADING_MUSIC   "loading.mp3"

#endif // CC_PLATFORM_WIN32
#define LINE_SPACE

USING_NS_CC;
using namespace CocosDenshion;
bool MyMenu::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


    CCSprite* pTitle = CCSprite::create("title.png");
    pTitle->setPosition(ccp(420.0f, 637.0f));
    this->addChild(pTitle, 1);

    CCMenuItemImage* pStart = CCMenuItemImage::create("button/startgameNormal.png", 
                                                                                                "button/startgameSelected.png",
                                                                                                this, 
                                                                                                menu_selector(MyMenu::__gameStartCallback));
    pStart->setPosition(ccp(270.0f, 440.0f));
    
    CCMenuItemImage* pAbout = CCMenuItemImage::create("button/about.png", 
                                                                                                    "button/aboutSelected.png", 
                                                                                                    this, 
                                                                                                    menu_selector(MyMenu::__menuAboutCallback));
    pAbout->setPosition(ccp(275.0f, 280.0f));
   

    CCMenuItemImage* pQuit = CCMenuItemImage::create("button/quit.png", 
                                                                                                "button/quitSelected.png", 
                                                                                                this, 
                                                                                                menu_selector(MyMenu::__menuCloseCallback));
    pQuit->setPosition(ccp(280.0f, 120.0f));
    
    //background picture
    CCSprite* pBackground = CCSprite::create("MyMenu.png");
    pBackground->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(pBackground, 0);

    CCMenuItemImage *pSetupItem = CCMenuItemImage::create("setupNormal.png", 
                                                                                                        "setupSelected.png", 
                                                                                                        this, 
                                                                                                        menu_selector(HelloWorld::setupCallback));
    pSetupItem->setPosition(ccp(origin.x + visibleSize.width - pSetupItem->getContentSize().width / 2, 
                                                    origin.y + visibleSize.height - pSetupItem->getContentSize().height / 2));

    CCMenu *pMenu = CCMenu::create(pStart, pAbout, pQuit, pSetupItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    ////一个可以点击的精灵，做贝塞尔曲线运动
    //CCMenuItemImage *pMenu = CCMenuItemImage::create("CloseNormal.png",
    //    "CloseSelected.png",
    //    this,
    //    menu_selector(MyMenu::menuCloseCallback));
    //pMenu->setPosition(origin.x+pMenu->getContentSize().width,origin.y+pMenu->getContentSize().height);

    //CCMenu *pm2 = CCMenu::create(pMenu,NULL);
    //pm2->setPosition(CCPointZero);
    //this->addChild(pm2);


    ////贝塞尔曲线移动实例
    //ccBezierConfig bezier;
    //bezier.controlPoint_1 = ccp(0,visibleSize.height/2);
    //bezier.controlPoint_2 = ccp(300,-visibleSize.height/2);
    //bezier.endPosition = ccp(300,100);
    //CCActionInterval * bezierForward = CCBezierBy::create(3,bezier);
    //CCActionInterval * bezierBack = bezierForward->reverse();
    //CCAction *rep = CCRepeatForever::create((CCActionInterval*)CCSequence::create(bezierForward,bezierBack,NULL));
    //pMenu->runAction(rep);

    ////一个jump的精灵
    //CCMenuItemImage *pMenu2 = CCMenuItemImage::create("CloseNormal.png",
    //    "CloseSelected.png",
    //    this,
    //    menu_selector(MyMenu::gameStartCallback));
    //pMenu2->setPosition(origin.x+pMenu2->getContentSize().width,origin.y+pMenu2->getContentSize().height);

    //CCActionInterval* actionTo = CCJumpTo::create(2,ccp(300,300),50,4);
    //CCActionInterval* actionBy = CCJumpBy::create(2,ccp(300,0),50,4);
    //CCActionInterval* actionUp = CCJumpBy::create(2,ccp(0,0),80,4);
    //CCActionInterval* actionByBack = actionBy->reverse();
    //CCAction *jump = CCRepeatForever::create((CCActionInterval*)CCSequence::create(actionBy,actionByBack,NULL));
    //pMenu2->runAction(jump);

    //CCMenu *pm = CCMenu::create(pMenu2,NULL);
    //pm->setPosition(CCPointZero);
    //this->addChild(pm);

    //添加背景音乐
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSIC_FILE1);
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSIC_FILE2);
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(LOADING_MUSIC);
    SimpleAudioEngine::sharedEngine()->preloadEffect("win.wav");

    SimpleAudioEngine::sharedEngine()->preloadEffect("bullet1.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("bullet2.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("hero.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("loseVoice.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("effect1.mp3");
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5f);
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
    //默认开启背景音乐播放
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("startbg.mp3", true);

    return true;
}

CCScene* MyMenu::createScene()
{

    CCScene *scene = CCScene::create();

    MyMenu *layer = MyMenu::create();

    scene->addChild(layer);

    return scene;

}
////////////////回调函数
//退出游戏
void MyMenu::__menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

//跳转到下一个Scene
void MyMenu::__gameStartCallback(CCObject* pSender)
{	
    CCScene *pScene = GameLoadingScene::createScene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f, pScene));
}

void MyMenu::__menuAboutCallback(CCObject* pSender)
{
    CCScene* pScene = HelloWorld::createScene(AboutScene);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f, pScene));
}
