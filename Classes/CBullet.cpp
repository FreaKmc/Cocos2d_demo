#include "CBullet.h"
USING_NS_CC;


CCBullet::CCBullet():
m_isAlive(true),
m_hurt(0)
{
}

CCBullet::~CCBullet(void)
{
}

CCBullet *CCBullet::create(const char* image, int hurt)
{
    CCBullet *pSprite = new CCBullet();
    if (pSprite && pSprite->initWithFile(image))
    {
        pSprite->init(hurt);
        pSprite->autorelease();
        return pSprite;
    }
    else
    {
        CC_SAFE_DELETE(pSprite);
    }

    return NULL;
}

bool CCBullet::init(int hurt)
{
    m_hurt = hurt;
    //CCLog("bullet created");
    schedule(schedule_selector(CCBullet::__bulletUpdate), 0.5f, kCCRepeatForever, 0);
    return true;
}

void CCBullet::__bulletUpdate(float dt)
{
     //CCLog("parent bullet position:%f %f ",getPosition().x,getPosition().y);
    //根据子弹位置来改变isAlive的值
    if(this->getPosition().y <= 0 || this->getPosition().y >= 720 || this->getPositionX() <= 0 || this->getPositionX()>= 2560 )
        this->m_isAlive = false;

}

bool CCBullet::ckeckAlive()
{
    return m_isAlive;
}

void CCBullet::bulletCrash()
{
    this->m_isAlive = false;
}

int CCBullet::getHurtAmount()
{
    return this->m_hurt;
}