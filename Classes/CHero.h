/********************************************************************
Baina@copyright 2014
类名: CCHero
作用: 主角类，负责展现主角动画，维护主角血量
特性: 有主角四方行走的动画，目前只实现两方
作者: ydli
时间: 2014/10/30
---------------------------------------------------------------------
备注:
*********************************************************************/
#pragma once
#include "cocos2d.h"

class CCHero :public cocos2d::CCSprite
{
public:

    CREATE_FUNC(CCHero);
    virtual bool init();
    static CCHero* create(const char* background);
    //初始化纹理和动作

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
    //四方行走动作，目前用到左右二方
    cocos2d::CCRepeatForever* m_pMoveAnimate[4];
    cocos2d::CCAnimate* m_pDeadthAnimate;
    int m_blood;//血量
    int m_Mana;//魔法值

};

