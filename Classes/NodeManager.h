/********************************************************************
Baina@copyright 2014
����: NodeManager
����: �����������е����нڵ㣬����ͷ��Ѫ����ʱ��㣬����
����: 
����: ydli
ʱ��: 2014/11/3
---------------------------------------------------------------------        
��ע: 
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
