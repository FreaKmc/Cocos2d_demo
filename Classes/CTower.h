/********************************************************************
Baina@copyright 2014
类名: CCTower
作用: 攻击主角的防御塔
特性: 定时更新主角位置，实例攻击子弹并追及攻击英雄
作者: ydli
时间: 2014/10/31
---------------------------------------------------------------------
备注:
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "math.h"

class CCBullet;
class CCTower : public cocos2d::CCSprite
{
public:

    //Rate为初始攻击间隔,TowerType为塔类型，子弹弹道不同
    static CCTower* create(const char* image, float Rate, int TowerType);

    //在外部刷新函数中调用，获取当前主角位置
    void flushPosition(cocos2d::CCPoint poi);

private:
    CCTower();

    virtual ~CCTower();

    bool init(float rate, int TowerType);

    //定时更新函数，内部完成创建新子弹，并维护m_PBullets数组，检查每个子弹的isAlive情况，若已经死亡，则remove掉
    void __updateAttack(float dt);

    //在updateAttack函数中调用，创建新子弹
    CCBullet* __shootBullet(const cocos2d::CCPoint heroPosion);

    //发射子弹
    void __moveBullet(int TowerType, CCBullet*);

private:
    float m_AttactRate;
    int m_TowerType;
    cocos2d::CCPoint m_targetPosition;

};

