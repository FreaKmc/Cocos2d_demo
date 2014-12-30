#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#define GAMEWIN  1
#define GAMELOSE 2
#define MainGameScene    1
USING_NS_CC;
using namespace CocosDenshion;
GameOverScene::GameOverScene(void)
{
}

GameOverScene::~GameOverScene(void)
{
}

CCScene* GameOverScene::createScene(int tag)
{
    CCScene* scene  = CCScene::create();
    GameOverScene* layer = GameOverScene::create(tag);
    scene->addChild(layer);
    return scene;
}

GameOverScene* GameOverScene::create(int tag)
{
    GameOverScene* pLayer = new GameOverScene();
    switch (tag)
    {
        case GAMEWIN:
          {
            if (pLayer && pLayer->__initGameWin())
            {
              pLayer->autorelease();
              return pLayer;
            }
          }
            break;

        case GAMELOSE:
          {
              if (pLayer && pLayer->__initGameLose())
              {
                  pLayer->autorelease();
                  return pLayer;
              }
          }
          break;
    default:
        delete pLayer;
        pLayer = NULL;
        return NULL;
        break;
    }
}

bool GameOverScene::__initGameLose()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("losebgm.mp3");
    SimpleAudioEngine::sharedEngine()->playEffect("loseVoice.wav");

    CCSprite *pbackground = CCSprite::create("GameOverLose.png");
    pbackground->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(pbackground, 0);
    //退出按钮
    CCMenuItemImage *pOverButton = CCMenuItemImage::create("button/quit.png",
                                                                                                          "button/quitSelected.png",
                                                                                                          this,
                                                                                                          menu_selector(GameOverScene::__menuCloseCallback));
    CCMenuItemImage *pRestartButton = CCMenuItemImage::create("button/restart.png",
                                                                                                             "button/restartSelected.png",
                                                                                                             this,
                                                                                                             menu_selector(GameOverScene::__menuRestartCallback));
    CCMenuItemImage *pSetupItem = CCMenuItemImage::create("setupNormal.png",
                                                                                                        "setupSelected.png",
                                                                                                        this,
                                                                                                        menu_selector(HelloWorld::setupCallback));
    pSetupItem->setPosition(ccp(origin.x + visibleSize.width - pSetupItem->getContentSize().width / 2,
                                                    origin.y + visibleSize.height - pSetupItem->getContentSize().height / 2));
    pOverButton->setPosition(ccp(660.0f, 60.0f));
    pRestartButton->setPosition(ccp(660.0f, 235.0f));
    CCMenu *pClose = CCMenu::create(pRestartButton, pOverButton, pSetupItem, NULL);
    pClose->setPosition(CCPointZero);
    this->addChild(pClose, 1);
    return true;
}

bool GameOverScene::__initGameWin()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
   
    SimpleAudioEngine::sharedEngine()->playEffect("win.wav");
    //SimpleAudioEngine::sharedEngine()->playBackgroundMusic();
    //背景
    CCSprite *pbackground = CCSprite::create("GameOverWin.png");
    pbackground->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(pbackground, 0);
    //退出按钮
    CCMenuItemImage *pOverButton = CCMenuItemImage::create("button/quit.png",
                                                                                                         "button/quitSelected.png",
                                                                                                         this,
                                                                                                         menu_selector(GameOverScene::__menuCloseCallback));
    CCMenuItemImage *pRestartButton = CCMenuItemImage::create("button/restart.png",
                                                                                                            "button/restartSelected.png",
                                                                                                            this,
                                                                                                            menu_selector(GameOverScene::__menuRestartCallback));
    CCMenuItemImage *pSetupItem = CCMenuItemImage::create("setupNormal.png",
                                                                                                        "setupSelected.png",
                                                                                                        this,
                                                                                                        menu_selector(HelloWorld::setupCallback));
    pSetupItem->setPosition(ccp(origin.x + visibleSize.width - pSetupItem->getContentSize().width / 2,
                                                    origin.y + visibleSize.height - pSetupItem->getContentSize().height / 2));
    pOverButton->setPosition(ccp(660.0f, 60.0f));
    pRestartButton->setPosition(ccp(660.0f, 235.0f));
    CCMenu *pClose = CCMenu::create(pRestartButton, pOverButton, pSetupItem, NULL);
    pClose->setPosition(CCPointZero);
    this->addChild(pClose, 1);
    return true;
}

//游戏结束回调函数
void GameOverScene::__menuCloseCallback(CCObject* pSender)
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

void GameOverScene::__menuRestartCallback(CCObject* pSender)
{
    CCScene *pScene = HelloWorld::createScene(MainGameScene);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f, pScene));
}
