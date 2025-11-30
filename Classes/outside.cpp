/****************************************************************************
 *
 * 使用观察者模式和外观模式重构后的代码
 *
 ****************************************************************************/
#include "outside.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "intovalley.h"
#include "SimpleAudioEngine.h"
#include "menu.h"
#include "GameTimeSystem.h"
#include "characterAction.h"
#include "Plantingcrops.h"
#include "othersence.h"
#include "SceneStateManager.h"
#include "Animal.h"
#include "GameSceneFacade.h"
 // ==================== 使用观察者模式重构新增====================
#include "EventCenter.h"   
#include "EventType.h"     
#include "EventData.h"    
#include "TimePublisher.h"

using namespace CocosDenshion;

USING_NS_CC;



Scene* outside::createSceneWithMapIndex(int mapIndex) {
    auto scene = Scene::create();
    auto layer = outside::create();

    layer->loadMapBackground(mapIndex);
    scene->addChild(layer);
    return scene;

}

void outside::loadMapBackground(int mapIndex) {
    // 根据地图索引加载不同的 TMX 地图文件
    std::string tmxFileName;
    switch (mapIndex) {
        case 0:
            tmxFileName = "tiledmap/Farm.tmx";
            break;
        case 1:
            tmxFileName = "tiledmap/new.tmx";
            break;
        case 2:
            tmxFileName = "tiledmap/my_map.tmx";
            break;
        case 3:
            tmxFileName = "tiledmap/Farm.tmx";
            break;
        default:
            //tmxFileName = "tiledmap/default.tmx";
            break;
    }
    // 加载背景图片
    auto tiledMap = TMXTiledMap::create(tmxFileName);
    if (tiledMap) {
        // 设置地图位置
        tiledMap->setPosition(Vec2(-500, -200));
        tiledMap->setScale(3);
        this->addChild(tiledMap, 0);

        auto imageView = ImageView::create("picture/time.png");
        if (imageView) {
            // 设置位置
            imageView->setPosition(Vec2(3 * 1500 - 100, 3 * 1100 + 1450 - 100));
            // 添加到场景
            this->addChild(imageView);
        }
       
    
        _meta = tiledMap->getLayer("meta");
        _meta->setVisible(false);

        TMXObjectGroup* objects = tiledMap->getObjectGroup("objects");
        CCASSERT(NULL != objects, "'objects' object group not found");
        auto spawnPoint = objects->getObject("lake");
        int x = spawnPoint["x"].asInt();
        int y = spawnPoint["y"].asInt();

        //创建动物
        //绵羊
        for (int i = 0; i < 5; i++) {
            auto sheep = Sheep::create("animal/Sheep1.png");
            if (sheep == nullptr) {
                CCLOG("Error: Failed to create sheep!");
                return;
            }
            this->addChild(sheep);
        }

        //牛
        auto cow=Cow::create("animal/Cow1.png");
        if (cow == nullptr) {
            CCLOG("Error: Failed to create cow!");
            return;
        }
        cow->setScale(3);
        this->addChild(cow);

        //鹦鹉
        auto parrot=Parrot::create("animal/Parrot1.png");
        if (parrot == nullptr) {
            CCLOG("Error: Failed to create parrot!");
            return;
        }
        parrot->setScale(3);
        this->addChild(parrot);

        //创建主角人物
        characteraction = CharacterWithTools::create("character/Dana0.png");
        if (characteraction == nullptr) {
            CCLOG("Error: Failed to create character!");
            return;
        }

        characteraction->setPosition(Vec2(3 * x + 600, 3 * y + 2000));
        this->addChild(characteraction);

        this->scheduleUpdate();
        // 在每帧中更新视点位置，使地图始终跟随人物
            this->schedule([=](float deltaTime) {
            // 获取人物当前的世界坐标
            Vec2 characterPosition = characteraction->getPosition();



            // 更新视点，确保地图始终跟随人物
            setViewPointCenter(characterPosition, tiledMap);


            if (characterPosition.x >= 3460 &&
                characterPosition.x <= 3500 &&
                characterPosition.y >= 3570 &&
                characterPosition.y <= 3610)
            {
                // 在切换场景之前保存状态
                SceneStateManager::getInstance()->saveSceneState(
                    characteraction->getPosition(),
                    tiledMap->getName()
                );
                
                // ==================== 外观模式: 重构场景切换 ====================
                /**
                 * 使用Facade模式重构后的代码
                 * 如果人物进入指定范围，则切换场景
                 * 通过GameSceneFacade统一管理场景切换，而不是直接调用Director和intovalley
                 */
                if (!inZones["zone1"]) {
                    GameSceneFacade::enterHouseScene();

                    inZones["zone1"] =true;
                }
                else
                    inZones["zone1"] =false;
            }

            if (characterPosition.x >= 3000 &&
                characterPosition.x <= 3060 &&
                characterPosition.y >= 4740 &&
                characterPosition.y <= 4770)
            {
                /**
                 * 使用Facade模式重构后的代码
                 * 如果人物进入指定范围，则切换场景
                 * 通过GameSceneFacade统一管理场景切换，而不是直接调用Director和othersence
                 */
                if (!inZones["zone2"]) {
                    GameSceneFacade::enterOtherAreaScene();

                    inZones["zone2"] = true;
                }
                else
                    inZones["zone2"] = false;
            }
            }, "view_point_update_key");
      
    }
    else {
        log("Failed to load TMX file: %s", tmxFileName.c_str());
    }

}

