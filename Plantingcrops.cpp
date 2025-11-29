#include "Crop.h"
#include "SimpleAudioEngine.h"
#include "intovalley.h"
#include "GameTimeSystem.h"
#include "Plantingcrops.h"

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

// 状态重置方法实现（用于对象池复用）
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

void Crop::update(float delta)
{
    if (growthTime >= matureTime * 2 && state != State::harvested && !watered) {
        this->setTexture("plant/cropdead.png");
        state = State::dead;
    }

    if (state == State::seed) {
        growthTime += delta;
        if (growthTime >= matureTime) {
            state = State::growing;
            this->setTexture("plant/cropgrowing.png");
        }
    }
    else if (state == State::growing) {
        growthTime += delta;
        if (growthTime >= matureTime * 2) {
            state = State::matured;
            this->setTexture("plant/cropmature.png");
        }
    }
    else if (state == State::matured) {
        growthTime += delta;
        if (growthTime >= matureTime * 3) {
            state = State::harvested;
            this->setTexture("plant/cropharvested.png");
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

void Crop::harvest()
{
    if (state == State::harvested || state == State::dead) {
        Vec2 pos = this->getPosition();
        int gridX = pos.x / gridWidth;
        int gridY = pos.y / gridHeight;

        Vec2 grid(gridX, gridY);
        cropPositions[grid] = false;

        this->removeFromParent();
        // 收获后回收到对象池（而非直接销毁）
        recycleCrop(this); // 调用对象池的回收函数
    }
}

/*-------------------------------------------------------
 |  CropFactory 工厂实现
 -------------------------------------------------------*/
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

// 工厂类配置方法实现（用于对象池复用时初始化不同类型作物）
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