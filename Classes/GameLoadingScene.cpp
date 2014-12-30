#include "GameLoadingScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#define MainGameScene    1
USING_NS_CC;
using namespace CocosDenshion;
CCScene* GameLoadingScene::createScene()
{
    CCScene *pScene = CCScene::create();
    GameLoadingScene *pLayer = GameLoadingScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool GameLoadingScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    SimpleAudioEngine::sharedEngine()->playEffect("loading.mp3");
    CCSprite* loadingBackgournd = CCSprite::create("loadingbackground.png");
    loadingBackgournd->setPosition(ccp(640.0f, 360.0f));
    this->addChild(loadingBackgournd);

    CCSprite* loadingProgressbar = CCSprite::create("loadingprogressbar.png");
    CCProgressTimer *progress = CCProgressTimer::create(loadingProgressbar);
    progress->setPosition(ccp(640.0f, 360.0f));
    progress->setType(kCCProgressTimerTypeBar);
    //设置为从左到右
    progress->setMidpoint(ccp(0.0f, 0.0f));
    progress->setBarChangeRate(ccp(1.0f, 0.0f));
    progress->setPercentage(100.0f);
    this->addChild(progress);
    CCProgressTo *to = CCProgressTo::create(5.0f, 100.0f);
    CCActionInstant *jumptoGame = CCCallFunc::create(this, callfunc_selector(GameLoadingScene::__jumptoNextScene));
    CCSequence *Sequence = CCSequence::create(to,  jumptoGame, NULL);
    progress->runAction(Sequence);
    return true;
}

void GameLoadingScene::__jumptoNextScene()
{
    CCScene* pScene = HelloWorld::createScene(MainGameScene);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f, pScene));
}