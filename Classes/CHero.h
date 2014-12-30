/********************************************************************
Baina@copyright 2014
����: CCHero
����: �����࣬����չ�����Ƕ�����ά������Ѫ��
����: �������ķ����ߵĶ�����Ŀǰֻʵ������
����: ydli
ʱ��: 2014/10/30
---------------------------------------------------------------------
��ע:
*********************************************************************/
#pragma once
#include "cocos2d.h"

class CCHero :public cocos2d::CCSprite
{
public:

    CREATE_FUNC(CCHero);
    virtual bool init();
    static CCHero* create(const char* background);
    //��ʼ������Ͷ���

    cocos2d::CCRepeatForever* initHeroRightAnimation();
    cocos2d::CCRepeatForever* initHeroLeftAnimation();
    cocos2d::CCRepeatForever* initHeroUpAnimaion();
    cocos2d::CCRepeatForever* initHeroDownAnimation();
    cocos2d::CCAnimate* initHeroDeathAnimation();
    cocos2d::CCAnimate* initShowUpAnimation();
    void runLeftAction();
    void runRightAction();
    void stopActionByDirection(int direction);
    //void runUpAction();
    //void runDownAction();
    void getHurt(int hurt);
    int getBlood();

private:
    CCHero(void);
    ~CCHero(void);

private:
    //�ķ����߶�����Ŀǰ�õ����Ҷ���
    cocos2d::CCRepeatForever* m_pMoveAnimate[4];
    cocos2d::CCAnimate* m_pDeadthAnimate;
    int m_blood;//Ѫ��
    int m_Mana;//ħ��ֵ

};

