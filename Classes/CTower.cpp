#include "CTower.h"
#include "CBullet.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace  CocosDenshion;
static const float R = 2000.0f;
static const int StraightBullet = 1;
static const int JumpBullet     = 2;


CCTower::CCTower():m_targetPosition(0,0)
{

}


CCTower::~CCTower(void)
{

}

CCTower* CCTower::create(const char* image, float Rate, int TowerType)
{
    CCTower *pSprite = new CCTower();

    if (pSprite && pSprite->initWithFile(image))
    {
        pSprite->init(Rate,TowerType);
        pSprite->autorelease();
        return pSprite;
    }
    else
    {
        CC_SAFE_DELETE(pSprite);
    }

    return NULL;
}

bool CCTower::init(float Rate, int TowerType)
{
    this->m_AttactRate = Rate;
    this->m_TowerType = TowerType;
    schedule(schedule_selector(CCTower::__updateAttack), m_AttactRate, kCCRepeatForever, 0);
    return true;
}

void CCTower::__updateAttack(float dt)
{
    CCBullet *pBullet = __shootBullet(m_targetPosition);
}

void CCTower::flushPosition(CCPoint poi)
{
    m_targetPosition = poi;
}

CCBullet* CCTower::__shootBullet(CCPoint target)
{
    CCBullet* pNewBullet = CCBullet::create("bullet.png", 20);
    pNewBullet->setPosition(this->getPosition());
    pNewBullet->setTag(1);
    this->getParent()->addChild(pNewBullet);//上溯到background节点
    __moveBullet(m_TowerType, pNewBullet);
    return pNewBullet;
}

void CCTower::__moveBullet(int TowerType, CCBullet*pNewBullet)
{

    switch(TowerType)
    {
    case StraightBullet:
        {
        //直线飞弹
            SimpleAudioEngine::sharedEngine()->playEffect("bullet1.mp3");
       //新算法方便多了~~
            float theta = ccpToAngle(ccp(m_targetPosition.x - this->getPositionX(), m_targetPosition.y - this->getPositionY()));
            CCActionInterval *pAction = CCMoveTo::create(10, ccp(cos(theta) * R + this->getPositionX(), sin(theta) * R + this->getPositionY()));
            pNewBullet->runAction(pAction);
        }
        break;
    case JumpBullet:
        {
        //jump的子弹
            SimpleAudioEngine::sharedEngine()->playEffect("bullet2.mp3");
            float theta = ccpToAngle(ccp(m_targetPosition.x - this->getPositionX(), m_targetPosition.y - this->getPositionY()));
            CCActionInterval *pAction = CCJumpTo::create(10.0f, ccp(cos(theta) * R + this->getPositionX(), sin(theta) * R + this->getPositionY()), 40.0f, 40);
            pNewBullet->runAction(pAction);
        }
        break;
    default:break;
    }
}