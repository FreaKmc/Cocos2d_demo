/********************************************************************
Baina@copyright 2014
����: GameLoadingScene
����: ��Ϸloading����
����: ��Ϸ����֮һ��������ؽ��������Զ���ת���¸�Scene
����: ydli
ʱ��: 2014/11/6
---------------------------------------------------------------------
��ע:
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