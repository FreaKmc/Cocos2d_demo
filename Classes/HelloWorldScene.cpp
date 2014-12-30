#include "HelloWorldScene.h"
#include "MyMenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "CHero.h"
#include "CTower.h"
#include "NodeManager.h"
#include "CBackground.h"
#include "InputController/SneakyJoystick.h"
#include "InputController/SneakyButtonSkinnedBase.h"
#include "InputController/SneakyButton.h"
#include "InputController/SneakyJoystickSkinnedBase.h"
#pragma execution_character_set("utf-8")

#define MainGameScene    1
#define AboutScene           2
#define ButtonPause           0
#define ButtonResume        1
#define TowerAmount        3

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
CCScene* HelloWorld::createScene(int Type)
{

    CCScene *scene = CCScene::create();

    HelloWorld *layer = HelloWorld::createByTag(Type);

    scene->addChild(layer);

    return scene;
}

HelloWorld* HelloWorld::createByTag(int type)
{
    HelloWorld *pScene = new HelloWorld;
    if(pScene && pScene->initByTag(type))
    {
        pScene->autorelease();
        return pScene;
    }
    else
    {
        delete pScene;
        pScene = NULL;

    }
    return NULL;
}

bool HelloWorld::initByTag(int type)
{
    switch(type)
    {
    case MainGameScene:
        {
            return this->init();
        }
        break;
    case AboutScene:
        {
            return this->__initAboutScene();
        }
        break;
    default:break;
    }
    return false;
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    m_isLeft= false;
    m_isRight = false;
    //创建主角,注意应当在背景初始化和nodemanager初始化前创建主角，因为背景和node需要传入hero指针参数
    m_pSprite = CCHero::create("walk/r1.png");
    m_pSprite->setTag(2);
    m_pSprite->setPosition(ccp(400.0f, 150.0f));
    m_pSprite->setScale(2.0f);
    //建立NodeManager
    pManager = NodeManager::create(m_pSprite);
    this->addChild(pManager);

    // 打开设置菜单的按钮
    CCMenuItemImage *pSetupItem = CCMenuItemImage::create("setupNormal.png", "setupSelected.png", this, menu_selector(HelloWorld::setupCallback));
    pSetupItem->setPosition(ccp(origin.x + visibleSize.width - pSetupItem->getContentSize().width / 2, 
        origin.y + visibleSize.height - pSetupItem->getContentSize().height / 2));
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pSetupItem, NULL);
    pMenu->setPosition(CCPointZero);
    pManager->addChild(pMenu, 1);

    // 添加背景层，并显示
    m_pBackground = CCBackground::create("map.png", m_pSprite);
    m_pBackground->setPosition(ccp(1280.0f, 360.0f));
    pManager->addChild(m_pBackground, 0);
    m_pBackground->addChild(m_pSprite, 1);

    // 添加操纵摇杆，使用开源的SneakyInput
    __createStick();

    //添加tower，可以设置位置 ,可扩展成为不同关卡的模块
    m_pTowerTest[0] = CCTower::create("tower1.png", 1.0f, 1);
    m_pTowerTest[0]->setPosition(ccp(1280.0f, 520.0f));
    m_pBackground->addChild(m_pTowerTest[0], 1);

    m_pTowerTest[1] = CCTower::create("tower2.png", 0.5f, 1);
    m_pTowerTest[1]->setPosition(ccp(1280.0f, 320.0f));
    m_pBackground->addChild(m_pTowerTest[1], 1);

    m_pTowerTest[2] = CCTower::create("tower3.png", 2.0f, 2);
    m_pTowerTest[2]->setPosition(ccp(2000.0f, 420.0f));
    m_pBackground->addChild(m_pTowerTest[2]);

    SimpleAudioEngine::sharedEngine()->playEffect("effect1.mp3");
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gamebgm.mp3");

    //设置定时器
    this->scheduleUpdate();
    //0.1刷新一次位置
    schedule(schedule_selector(HelloWorld::__heroPositionCallback), 0.1f, kCCRepeatForever, 0);
    return true;
}

