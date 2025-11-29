/****************************************************************************
 *
 * 使用工厂模式和对象池模式和观察者模式重构后的代码
 *
 ****************************************************************************/
#include "Crop.h"
#include "SimpleAudioEngine.h"
#include "intovalley.h"
#include "GameTimeSystem.h"
#include "Plantingcrops.h"
// ==================== 使用观察者模式重构新增 ====================
#include "EventCenter.h"   // 新增
#include "EventType.h"     // 新增

USING_NS_CC;

Crop::Crop() {
    state = State::seed;
    growthTime = 0;
    pregrowthTime = 0;
    matureTime = 1.0f;
    watered = false;
}

Crop::~Crop() {}

Crop* Crop::create()
{
    auto crop = new (std::nothrow) Crop();
    if (crop && crop->init("plant/cropseed.png")) {   
        crop->autorelease();
        return crop;
    }
    CC_SAFE_DELETE(crop);
    return nullptr;
}

bool Crop::init(const std::string& filename)
{
    if (!Sprite::initWithFile(filename)) {
        CCLOG("Error loading crop sprite: %s", filename.c_str());
        return false;
    }

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Crop::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Crop::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    this->scheduleUpdate();
    return true;
}

// ==================== 对象池模式：新增resetState ====================
/**
* 作物状态重置（用于复用）
*/
void Crop::resetState() {
    // 重置生长状态参数
    state = State::seed;
    growthTime = 0;
    pregrowthTime = 0;
    watered = false;

    // 重置视觉表现（恢复种子纹理）
    this->setTexture("plant/cropseed.png");
    this->setVisible(true);

    // 停止所有动作并重新开启更新（确保生长逻辑正常）
    this->stopAllActions();
    if (!this->isScheduledUpdate()) {
        this->scheduleUpdate();
    }
}

// ==================== 使用观察者模式重构后的update函数 ====================
 

void Crop::update(float delta) {
    // 1）未浇水，超过 2 倍成熟时间直接死亡
    if (growthTime >= matureTime * 2 && state != State::harvested
        && watered == false) {
        this->setTexture("plant/cropdead.png");
        state = State::dead;

        // ★ 新增：通知“作物死亡”事件
        EventCenter::getInstance()->publish(EventType::CropDead, this);
    }

    // 2）种子阶段 -> 发芽(growing)
    if (state == State::seed) {
        growthTime += delta;
        if (growthTime >= matureTime) {
            state = State::growing;
            this->setTexture("plant/cropgrowing.png");

            // ★ 新增：通知“作物发芽”事件
            EventCenter::getInstance()->publish(EventType::CropGerminated, this);
        }
    }
    // 3）生长期 -> 成熟(matured)
    else if (state == State::growing) {
        growthTime += delta;
        if (growthTime >= matureTime * 2) {
            state = State::matured;
            this->setTexture("plant/cropmature.png");

            // ★ 新增：通知“作物成熟”事件
            EventCenter::getInstance()->publish(EventType::CropMatured, this);
        } 
    }
    // 4）成熟阶段 -> 逾期未被收获而被系统自动回收
    else if (state == State::matured) {
        growthTime += delta;
        if (growthTime >= matureTime * 3) {
            state = State::harvested;
            this->setTexture("plant/cropharvested.png");

            // ★ 新增：通知“作物已收获(自动结束生命周期)”事件
            EventCenter::getInstance()->publish(EventType::CropHarvested, this);
        }
    }
}


State Crop::getState() const {
    return state;
}

void Crop::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_J)
        harvest();
    if (keyCode == EventKeyboard::KeyCode::KEY_K)
        watered = true;
}

// ==================== 对象池模式：新增harvest ====================
/**
* 作物收获与回收
*/
// ==================== 观察者模式：新增手动收获事件 ====================
//补全系统缺失的核心事件通路，使外部模块能感知“作物被收获”这一关键行为。
void Crop::harvest()
{
    if (state == State::harvested || state == State::dead) {
        Vec2 pos = this->getPosition();
        int gridX = pos.x / gridWidth;
        int gridY = pos.y / gridHeight;

        Vec2 grid(gridX, gridY);
        cropPositions[grid] = false;

        // ★ 新增：手动收获事件
        EventCenter::getInstance()->publish(EventType::CropHarvested, this);

        this->removeFromParent();
        // 收获后回收到对象池（而非直接销毁）
        recycleCrop(this); // 调用对象池的回收函数
    }
}

// ==================== 工厂模式: 新增CropFactory ====================
Crop* CropFactory::createCrop(const std::string& cropType)
{
    auto crop = Crop::create();
    if (!crop) return nullptr;

    if (cropType == "wheat") {
        crop->setInitialTexture("plant/wheat_seed.png");
        crop->setMatureTime(3.0);
    }
    else if (cropType == "corn") {
        crop->setInitialTexture("plant/corn_seed.png");
        crop->setMatureTime(4.0);
    }
    else if (cropType == "pumpkin") {
        crop->setInitialTexture("plant/pumpkin_seed.png");
        crop->setMatureTime(5.0);
    }
    else {
        crop->setInitialTexture("plant/cropseed.png");
        crop->setMatureTime(3.0);
    }

    return crop;
}

// ==================== 工厂模式：新增configureCrop ====================
/**
* 作物配置（用于对象池复用初始化）
*/
void CropFactory::configureCrop(Crop* crop, const std::string& cropType) {
    if (!crop) return;

    crop->resetState(); // 先重置状态，再配置类型属性
    if (cropType == "wheat") {
        crop->setInitialTexture("plant/wheat_seed.png");
        crop->setMatureTime(3.0);
    }
    else if (cropType == "corn") {
        crop->setInitialTexture("plant/corn_seed.png");
        crop->setMatureTime(4.0);
    }
    else if (cropType == "pumpkin") {
        crop->setInitialTexture("plant/pumpkin_seed.png");
        crop->setMatureTime(5.0);
    }
    else {
        crop->setInitialTexture("plant/cropseed.png");
        crop->setMatureTime(3.0);
    }
}