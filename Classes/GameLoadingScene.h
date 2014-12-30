/********************************************************************
Baina@copyright 2014
类名: GameLoadingScene
作用: 游戏loading界面
特性: 游戏场景之一，负责加载进度条，自动跳转到下个Scene
作者: ydli
时间: 2014/11/6
---------------------------------------------------------------------
备注:
*********************************************************************/
#pragma once
#include "cocos2d.h"

class GameLoadingScene :public cocos2d::CCLayer
{
public :
    static cocos2d::CCScene* createScene();

    CREATE_FUNC(GameLoadingScene);

private:
    virtual bool init();
    void __jumptoNextScene();

};