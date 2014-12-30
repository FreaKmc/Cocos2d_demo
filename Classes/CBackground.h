/********************************************************************
Baina@copyright 2014
类名: CCBackground
作用: 主场景中的背景节点，负责展现地图，防御塔，子弹以及主角
特性: 父节点为NodeManager，相对坐标原点在NodeManager(0,0)处
作者: ydli
时间: 2014/11/4
---------------------------------------------------------------------
备注:
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