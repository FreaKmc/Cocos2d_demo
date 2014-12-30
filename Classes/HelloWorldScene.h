/********************************************************************
Baina@copyright 2014
类名: HelloWorld, PopupMenu
作用: 主画面场景，负责展现主要的游戏场景；全局的弹出菜单
特性: 主画面场景根据传入参数确定所展现Layer；弹出菜单已作为组件封装
作者: ydli
时间: 2014/10/23
---------------------------------------------------------------------
备注: HelloWorld中popupMenu回调函数可以作为单例方式全局调用
*********************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

class SneakyJoystick;
class CCHero;
class CCBackground;
class CCTower;
class NodeManager;

class HelloWorld : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* createScene(int Type);

    static HelloWorld* createByTag(int type);

    // a selector callback
    void setupCallback(cocos2d::CCObject* pSender);

    //弹出菜单
    void popupMenu();
    //手动实现static node()
    CREATE_FUNC(HelloWorld);



private:
    //Layer初始化选择器，根据传来的Tag来确定初始化哪个Layer
    bool initByTag(int);
    //正式游戏场景
    virtual bool init();

    virtual void update(float t);
    
    //about界面
    bool __initAboutScene();

    void __sceneChangeCallback(cocos2d::CCObject* pSender);

    void __buttonCallback(cocos2d::CCNode* pNode);

    void __heroPositionCallback(float dt);

    void __aboutReturnCallback(cocos2d::CCObject* pSender);

    void __rollMap(cocos2d::CCPoint);

    void __moveHero(cocos2d::CCPoint);

    void __createStick(void);

private:
    SneakyJoystick* m_pJoystick;
    CCHero* m_pSprite;//主角
    CCBackground* m_pBackground;//背景
    CCTower* m_pTowerTest[2]; //防御塔
    NodeManager* pManager;//全局控制manager
    //current hero walk direction 可以考虑封装到hero类中
    bool m_isLeft;
    bool m_isRight;
};

class PopupMenu : public cocos2d::CCLayer
{
public:
    //回调函数，当点击按钮后，关闭弹出层同事，回调一个函数，通知点击了哪个按钮
    void setCallBackFunc(cocos2d::CCObject* pTarget, cocos2d::SEL_CallFuncN callfun);

    //重写触摸函数，永远返回true，屏蔽其他应用层，达到模态效果
    bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);

    //创建并显示对话框背景图片
    static PopupMenu* create(const char* backgroundImage);

    //显示标题，设置显示文字大小
    void setTitle(const char* title, int fontsize = 20);

    //文本内容，padding为到对话框两边的预留距离，可控
    void setContentText(const char* text, int fontsize = 20, int padding = 50, int paddingTop =100);

    bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);

    CREATE_FUNC(PopupMenu);
private:
    void __buttonCallback(cocos2d::CCObject* pSender);

    virtual bool init();
    //需要重写的触摸注册函数，重新给定触摸级别
    virtual void registerWithTouchDispatcher(void);

    virtual void onEnter();

    virtual void onExit();

    PopupMenu();

    virtual ~PopupMenu();

private:
    int m_contentPadding;
    int m_contentPaddingTop;
    cocos2d::CCObject* m_callbackListener;
    cocos2d::SEL_CallFuncN m_callback;

    CC_SYNTHESIZE_RETAIN(cocos2d::CCMenu*, m_pMenu, MenuButton);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite*, m_sfBackGround, SpriteBackGround);
    CC_SYNTHESIZE_RETAIN(cocos2d::extension::CCScale9Sprite*, m_s9BackGround, Sprite9BackGround);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCLabelTTF*, m_ltTitle, LabelTitle);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCLabelTTF*, m_ltContentText, LabelContentText );
};