bool outside::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 初始化成员变量
    _personalInterfaceLayer = nullptr;
    _menuWindow = nullptr;
    _closeButton = nullptr;
    _isPersonalInterfaceVisible = false;
    _currentImageIndex = 1;
    _selectedButtonIndex = -1;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    _rainParticleSystem = ParticleRain::create();
    this->addChild(_rainParticleSystem, 12);
    _rainParticleSystem->setPosition(Vec2(3470, 3560));
    _rainParticleSystem->resetSystem(); // 开始发射粒子
    _rainParticleSystem->setStartSize(10.0f); // 粒子生命周期的开始大小
    _rainParticleSystem->setEndSize(20.0f);   // 粒子生命周期的结束大小

    // 设置粒子的开始颜色为海的蓝色（完全不透明）
    _rainParticleSystem->setStartColor(Color4F(0.0f, 0.5f, 1.0f, 1.0f));

    // 设置粒子的结束颜色为海的蓝色（半透明）
    _rainParticleSystem->setEndColor(Color4F(0.0f, 0.3f, 0.6f, 0.5f));


    _rainParticleSystem->setStartSize(15.0f);
    _rainParticleSystem->setEndSize(15.0f);

    this->scheduleOnce([&](float dt) {

        // 创建实体管理器（管理动物/作物等场景实体）
        _entityManager = EntityManager::create(this);
        if (_entityManager) {
            this->addChild(_entityManager);
        }
        _rainParticleSystem->stopSystem(); // 停止粒子系统
        }, 40.0f, "stopRainTimer");

    // 创建并启用输入管理器（处理键盘/输入）
    _inputManager = new InputManager(this, [this]() {
        // toggle UI when InputManager detects the key
        if (_isPersonalInterfaceVisible) hidePersonalInterface(); else showPersonalInterface();
    });
    _inputManager->enable();

    _uiManager = new UIManager(this);

    // pass showDialog callback to NPCManager so UI is handled by UIManager
    _npcManager = new NPCManager(this, [this]() {
        if (characteraction) return characteraction->getPosition();
        return Vec2::ZERO;
    }, [this](const std::string& tex, const Vec2& pos, float dur) {
        if (_uiManager) _uiManager->showNPCDialog(tex, pos, dur);
    });

    NPCSpec npc1;
    npc1.normalTexture = "bag/npc1.png";
    npc1.selectedTexture = "bag/npc2.png";
    npc1.position = Vec2(800, 700);
    npc1.scale = 4.0f;
    npc1.dialogTexture = "picture/dialog.png";
    npc1.dialogPosition = Vec2(900, 400);
    npc1.proximityThreshold = 100.0f;
    _npcManager->spawnNPC(npc1);

    NPCSpec npc2;
    npc2.normalTexture = "bag/npc3.png";
    npc2.selectedTexture = "bag/npc4.png";
    npc2.position = Vec2(4100, 650);
    npc2.scale = 0.8f;
    npc2.dialogTexture = "picture/dialog2.png";
    npc2.dialogPosition = Vec2(4100, 400);
    npc2.proximityThreshold = 100.0f;
    _npcManager->spawnNPC(npc2);

    // 启动全局时间发布器（每秒计算并发布游戏内时间）
    TimePublisher::getInstance()->start(1.0f);

   
    // 创建签到窗口
    auto qiandaoWindow = Sprite::create("picture/qiandao.png");

    qiandaoWindow->setPosition(3 * 890 + 600, 3 * 740 + 1300);
    this->addChild(qiandaoWindow, 10); // 设置较高的z轴，确保窗口在最上层
            // 创建实体：由 EntityManager 根据地图上的 objects 对象组来生成（如果存在）
            if (_entityManager) {
                _entityManager->spawnFromMap(tiledMap);
            }

    //钓鱼
    auto fishing = Button::create("picture/tofish.png", "picture/tofish2.png");
    fishing->setPosition(Vec2(3 * 890 + 1000, 3 * 740 - 210));
    this->addChild(fishing,3);
    fishing->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            if (_uiManager) {
                _uiManager->toggleFishing();
            }
        }
    });
    
  
    this->scheduleUpdate();

    return true;
}
// ==================== 使用观察者模式重构修改updateTime函数：改为“发布 MinuteChanged 事件” ====================
//**updateTime 只负责“产生时间数据 + 发布事件”;具体 UI 更新放到 onNotify 中//

