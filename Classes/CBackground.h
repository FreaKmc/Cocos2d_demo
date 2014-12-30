/********************************************************************
Baina@copyright 2014
����: CCBackground
����: �������еı����ڵ㣬����չ�ֵ�ͼ�����������ӵ��Լ�����
����: ���ڵ�ΪNodeManager���������ԭ����NodeManager(0,0)��
����: ydli
ʱ��: 2014/11/4
---------------------------------------------------------------------
��ע:
*********************************************************************/
#pragma once
#include "cocos2d.h"
class CCHero;

class CCBackground :public cocos2d::CCSprite
{
public:
    static CCBackground* create(const char* image, CCHero*);
    void isHeroAlive(float dt);

private:
    CCBackground();
    virtual ~CCBackground();
    virtual void update(float);
    virtual bool init(CCHero* pHero);

private:
    CCHero* m_pHero;
    cocos2d::CCArray* m_pNodeChildrenArray;
};