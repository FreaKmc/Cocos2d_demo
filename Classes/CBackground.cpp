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
    //�ӵ���������ά��
    this->scheduleUpdate();
    return true;
}

//��ʱ��������������Ļ���ӵ���������
void CCBackground::update(float dt)
{
    //�����ӵ���������
    m_pNodeChildrenArray = getChildren();
    CCObject* pobj = NULL;
    CCARRAY_FOREACH(m_pNodeChildrenArray, pobj)
    {
        CCNode* pNode = static_cast<CCNode*>(pobj);
        if(pNode->getTag() == 1)
        {
            CCBullet* pBullet = static_cast<CCBullet*>(pNode);
            //��ײ�ж�
            CCRect HeroRect = m_pHero->boundingBox();
            float x = HeroRect.origin.x + HeroRect.size.width * 0.3f;
            float y = HeroRect.origin.y + HeroRect.size.height * 0.4f;
            float width = HeroRect.size.width * 0.3f;
            float height = HeroRect.size.height * 0.6f;

            CCRect rect_HeroForCrash = CCRectMake(x, y, width, height);
            if(pBullet->boundingBox().intersectsRect(rect_HeroForCrash))
            {
                m_pHero->getHurt(pBullet->getHurtAmount());//�е���Ѫ
                pBullet->bulletCrash();
                //�е���Ч
                SimpleAudioEngine::sharedEngine()->playEffect("hero.mp3");
            }
            //�ӵ��е�����
            if(!pBullet->ckeckAlive())
            {
                pBullet->unscheduleAllSelectors();
                m_pNodeChildrenArray->removeObject(pBullet);
            }
        }
    }
}

