/********************************************************************
Baina@copyright 2014
类名: NodeManager
作用: 管理主场景中的所有节点，包括头像，血条，时间点，背景
特性: 
作者: ydli
时间: 2014/11/3
---------------------------------------------------------------------        
备注: 
*********************************************************************/
#pragma once
#include "cocos2d.h"

class CCHero;
class NodeManager : public cocos2d::CCNode
{
public:
    NodeManager();

    virtual ~NodeManager();

    static NodeManager* create(CCHero*);



private:
    void __changeToWinScene();

    void __changeToLoseScene();

    virtual bool init(CCHero*);

    void __TimeUpdate(float dt);

private:
    CCHero* m_pHero;

    cocos2d::CCLabelTTF *m_pTimer;

    cocos2d::CCLabelTTF *m_pBlood;

    float m_time;

    int m_blood;


};
