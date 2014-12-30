#include "NodeManager.h"
#include "GameOverScene.h"
#include "CHero.h"
#include "SimpleAudioEngine.h"
#define GAMEWIN  1
#define GAMELOSE 2
USING_NS_CC;
using namespace CocosDenshion;
 
NodeManager::NodeManager():
m_pHero(NULL),
m_pTimer(NULL),
m_time(0),
m_blood(0)
{

}

NodeManager::~NodeManager()
{

}

NodeManager* NodeManager::create(CCHero* hero)
{
    NodeManager * pNode = new NodeManager();
    if(pNode && pNode->init(hero))
    {   
        pNode->autorelease();
        return pNode;
    }
    else
    {
        CC_SAFE_DELETE(pNode);
    }

    return NULL;
}

bool NodeManager::init(CCHero* hero)
{
    this->m_pHero = hero;
    //主角头像
    CCSprite *avatar = CCSprite::create("avatar.png");
    avatar->setPosition(ccp(90.0f, 630.0f));
    this->addChild(avatar, 3);
    //血量显示
    m_pBlood = CCLabelTTF::create("Remain Blood: 200", "Starcraft Normal", 25);
    m_pBlood->setPosition(ccp(150.0f, 520.0f));
    this->addChild(m_pBlood, 3);
    //技能按钮

    //游戏时间
    m_time = 50.0f;
    m_pTimer = CCLabelTTF::create("Remain Time: 100.0S", "Starcraft Normal", 50);
    m_pTimer->setPosition(ccp(640.0f, 680.0f));
    m_pTimer->setOpacity(50);
    this->addChild(m_pTimer, 4);
    this->schedule(schedule_selector(NodeManager::__TimeUpdate), 0.1f, kCCRepeatForever, 0);
    return true;
}

void NodeManager::__TimeUpdate(float dt)
{   
    this->removeChild(m_pTimer);
    m_time -= 0.1f;
    char title[100]= {0};
    sprintf(title,"Remain Time: %.1f S", m_time);
    m_pTimer = CCLabelTTF::create(title, "Starcraft Normal", 50);
    m_pTimer->setPosition(ccp(640.0f, 680.0f));
    m_pTimer->setOpacity(80);
    this->addChild(m_pTimer, 4);
    
    this->removeChild(m_pBlood);
    m_blood = m_pHero->getBlood();
    char blood[100] = {0};
    sprintf(blood, "Remain Blood: %d", m_blood);
    m_pBlood = CCLabelTTF::create(blood, "Starcraft Normal", 25);
    m_pBlood->setPosition(ccp(150.0f, 520.0f));
    this->addChild(m_pBlood, 3);
    
    //检查游戏结果
    if(m_time <= 0){
        __changeToWinScene();
    }
    if(m_pHero->getBlood() < 0)
    {
        __changeToLoseScene();
    }
}

void NodeManager::__changeToWinScene()
{
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCScene *pScene = GameOverScene::createScene(GAMEWIN);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipAngular::create(2.0f, pScene));

}

void NodeManager::__changeToLoseScene()
{
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCScene *pScene = GameOverScene::createScene(GAMELOSE);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipAngular::create(2.0f, pScene));
}
