/********************************************************************
Baina@copyright 2014
����: GameOverScene
����: ��Ϸ��������
����: ���ݴ���Ĳ���������չ�ֵ�layer
����: ydli
ʱ��: 2014/10/23
---------------------------------------------------------------------
��ע:
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

