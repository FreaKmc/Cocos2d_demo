#include "CHero.h"
#define DIRECTION_LEFT    0
#define DIRECTION_RIGHT 1
USING_NS_CC;
const int moveFrame = 28;
CCHero::CCHero(void)
{
}

CCHero::~CCHero(void)
{
    m_pMoveAnimate[0]->release();
    m_pMoveAnimate[1]->release();
}

CCHero* CCHero::create(const char* background)
{
    CCHero *pobSprite = new CCHero();

    if (pobSprite && pobSprite->initWithFile(background))
    {
        pobSprite->init();
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

bool CCHero::init()
{
    m_pMoveAnimate[DIRECTION_LEFT] = initHeroLeftAnimation();
    m_pMoveAnimate[DIRECTION_RIGHT] = initHeroRightAnimation();
    m_pMoveAnimate[DIRECTION_LEFT]->retain();
    m_pMoveAnimate[DIRECTION_RIGHT]->retain();
    this->m_blood = 200;//ÑªÁ¿Îª200
    return true;

}

CCRepeatForever* CCHero::initHeroRightAnimation()
{
    CCAnimation *animation = CCAnimation::create();
    for(int i = 1; i < moveFrame; i++)
    {
        char szName[100]={0};
        sprintf(szName, "walk/r%d.png", i);
        animation->addSpriteFrameWithFileName(szName);
        //CCLog("%d",i);
    }

    animation->setDelayPerUnit(1.0f / 18.0f);
    animation->setRestoreOriginalFrame(true);
    CCAnimate *walk = CCAnimate::create(animation);
    CCRepeatForever *pRightwalk = CCRepeatForever::create(walk);
    pRightwalk->setTag(1);//right tag1
    return pRightwalk;
}

CCRepeatForever* CCHero::initHeroLeftAnimation()
{
    CCAnimation *animation = CCAnimation::create();
    for(int i = 1; i < moveFrame; i++)
    {
        char szName[100]={0};
        sprintf(szName, "walk/l%d.png", i);
        animation->addSpriteFrameWithFileName(szName);
        //CCLog("%d",i);
    }
    animation->setDelayPerUnit(1.0f / 18.0f);
    animation->setRestoreOriginalFrame(true);
    CCAnimate *walk = CCAnimate::create(animation);
    CCRepeatForever *pLeftWalk = CCRepeatForever::create(walk);
    pLeftWalk->setTag(2);//left tag 2
    return pLeftWalk;
}

CCRepeatForever* CCHero::initHeroUpAnimaion()
{
    return NULL;
}

CCRepeatForever* CCHero::initHeroDownAnimation()
{
    return NULL;
}

CCAnimate* CCHero::initHeroDeathAnimation()
{
    return NULL;
}

CCAnimate* CCHero::initShowUpAnimation()
{
    return NULL;
}

void CCHero::runLeftAction()
{
    this->runAction(m_pMoveAnimate[0]);
}

void CCHero::runRightAction()
{
    this->runAction(m_pMoveAnimate[1]);
}

//void runUpAction();

//void runDownAction();

void CCHero::stopActionByDirection(int direction)
{
    this->stopAction(m_pMoveAnimate[direction]);
}

void CCHero::getHurt(int hurt)
{
   m_blood -= hurt;
}

int CCHero::getBlood()
{
    return m_blood;
}