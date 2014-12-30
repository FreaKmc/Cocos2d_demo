/********************************************************************
Baina@copyright 2014
类名: CCBullet
作用: 追随攻击主角
特性: 由Tower负责实例，Background负责管理
作者: ydli
时间: 2014/10/31
---------------------------------------------------------------------
备注:
*********************************************************************/
#pragma once
#include "cocos2d.h"

class CCBullet : public cocos2d::CCSprite
{
public:
    //自定义create函数，参数为图片和伤害值
    static CCBullet* create(const char* image ,int hurt);
    //检查子弹是否存活，击中或者出界都会导致子弹死亡
    bool ckeckAlive();
    int getHurtAmount(void);
    void bulletCrash(void);

private:
    void __bulletUpdate(float);
    virtual bool init(int hurt);
    CCBullet(void);
    virtual ~CCBullet(void);

private:
    bool m_isAlive;
    int m_hurt;
};