bool HelloWorld::__initAboutScene()
{
    //about界面的初始化
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSprite* pAbout = CCSprite::create("aboutDemo.png");
    pAbout->setPosition(ccp(640.0f, -720.0f));
    this->addChild(pAbout);

    CCActionInterval* pAction = CCMoveTo::create(20.0f, ccp(640.0f, 1440.0f));
    pAbout->runAction(pAction);

    CCMenuItemImage *pBack = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(HelloWorld::__aboutReturnCallback));
    pBack->setScale(2);
    pBack->setPosition(ccp(visibleSize.width - pBack->getContentSize().width, pBack->getContentSize().height));
    CCMenu *pMenu = CCMenu::create(pBack, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    return true;
}


void HelloWorld::__sceneChangeCallback(CCObject* pSender)
{	

    CCScene *pScene = GameOverScene::createScene(1);

    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f, pScene));

}

void HelloWorld::setupCallback(CCObject* pSender)
{
    popupMenu();
}

void HelloWorld::__buttonCallback(CCNode* pNode)
{
    int tag = pNode->getTag();
    switch(tag)
    {
    case ButtonPause:
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        break; 

    case ButtonResume:
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        break;

    default:break;
    }
    CCDirector::sharedDirector()->resume();//恢复Scene
}

void HelloWorld::__heroPositionCallback(float dt)
{
    for(int i = 0; i < TowerAmount; i++)
        m_pTowerTest[i]->flushPosition(m_pSprite->getPosition());
}

void HelloWorld::__aboutReturnCallback(CCObject* pSender)
{
    CCScene *pScene = MyMenu::createScene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f, pScene));
}

//Scheduleupdate
void HelloWorld::update(float t)
{

    //放大getVelocity()得到的数值
    CCPoint poi = ccpMult(m_pJoystick->getVelocity(), 50);

    //控制在屏幕内移动
    __moveHero(poi);
    __rollMap(poi);

    //在Tower中刷新hero位置

}

void HelloWorld::__rollMap(CCPoint poi)
{
    //横滚地图
    if((poi.x > 0) && (poi.x - poi.y) > 0 && (poi.x + poi.y) > 0 && m_pSprite->getPositionX() > 1250 && m_pBackground->getPositionX() > 0)
    {
        m_pBackground->setPosition(ccp(m_pBackground->getPosition().x - 5, m_pBackground->getPosition().y));
    }
    if((poi.x < 0) && (poi.x - poi.y) < 0 && (poi.x - poi.y) < 0 && m_pSprite->getPositionX() <= 1310 && m_pBackground->getPositionX() < 1280)
    {
        m_pBackground->setPosition(ccp(m_pBackground->getPosition().x + 5, m_pBackground->getPosition().y));
    }
}

void HelloWorld::__moveHero(CCPoint poi)
{
    //操纵杆更新模块
    //right
    if((poi.x > 0) && (poi.x - poi.y) > 0 && (poi.x + poi.y) > 0 && m_pSprite->getPositionX() <= 2530){
        m_pSprite->setPosition(ccp(m_pSprite->getPosition().x + 3, m_pSprite->getPosition().y));
        //call rigth move function
        if(!m_isRight) 
        {
            m_isRight = true;
            if(m_isLeft)
            {
                m_pSprite->stopActionByDirection(0);
            }
            m_pSprite->runRightAction();
            m_isLeft = false;
        }
    }
    //left
    else if((poi.x < 0) && (poi.x - poi.y) < 0 && (poi.x - poi.y) < 0 && m_pSprite->getPositionX() >= 30){
        m_pSprite->setPosition(ccp(m_pSprite->getPosition().x - 3, m_pSprite->getPosition().y));
        if(!m_isLeft)
        {
            m_isLeft= true;
            if(m_isRight)
            {
                m_pSprite->stopActionByDirection(1);
            }
            //call left move function
            m_pSprite->runLeftAction();
            m_isRight = false;
        }

    }
    //up
    else if((poi.y > 0) && (poi.y - poi.x) > 0 && (poi.x + poi.y) > 0 && m_pSprite->getPositionY() <= 690)
    {
        m_pSprite->setPosition(ccp(m_pSprite->getPosition().x, m_pSprite->getPosition().y + 3));
    }
    //down
    if((poi.y < 0) && (poi.y - poi.x) < 0 && (poi.x + poi.y) < 0 && m_pSprite->getPositionY() >= 30)
    {
        m_pSprite->setPosition(ccp(m_pSprite->getPosition().x, m_pSprite->getPosition().y - 3));
    }
}

