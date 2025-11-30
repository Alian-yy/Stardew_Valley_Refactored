/****************************************************************************
 *
 * Refactored with Factory Method, Object Pool and Observer design patterns.
 *
 ****************************************************************************/
#include "Plantingcrops.h"
#include "SimpleAudioEngine.h"
#include "intovalley.h"
#include "GameTimeSystem.h"
#include "characterAction.h"
 // ==================== Observer Pattern: New Additions ====================
#include "EventCenter.h"   // New addition
#include "EventType.h"     // New addition

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

// ==================== Object Pool Pattern: Add resetState ====================
/**
* Reset crop state (for reuse)
*/
void Crop::resetState() {
    // Reset growth state parameters
    state = State::seed;
    growthTime = 0;
    pregrowthTime = 0;
    watered = false;

    // Reset visual appearance (restore seed texture)
    this->setTexture("plant/cropseed.png");
    this->setVisible(true);

    // Stop all actions and restart update (ensure normal growth logic)
    this->stopAllActions();
    if (!this->isScheduledUpdate()) {
        this->scheduleUpdate();
    }
}

// ==================== Observer Pattern: Refactored update Function ====================


void Crop::update(float delta) {
    // 1) If not watered and exceeds 2x mature time, die directly
    if (growthTime >= matureTime * 2 && state != State::harvested
        && watered == false) {
        this->setTexture("plant/cropdead.png");
        state = State::dead;

        // ★ New addition: Notify "Crop Dead" event
        EventCenter::getInstance()->publish(EventType::CropDead, this);
    }

    // 2) Seed phase -> Germination (growing)
    if (state == State::seed) {
        growthTime += delta;
        if (growthTime >= matureTime) {
            state = State::growing;
            this->setTexture("plant/cropgrowing.png");

            // ★ New addition: Notify "Crop Germinated" event
            EventCenter::getInstance()->publish(EventType::CropGerminated, this);
        }
    }
    // 3) Growing phase -> Mature (matured)
    else if (state == State::growing) {
        growthTime += delta;
        if (growthTime >= matureTime * 2) {
            state = State::matured;
            this->setTexture("plant/cropmature.png");

            // ★ New addition: Notify "Crop Matured" event
            EventCenter::getInstance()->publish(EventType::CropMatured, this);
        }
    }
    // 4) Mature phase -> Automatically recycled by system if not harvested overdue
    else if (state == State::matured) {
        growthTime += delta;
        if (growthTime >= matureTime * 3) {
            state = State::harvested;
            this->setTexture("plant/cropharvested.png");

            // ★ New addition: Notify "Crop Harvested (auto lifecycle end)" event
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

// ==================== Object Pool Pattern: Add harvest ====================
/**
* Crop harvesting and recycling
*/
// ==================== Observer Pattern: Add Manual Harvest Event ====================
void Crop::harvest()
{
    if (state == State::matured) {
        Vec2 pos = this->getPosition();
        int gridX = pos.x / gridWidth;
        int gridY = pos.y / gridHeight;

        Vec2 grid(gridX, gridY);
        cropPositions[grid] = false;

        // ★ New addition: Manual harvest event
        EventCenter::getInstance()->publish(EventType::CropHarvested, this);

        this->removeFromParent();
        // Recycle to object pool after harvesting (instead of direct destruction)
        recycleCrop(this); // Call object pool's recycle function
    }
}

// ==================== Factory Pattern: Add CropFactory ====================
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

// ==================== Factory Pattern: Add configureCrop ====================
/**
* Crop configuration (for object pool reuse initialization)
*/
void CropFactory::configureCrop(Crop* crop, const std::string& cropType) {
    if (!crop) return;

    crop->resetState(); // Reset state first, then configure type attributes
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