#include "SneakyJoystick.h"
using namespace cocos2d;

#define SJ_PI 3.14159265359f
#define SJ_PI_X_2 6.28318530718f
#define SJ_RAD2DEG 180.0f/SJ_PI
#define SJ_DEG2RAD SJ_PI/180.0f

SneakyJoystick::~SneakyJoystick()
{
}

bool SneakyJoystick::initWithRect(CCRect rect)
{
    bool pRet = false;

    stickPosition = CCPointZero;
    degrees = 0.0f;
    velocity = CCPointZero;
    autoCenter = true;
    isDPad = false;
    hasDeadzone = false;
    numberOfDirections = 4;

    this->setJoystickRadius(rect.size.width/2);
    this->setThumbRadius(32.0f);
    this->setDeadRadius(0.0f);

    //Cocos node stuff
    setPosition(rect.origin);
    pRet = true;

    return pRet;
}

void SneakyJoystick::onEnterTransitionDidFinish()
{
    //	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 1, true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,1,true);
}

void SneakyJoystick::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    //CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
}

float round(float r) 
{
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

void SneakyJoystick::__updateVelocity(CCPoint point)
{
    // Calculate distance and angle from the center.
    float dx = point.x;
    float dy = point.y;
    float dSq = dx * dx + dy * dy;

    if(dSq <= m_deadRadiusSq)
    {
        velocity = CCPointZero;
        degrees = 0.0f;
        stickPosition = point;
        return;
    }

    float angle = atan2f(dy, dx); // in radians
    if(angle < 0)
    {
        angle += SJ_PI_X_2;
    }
    float cosAngle;
    float sinAngle;

    if(isDPad)
    {
        float anglePerSector = 360.0f / numberOfDirections * SJ_DEG2RAD;
        angle = round(angle / anglePerSector) * anglePerSector;
    }

    cosAngle = cosf(angle);
    sinAngle = sinf(angle);

    // NOTE: Velocity goes from -1.0 to 1.0.
    if (dSq > m_joystickRadiusSq || isDPad) 
    {
        dx = cosAngle * joystickRadius;
        dy = sinAngle * joystickRadius;
    }

    velocity = CCPointMake(dx/joystickRadius, dy/joystickRadius);
    degrees = angle * SJ_RAD2DEG;

    // Update the thumb's position
    stickPosition = ccp(dx, dy);
}

void SneakyJoystick::setIsDPad(bool b)
{
    isDPad = b;
    if(isDPad)
    {
        hasDeadzone = true;
        this->setDeadRadius(10.0f);
    }
}

void SneakyJoystick::setJoystickRadius(float r)
{
    joystickRadius = r;
    m_joystickRadiusSq = r*r;
}

void SneakyJoystick::setThumbRadius(float r)
{
    thumbRadius = r;
    m_thumbRadiusSq = r*r;
}

void SneakyJoystick::setDeadRadius(float r)
{
    deadRadius = r;
    m_deadRadiusSq = r*r;
}

bool SneakyJoystick::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
    //CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->locationInView(touch->view()));
    CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    //if([background containsPoint:[background convertToNodeSpace:location]]){
    location = this->convertToNodeSpace(location);
    //Do a fast rect check before doing a circle hit check:
    if(location.x < -joystickRadius || location.x > joystickRadius || location.y < -joystickRadius || location.y > joystickRadius)
    {
        return false;
    }
    else
    {
        float dSq = location.x * location.x + location.y * location.y;
        if(m_joystickRadiusSq > dSq)
        {
            this->__updateVelocity(location);
            return true;
        }
    }
    return false;
}

void SneakyJoystick::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
    //CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->locationInView(touch->view()));
    CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    location = this->convertToNodeSpace(location);
    this->__updateVelocity(location);
}

void SneakyJoystick::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
    CCPoint location = CCPointZero;
    if(!autoCenter)
    {
        //CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->locationInView(touch->view()));
        CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
        location = this->convertToNodeSpace(location);
    }
    this->__updateVelocity(location);
}

void SneakyJoystick::ccTouchCancelled(CCTouch *touch, CCEvent *event)
{
    this->ccTouchEnded(touch, event);
}

void SneakyJoystick::touchDelegateRelease()
{
    this->release();
}

void SneakyJoystick::touchDelegateRetain()
{
    this->retain();
}