void HelloWorld::__createStick()
{
    float joystickRadius = 180.0f;
    m_pJoystick = new SneakyJoystick();
    m_pJoystick->autorelease();
    m_pJoystick->initWithRect(CCRectZero);

    //是否自动回到中心
    m_pJoystick->setAutoCenter(true);
    //是否支持deadzone，该区域触发
    m_pJoystick->setHasDeadzone(true);
    //设置死亡半径
    m_pJoystick->setDeadRadius(10.0f);

    SneakyJoystickSkinnedBase *joystickSkin = new SneakyJoystickSkinnedBase();
    joystickSkin->autorelease();
    joystickSkin->init();

    //操纵杆背景
    joystickSkin->setBackgroundSprite(CCSprite::create("directioncontrol1.png"));
    //中心点
    joystickSkin->setThumbSprite(CCSprite::create("directioncontrol2.png"));
    joystickSkin->getThumbSprite()->setScale(1.0f);
    joystickSkin->setPosition(ccp(joystickRadius, joystickRadius));
    joystickSkin->setJoystick(m_pJoystick);
    joystickSkin->setScale(1.5f);

    pManager->addChild(joystickSkin, 3);





}

void HelloWorld::popupMenu()
{   
    CCDirector::sharedDirector()->pause();//暂停当前Scene，在buttonCallback中恢复
    PopupMenu* pl = PopupMenu::create("setupBackground.png");
    pl->setContentSize(CCSizeMake(500.0f, 350.0f));
    pl->setTitle("Setup");
    //pl->setContentText("这只是一个测试",20,60,250);
    pl->setCallBackFunc(this, callfuncN_selector(HelloWorld::__buttonCallback));
    pl->addButton("CloseNormal.png", "CloseSelected.png", "暂停音乐", 0);
    pl->addButton("CloseNormal.png", "CloseSelected.png", "继续音乐", 1);

    this->addChild(pl, 2);
}


///////////////////////////////////弹出菜单类
PopupMenu::PopupMenu():
m_pMenu(NULL)
    , m_contentPadding(0)
    , m_contentPaddingTop(0)
    , m_callbackListener(NULL)
    , m_callback(NULL)
    , m_sfBackGround(NULL)
    , m_s9BackGround(NULL)
    , m_ltContentText(NULL)
    , m_ltTitle(NULL)
{

}

PopupMenu::~PopupMenu()
{
    CC_SAFE_RELEASE(m_pMenu);
    CC_SAFE_RELEASE(m_sfBackGround);
    CC_SAFE_RELEASE(m_ltContentText);
    CC_SAFE_RELEASE(m_ltTitle);
    CC_SAFE_RELEASE(m_s9BackGround);
}

bool PopupMenu::init()
{
    bool bRef = false;
    do{
        CC_BREAK_IF(!CCLayer::init());
        this->setContentSize(CCSizeZero);
        //初始化需要的menu
        CCMenu * menu = CCMenu::create();
        menu->setPosition(CCPointZero);
        setMenuButton(menu);
        setTouchEnabled(true);

        bRef = true;
    }while(0);
    return bRef;
}


void PopupMenu::registerWithTouchDispatcher()
{//将这里的触摸优先级设置为-128，保证屏蔽了下方的触摸
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);

}

bool PopupMenu::ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
{
    CCLog("PopupMenu touch");
    return true;
}

PopupMenu* PopupMenu::create(const char* backgroundImage)
{
    PopupMenu * ml = PopupMenu::create();
    ml->setSpriteBackGround(CCSprite::create(backgroundImage));
    ml->setSprite9BackGround(CCScale9Sprite::create(backgroundImage));
    return ml;
}

