/********************************************************************
Baina@copyright 2014
����: MyMenu
����: ��ʼ�������ṩѡ��˵�
����: ��ת�������泡��ʱ�������������ݲ���������ѡ��չ�ֻ���
����: ydli
ʱ��: 2014/10/23
��ע: 
*********************************************************************/
#pragma once
#include "cocos2d.h"
class MyMenu :public cocos2d::CCLayer
{
public:

    static cocos2d::CCScene* createScene();

    CREATE_FUNC(MyMenu);

private:
    virtual bool init();

    void __menuCloseCallback(cocos2d::CCObject* pSender);

    void __gameStartCallback(cocos2d::CCObject* pSender);

    void __menuAboutCallback(cocos2d::CCObject* pSender);
    //void SetupCallback();
    //void popupMenu();
};

