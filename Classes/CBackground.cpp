#include "CBackground.h"
#include "CHero.h"
#include "CBullet.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
CCBackground::CCBackground():
m_pHero(NULL),
m_pNodeChildrenArray(NULL)
{

}

CCBackground::~CCBackground()
{

}

CCBackground* CCBackground::create(const char* image, CCHero* pHero)
{
    CCBackground* pSprite = new CCBackground;
    if(pSprite && pSprite->initWithFile(image)) 
    {
        pSprite->init(pHero);
        pSprite->autorelease();
        return pSprite;
    }
    else
    {
        CC_SAFE_DELETE(pSprite);
        return NULL;
   }
}

bool CCBackground::init(CCHero* pHero)
{
    this->m_pHero = pHero;
    //子弹生命周期维护
    this->scheduleUpdate();
    return true;
}

//计时器，管理整个屏幕的子弹生命周期
void CCBackground::update(float dt)
{
    //管理子弹生命周期
    m_pNodeChildrenArray = getChildren();
    CCObject* pobj = NULL;
    CCARRAY_FOREACH(m_pNodeChildrenArray, pobj)
    {
        CCNode* pNode = static_cast<CCNode*>(pobj);
        if(pNode->getTag() == 1)
        {
            CCBullet* pBullet = static_cast<CCBullet*>(pNode);
            //碰撞判定
            CCRect HeroRect = m_pHero->boundingBox();
            float x = HeroRect.origin.x + HeroRect.size.width * 0.3f;
            float y = HeroRect.origin.y + HeroRect.size.height * 0.4f;
            float width = HeroRect.size.width * 0.3f;
            float height = HeroRect.size.height * 0.6f;

            CCRect rect_HeroForCrash = CCRectMake(x, y, width, height);
            if(pBullet->boundingBox().intersectsRect(rect_HeroForCrash))
            {
                m_pHero->getHurt(pBullet->getHurtAmount());//中弹减血
                pBullet->bulletCrash();
                //中弹音效
                SimpleAudioEngine::sharedEngine()->playEffect("hero.mp3");
            }
            //子弹中弹回收
            if(!pBullet->ckeckAlive())
            {
                pBullet->unscheduleAllSelectors();
                m_pNodeChildrenArray->removeObject(pBullet);
            }
        }
    }
}

