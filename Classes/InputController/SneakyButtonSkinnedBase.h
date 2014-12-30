#pragma once

#include "SneakyButton.h"

class SneakyButtonSkinnedBase : public cocos2d::CCLayer 
{
public:
    //Public methods
    CREATE_FUNC(SneakyButtonSkinnedBase);

    virtual ~SneakyButtonSkinnedBase();

    virtual bool init();

    void watchSelf(float delta);

    void setContentSize(cocos2d::CCSize s);

    void setDefaultSprite(cocos2d::CCSprite *aSprite);

    void setActivatedSprite(cocos2d::CCSprite *aSprite);

    void setDisabledSprite(cocos2d::CCSprite *aSprite);

    void setPressSprite(cocos2d::CCSprite *aSprite);

    void setButton(SneakyButton *aButton);

public:
    CC_SYNTHESIZE_READONLY(cocos2d::CCSprite *, defaultSprite, DefaultSprite);

    CC_SYNTHESIZE_READONLY(cocos2d::CCSprite *, activatedSprite, ActivatedSprite);

    CC_SYNTHESIZE_READONLY(cocos2d::CCSprite *, disabledSprite, DisabledSprite);

    CC_SYNTHESIZE_READONLY(cocos2d::CCSprite *, pressSprite, PressSprite);

    CC_SYNTHESIZE_READONLY(SneakyButton *, button, Button); //Not sure about this

};

