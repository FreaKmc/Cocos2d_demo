/********************************************************************
Baina@copyright 2014
类名: MyMenu
作用: 开始场景，提供选择菜单
特性: 跳转到主画面场景时传出参数，根据参数主场景选择展现画面
作者: ydli
时间: 2014/10/23
备注: 
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

