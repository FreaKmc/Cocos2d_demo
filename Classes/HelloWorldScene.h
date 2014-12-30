/********************************************************************
Baina@copyright 2014
����: HelloWorld, PopupMenu
����: �����泡��������չ����Ҫ����Ϸ������ȫ�ֵĵ����˵�
����: �����泡�����ݴ������ȷ����չ��Layer�������˵�����Ϊ�����װ
����: ydli
ʱ��: 2014/10/23
---------------------------------------------------------------------
��ע: HelloWorld��popupMenu�ص�����������Ϊ������ʽȫ�ֵ���
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

    //�����˵�
    void popupMenu();
    //�ֶ�ʵ��static node()
    CREATE_FUNC(HelloWorld);



private:
    //Layer��ʼ��ѡ���������ݴ�����Tag��ȷ����ʼ���ĸ�Layer
    bool initByTag(int);
    //��ʽ��Ϸ����
    virtual bool init();

    virtual void update(float t);
    
    //about����
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
    CCHero* m_pSprite;//����
    CCBackground* m_pBackground;//����
    CCTower* m_pTowerTest[2]; //������
    NodeManager* pManager;//ȫ�ֿ���manager
    //current hero walk direction ���Կ��Ƿ�װ��hero����
    bool m_isLeft;
    bool m_isRight;
};

class PopupMenu : public cocos2d::CCLayer
{
public:
    //�ص��������������ť�󣬹رյ�����ͬ�£��ص�һ��������֪ͨ������ĸ���ť
    void setCallBackFunc(cocos2d::CCObject* pTarget, cocos2d::SEL_CallFuncN callfun);

    //��д������������Զ����true����������Ӧ�ò㣬�ﵽģ̬Ч��
    bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);

    //��������ʾ�Ի��򱳾�ͼƬ
    static PopupMenu* create(const char* backgroundImage);

    //��ʾ���⣬������ʾ���ִ�С
    void setTitle(const char* title, int fontsize = 20);

    //�ı����ݣ�paddingΪ���Ի������ߵ�Ԥ�����룬�ɿ�
    void setContentText(const char* text, int fontsize = 20, int padding = 50, int paddingTop =100);

    bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);

    CREATE_FUNC(PopupMenu);
private:
    void __buttonCallback(cocos2d::CCObject* pSender);

    virtual bool init();
    //��Ҫ��д�Ĵ���ע�ắ�������¸�����������
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

