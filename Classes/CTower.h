/********************************************************************
Baina@copyright 2014
����: CCTower
����: �������ǵķ�����
����: ��ʱ��������λ�ã�ʵ�������ӵ���׷������Ӣ��
����: ydli
ʱ��: 2014/10/31
---------------------------------------------------------------------
��ע:
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "math.h"

class CCBullet;
class CCTower : public cocos2d::CCSprite
{
public:

    //RateΪ��ʼ�������,TowerTypeΪ�����ͣ��ӵ�������ͬ
    static CCTower* create(const char* image, float Rate, int TowerType);

    //���ⲿˢ�º����е��ã���ȡ��ǰ����λ��
    void flushPosition(cocos2d::CCPoint poi);

private:
    CCTower();

    virtual ~CCTower();

    bool init(float rate, int TowerType);

    //��ʱ���º������ڲ���ɴ������ӵ�����ά��m_PBullets���飬���ÿ���ӵ���isAlive��������Ѿ���������remove��
    void __updateAttack(float dt);

    //��updateAttack�����е��ã��������ӵ�
    CCBullet* __shootBullet(const cocos2d::CCPoint heroPosion);

    //�����ӵ�
    void __moveBullet(int TowerType, CCBullet*);

private:
    float m_AttactRate;
    int m_TowerType;
    cocos2d::CCPoint m_targetPosition;

};