void PopupMenu::setTitle(const char* title, int fontsize /* = 20 */)
{
    CCLabelTTF* ltfTitle = CCLabelTTF::create(title, "arial", fontsize);
    setLabelTitle(ltfTitle);

}

void PopupMenu::setContentText(const char* text, int fontsize /* = 20 */, int padding /* = 50 */, int paddingTop /* =100 */)
{
    CCLabelTTF* ltf = CCLabelTTF::create(text, "arial", fontsize);
    setLabelContentText(ltf);
    m_contentPadding = padding;
    m_contentPaddingTop = paddingTop;

}

void PopupMenu::setCallBackFunc(CCObject* pTarget, SEL_CallFuncN callfun)
{
    m_callbackListener = pTarget;
    m_callback = callfun;
}
bool PopupMenu::addButton(const char* normalImage, const char* selectedImage, const char* title, int tag /* = 0 */)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint pCenter = ccp(winSize.width / 2, winSize.height / 2);

    //创建图片按钮
    CCMenuItemImage* menuImage = CCMenuItemImage::create(normalImage, selectedImage, this, menu_selector(PopupMenu::__buttonCallback));
    menuImage->setTag(tag);
    menuImage->setPosition(pCenter);

    //添加文字说明
    CCSize imenu = menuImage->getContentSize();
    CCLabelTTF* ttf = CCLabelTTF::create(title, "", 20);
    ttf->setColor(ccc3(0, 0, 0));
    ttf->setPosition(ccp(imenu.width / 2, imenu.height  / 2));
    menuImage->addChild(ttf);

    getMenuButton()->addChild(menuImage);
    return true;

}

void PopupMenu::__buttonCallback(CCObject* pSender)
{
    CCNode* node = static_cast<CCNode*>(pSender);
    CCLog("Touch tag:%d", node->getTag());
    if(m_callback && m_callbackListener)
    {
        (m_callbackListener->*m_callback)(node);
    }
    this->removeFromParent();
}

void PopupMenu::onEnter()
{
    CCLayer::onEnter();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint pCenter = ccp(winSize.width / 2,winSize.height / 2);

    CCSize contentSize;

    if(getContentSize().equals(CCSizeZero))
    {
        getSpriteBackGround()->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(getSpriteBackGround(), 0 ,0);
        contentSize = getSpriteBackGround()->getTexture()->getContentSize();

    }else
    {
        CCScale9Sprite *background = getSprite9BackGround();
        background->setContentSize(getContentSize());
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(background, 0, 0);
        contentSize = getContentSize();
    }


    //添加按钮，设置位置

    this->addChild(getMenuButton());
    float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);

    CCArray* array = getMenuButton()->getChildren();
    CCObject* pObj = NULL;
    int i = 0;
    CCARRAY_FOREACH(array, pObj)
    {
        CCNode* node = static_cast<CCNode*>(pObj);
        node->setPosition(ccp(winSize.width / 2 - contentSize.width / 2 + btnWidth * (i + 1)
            ,winSize.height / 2 - contentSize.height / 3));
        i++;
    }

    //显示对话框标题
    if (getLabelTitle())
    {
        getLabelTitle()->setPosition(ccpAdd(pCenter, ccp(0, contentSize.height / 2 - 35.0f)));
        this->addChild(getLabelTitle());

    }

    //显示文本内容
    if (getLabelContentText())
    {
        CCLabelTTF* lft = getLabelContentText();
        lft->setPosition(ccp(winSize.width / 2,winSize.height / 2));
        lft->setDimensions(CCSizeMake(contentSize.width - m_contentPadding * 2, contentSize.height - m_contentPaddingTop));
        lft->setHorizontalAlignment(kCCTextAlignmentLeft);
        this->addChild(lft);
    }

    //弹出效果
    CCAction* popupMenu = CCSequence::create(CCScaleTo::create(0.0f,0.0f)
, CCScaleTo::create(0.06f, 1.05f)
, CCScaleTo::create(0.08f, 0.95f)
, CCScaleTo::create(0.08f, 1.0f)
, NULL);

    this->runAction(popupMenu);

}

void PopupMenu::onExit()
{
    CCLog("popip on exit");
    CCLayer::onExit();
}