void outside::updateTime(float dt) {

    auto currentTime = std::chrono::high_resolution_clock::now();

    // 计算从游戏开始到现在的现实时间流逝（以秒为单位）
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - gameStartTime).count();

    // 将现实时间转换为游戏内时间（每0.7秒等于游戏内的一分钟）
    int elapsedTime = static_cast<int>(duration / 0.7f);
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);

    // 更新分钟数
    timeinfo->tm_min += elapsedTime / 60;
    mktime(timeinfo); // 更新时间结构体

    // 格式化时间为字符串
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%H:%M", timeinfo);

    // ★ 新增：不在这里直接改 Label，而是发布 MinuteChanged 事件
    cocos2d::Value timeStr(buffer);
    EventCenter::getInstance()->publish(EventType::MinuteChanged, this, timeStr);
}
// ==================== 使用观察者模式重构新增onNotify函数：真正处理 UI 更新” ====================

void outside::onNotify(const EventData& event)
{
    switch (event.type) {
    case EventType::MinuteChanged:
    {
        // 事件 extra 中存放的是时间字符串
        std::string timeStr = event.extra.asString();

        auto label = dynamic_cast<cocos2d::Label*>(getChildByName("timeLabel"));
        if (label) {
            label->setString(timeStr);
        } else {
            CCLOG("outside::onNotify - timeLabel not found.");
        }
        break;
    }
  
    default:
        break;
    }
}


void outside::setViewPointCenter(Point position, cocos2d::TMXTiledMap* tiledMap) {
    const auto winSize = Director::getInstance()->getWinSize();
    float scale = tiledMap->getScale(); // 获取当前的缩放比例

    // 计算实际的视图中心坐标（考虑缩放）
    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);

    // 计算缩放后的地图尺寸
    float mapWidth = tiledMap->getMapSize().width * tiledMap->getTileSize().width * scale;
    float mapHeight = tiledMap->getMapSize().height * tiledMap->getTileSize().height * scale;

    // 确保视点不会超出地图的范围
    x = MIN(x, mapWidth - winSize.width / 2);
    y = MIN(y, mapHeight - winSize.height / 2);

    // 计算视点实际位置
    auto actualPosition = Point(x, y);

    // 屏幕中心点
    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);

    // 计算新的视点位置
    auto viewPoint = centerOfView - actualPosition;

    // 更新视图位置
    this->setPosition(viewPoint);
}


Point outside::tileCoordForPosition(cocos2d::Point position, cocos2d::TMXTiledMap* tiledMap)
{
    int x = position.x /  tiledMap->getTileSize().width;
    int y = (( tiledMap->getMapSize().height *  tiledMap->getTileSize().height) - position.y) /  tiledMap->getTileSize().height;
    return Point(x, y);
}


void outside::update(float delta, cocos2d::Sprite* _player,cocos2d::TMXTiledMap* tiledMap) {
    Vec2 playerPosition = _player->getPosition();

    // 定义触发场景切换的位置
    Vec2 triggerPosition = Vec2(900, 1300); 

    // 检查玩家是否到达了触发位置
    if (playerPosition.x == triggerPosition.x && playerPosition.y == triggerPosition.y) {
        // 触发场景切换
        changeScene();
    }

    Vec2 characterPosition = characteraction->getPosition();

    // 更新视点，确保人物始终位于屏幕中心
    setViewPointCenter(characterPosition, tiledMap);
}

void outside::changeScene() {
    // 创建并切换到Scene2
    auto scene = intovalley::createintovalleyScene(); 
    Director::getInstance()->replaceScene(scene);
}


void outside::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    // 检查按下的键是否为 E 键
    if (keyCode == EventKeyboard::KeyCode::KEY_E)
    {
        // 切换个人界面的显示状态
        if (_isPersonalInterfaceVisible)
        {
            hidePersonalInterface();
        }
        else
        {
            showPersonalInterface();
        }
    }
}

void outside::hidePersonalInterface()
{
    if (_uiManager) _uiManager->hidePersonalInterface();
}
void outside::showPersonalInterface()
{
    if (_uiManager) _uiManager->showPersonalInterface(characteraction ? characteraction->getPosition() : Vec2::ZERO);
}

void outside::selectImage(int index)
{
    if (_uiManager) _uiManager->selectImage(index);
}

void outside::showVerticalButtons()
{
    if (_uiManager) _uiManager->showVerticalButtons();
}


void outside::showVerticalButtons2()
{
    if (_uiManager) _uiManager->showVerticalButtons2();



void outside::removeVerticalButtons()
{
    if (_uiManager) _uiManager->removeVerticalButtons();
}

void outside::showNewWindow()
{
    if (_uiManager) _uiManager->showNewWindow(_clickedButtonIndex);
}


void outside::closePersonalInterface(Ref* sender)
{
    if (_uiManager) _uiManager->hidePersonalInterface();
}

 // ==================== 使用观察者模式重构新增：从事件中心注销 ====================
outside::~outside()
{
    EventCenter::getInstance()->detach(this);
    if (_uiManager) {
        delete _uiManager;
        _uiManager = nullptr;
    }
    if (_inputManager) {
        delete _inputManager;
        _inputManager = nullptr;
    }
    if (_npcManager) {
        delete _npcManager;
        _npcManager = nullptr;
    }
    if (_entityManager) {
        _entityManager->clearAll();
        _entityManager->removeFromParentAndCleanup(true);
        _entityManager = nullptr;
    }
}
