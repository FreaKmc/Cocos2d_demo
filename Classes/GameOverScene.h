/********************************************************************
Baina@copyright 2014
类名: GameOverScene
作用: 游戏结束场景
特性: 根据传入的参数决定所展现的layer
作者: ydli
时间: 2014/10/23
---------------------------------------------------------------------
备注:
*********************************************************************/
#pragma once
#include "cocos2d.h"


class GameOverScene: public cocos2d::CCLayer
{
public:
    CREATE_FUNC(GameOverScene);

    static cocos2d::CCScene* createScene(int tag);

    static GameOverScene* create(int tag);

private:
    GameOverScene(void);

    virtual ~GameOverScene(void);

    bool __initGameWin();

    bool __initGameLose();

    void __menuCloseCallback(cocos2d::CCObject *pSender);

    void __menuRestartCallback(cocos2d::CCObject *pSender);

};

