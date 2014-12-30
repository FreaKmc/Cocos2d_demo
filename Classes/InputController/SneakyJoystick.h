#pragma once

#include "cocos2d.h"

class SneakyJoystick : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate 
{
public:
    void setIsDPad(bool b);
    void setJoystickRadius(float r);
    void setThumbRadius(float r);
    void setDeadRadius(float r);

protected:
    CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, stickPosition, StickPosition);
    CC_SYNTHESIZE_READONLY(float, degrees, Degrees);
    CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, velocity, Velocity);
    CC_SYNTHESIZE(bool, autoCenter, AutoCenter);
    CC_SYNTHESIZE_READONLY(bool, isDPad, IsDPad);
    CC_SYNTHESIZE(bool, hasDeadzone, HasDeadzone);
    CC_SYNTHESIZE(int, numberOfDirections, NumberOfDirections);
    CC_SYNTHESIZE_READONLY(float, joystickRadius, JoystickRadius);
    CC_SYNTHESIZE_READONLY(float, thumbRadius, ThumbRadius);
    CC_SYNTHESIZE_READONLY(float, deadRadius, DeadRadius);

    bool initWithRect(cocos2d::CCRect rect);
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    void touchDelegateRelease();
    void touchDelegateRetain();

private:
    void __updateVelocity(cocos2d::CCPoint point);
    void __setTouchRadius();
    virtual ~SneakyJoystick();

private:
    float m_joystickRadiusSq;
    float m_thumbRadiusSq;
    float m_deadRadiusSq;
};

