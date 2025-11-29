#include "intovalley.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "SceneStateManager.h"
#include "characterAciton.h"
#include "GameSceneFacade.h"

USING_NS_CC;

Scene* intovalley::createintovalleyScene()
{
    auto scene = Scene::create();
    auto layer = intovalley::create();
    scene->addChild(layer);
    return scene;
}



bool intovalley::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //���ÿ�ʼ����
    auto spriteback = Sprite::create("picture/home.png");
    spriteback->setAnchorPoint(Vec2::ZERO);
    spriteback->setPosition(Vec2(700, 200));
    this->addChild(spriteback);


    characteraction = CharacterWithTools::create("character/Dana0.png");
    if (characteraction == nullptr) {
        CCLOG("Error: Failed to create character!");
        return false;
    }
    auto button = ui::Button::create("picture/out1.png", "picture/out2.png"); // ��ť������״̬�Ͱ���״̬ͼƬ
    button->setPosition(Vec2(975, 230));
    this->addChild(button);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    characteraction->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(characteraction);

    this->scheduleUpdate();
    // ��ÿ֡�и����ӵ�λ�ã�ʹ��ͼʼ�ո�������
    this->schedule([=](float deltaTime) {
        // ��ȡ���ﵱǰ����������
        Vec2 characterPosition = characteraction->getPosition();

        button->addClickEventListener([&](Ref* sender) {
            // �ص��ɳ���ʱ�ָ�״̬
            
            /**
             * 使用Facade模式重构后的代码
             * 通过GameSceneFacade统一管理场景返回，而不是直接调用Director和outside
             */
            GameSceneFacade::returnToPreviousScene();
            });

        }, "view_point_update_key");

    return true;
}


