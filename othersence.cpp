#include "othersence.h"
#include "outside.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "characterAciton.h"
#include "SceneStateManager.h"
#include "GameSceneFacade.h"
USING_NS_CC;

Scene* othersence::createothersenceScene()
{
    auto scene = Scene::create();
    auto layer = othersence::create();
    scene->addChild(layer);
    return scene;
}



bool othersence::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //���ÿ�ʼ����
    auto tiledMap = TMXTiledMap::create("tiledmap/othersence1.tmx");
    this->addChild(tiledMap, 0);
   tiledMap->setScale(3);

    characteraction = CharacterWithTools::create("character/Dana0.png");
    if (characteraction == nullptr) {
        CCLOG("Error: Failed to create character!");
        return false;
    }
    auto button = ui::Button::create("picture/out1.png", "picture/out2.png"); // ��ť������״̬�Ͱ���״̬ͼƬ
    button->setPosition(Vec2(3700,100));
    this->addChild(button);

    characteraction->setPosition(Vec2(3030+500,0));
    this->addChild(characteraction);

    this->scheduleUpdate();
    // ��ÿ֡�и����ӵ�λ�ã�ʹ��ͼʼ�ո�������
    this->schedule([=](float deltaTime) {
        // ��ȡ���ﵱǰ����������
        Vec2 characterPosition = characteraction->getPosition();

        // �����ӵ㣬ȷ����ͼʼ�ո�������
        setViewPointCenter(characterPosition, tiledMap);
        }, "view_point_update_key");

    button->addClickEventListener([=](Ref* sender) {
        // �ص��ɳ���ʱ�ָ�״̬
        //Scene* previousScene = outside::createSceneWithMapIndex(1); // �����ɳ���
        characteraction->setPosition(SceneStateManager::getInstance()->getCharacterPosition());
        tiledMap->setName(SceneStateManager::getInstance()->getMapName());
        /**
         * 使用Facade模式重构后的代码
         * 通过GameSceneFacade统一管理场景返回，而不是直接调用Director
         */
        GameSceneFacade::returnToPreviousScene();
        });

    return true;
}

void othersence::setViewPointCenter(Point position, cocos2d::TMXTiledMap* tiledMap) {
    const auto winSize = Director::getInstance()->getWinSize();
    float scale = tiledMap->getScale(); // ��ȡ��ǰ�����ű���

    // ����ʵ�ʵ���ͼ�������꣨�������ţ�
    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);

    // �������ź�ĵ�ͼ�ߴ�
    float mapWidth = tiledMap->getMapSize().width * tiledMap->getTileSize().width * scale;
    float mapHeight = tiledMap->getMapSize().height * tiledMap->getTileSize().height * scale;

    // ȷ���ӵ㲻�ᳬ����ͼ�ķ�Χ
    x = MIN(x, mapWidth - winSize.width / 2);
    y = MIN(y, mapHeight - winSize.height / 2);

    // �����ӵ�ʵ��λ��
    auto actualPosition = Point(x, y);

    // ��Ļ���ĵ�
    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);

    // �����µ��ӵ�λ��
    auto viewPoint = centerOfView - actualPosition;

    // ������ͼλ��
    this->setPosition(viewPoint);
}
