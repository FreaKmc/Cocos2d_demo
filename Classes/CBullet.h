/********************************************************************
Baina@copyright 2014
����: CCBullet
����: ׷�湥������
����: ��Tower����ʵ����Background�������
����: ydli
ʱ��: 2014/10/31
---------------------------------------------------------------------
��ע:
*********************************************************************/
#pragma once
#include "cocos2d.h"

class CCBullet : public cocos2d::CCSprite
{
public:
    //�Զ���create����������ΪͼƬ���˺�ֵ
    static CCBullet* create(const char* image ,int hurt);
    //����ӵ��Ƿ�����л��߳��綼�ᵼ���ӵ�����
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

