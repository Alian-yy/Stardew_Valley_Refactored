/****************************************************************************
* 使用生成器模式和对象池模式的角色实现代码
* CharacterWithTools.cpp - 角色功能实现
* 实现角色动画构建、工具使用、作物种植等功能，结合对象池优化资源管理
****************************************************************************/
#include "characterAciton.h"
#include "outside.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "intovalley.h"
#include "SimpleAudioEngine.h"
#include "menu.h"
#include "GameTimeSystem.h"
#include "Plantingcrops.h"
#include "CharacterWithTools.h"

std::map<Vec2, bool> cropPositions;

CharacterWithTools::CharacterWithTools()
    : walkLeftAnimation(nullptr), walkRightAnimation(nullptr),
    walkUpAnimation(nullptr), walkDownAnimation(nullptr),
    walkLeftAnimate(nullptr), walkRightAnimate(nullptr),
    walkUpAnimate(nullptr), walkDownAnimate(nullptr) {
    velocity = Vec2(0, 0);
}

CharacterWithTools::~CharacterWithTools() {}

CharacterWithTools* CharacterWithTools::create(const std::string& filename) {
    auto c = new (std::nothrow) CharacterWithTools();
    if (c && c->init(filename)) {
        c->autorelease();
        return c;
    }
    CC_SAFE_DELETE(c);
    return nullptr;
}

bool CharacterWithTools::init(const std::string& filename) {
    if (!Sprite::initWithFile(filename)) {
        CCLOG("Error: Failed to load character image.");
        return false;
    }

    velocity = Vec2::ZERO;

    // ========== 生成器模式：使用 AnimationBuilder 构建动画 ==========
    walkLeftAnimation = AnimationBuilder().from("character/Danaleft").frames(1, 3).delay(0.1f).build();
    walkLeftAnimate = Animate::create(walkLeftAnimation); walkLeftAnimate->retain();

    walkRightAnimation = AnimationBuilder().from("character/Danaright").frames(1, 3).delay(0.1f).build();
    walkRightAnimate = Animate::create(walkRightAnimation); walkRightAnimate->retain();

    walkUpAnimation = AnimationBuilder().from("character/Danaback").frames(1, 3).delay(0.1f).build();
    walkUpAnimate = Animate::create(walkUpAnimation); walkUpAnimate->retain();

    walkDownAnimation = AnimationBuilder().from("character/Dana").frames(1, 3).delay(0.1f).build();
    walkDownAnimate = Animate::create(walkDownAnimation); walkDownAnimate->retain();

    // 键盘事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(CharacterWithTools::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(CharacterWithTools::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    scheduleUpdate();
    return true;
}

void CharacterWithTools::move() {
    auto action = this->getActionByTag(1);

    if (velocity != Vec2::ZERO) {
        if (velocity.x < 0) {
            if (!action || action != walkLeftAnimate) {
                stopAllActions(); walkLeftAnimate->setTag(1); runAction(walkLeftAnimate);
            }
        }
        else if (velocity.x > 0) {
            if (!action || action != walkRightAnimate) {
                stopAllActions(); walkRightAnimate->setTag(1); runAction(walkRightAnimate);
            }
        }
        else if (velocity.y > 0) {
            if (!action || action != walkUpAnimate) {
                stopAllActions(); walkUpAnimate->setTag(1); runAction(walkUpAnimate);
            }
        }
        else if (velocity.y < 0) {
            if (!action || action != walkDownAnimate) {
                stopAllActions(); walkDownAnimate->setTag(1); runAction(walkDownAnimate);
            }
        }
    }
    else {
        if (action) stopAllActions();
    }
}

// ==================== 对象池模式：新增usetools ====================
/**
 * 工具使用实现
 */
void CharacterWithTools::usetools(const std::string& filename) {
    Sprite* tool = getPooledTool(filename);
    if (!tool) return;

    tool->setPosition(Vec2(50, 20));
    tool->setAnchorPoint(Vec2(0, 0));
    this->addChild(tool);

    tool->runAction(Sequence::create(
        RotateBy::create(0.3f, 90),
        RotateBy::create(0.3f, -90),
        DelayTime::create(0.1f),
        CallFunc::create([tool, filename]() {
            tool->removeFromParent();
            recycleTool(tool, filename);
            }),
        nullptr
    ));
}

void CharacterWithTools::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    velocity = Vec2::ZERO;

    if (keyCode == EventKeyboard::KeyCode::KEY_J) usetools("tools/axe.png");
    if (keyCode == EventKeyboard::KeyCode::KEY_K) usetools("tools/kettle.png");
    if (keyCode == EventKeyboard::KeyCode::KEY_L) usetools("tools/pickaxe.png");

    if (keyCode == EventKeyboard::KeyCode::KEY_W) velocity.y = 1;
    if (keyCode == EventKeyboard::KeyCode::KEY_S) velocity.y = -1;
    if (keyCode == EventKeyboard::KeyCode::KEY_A) velocity.x = -1;
    if (keyCode == EventKeyboard::KeyCode::KEY_D) velocity.x = 1;

    move();

    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
        Vec2 pos = this->getPosition();
        if (pos.x >= 350 * 3 && pos.x <= (350 + 320) * 3 && pos.y >= (830 - 300) * 3 && pos.y <= 850 * 3)
            plantcrop(pos);
    }
}

void CharacterWithTools::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    velocity = Vec2::ZERO;
    move();
}

void CharacterWithTools::update(float delta) {
    setPosition(getPosition() + velocity * delta * 1000);
}

bool CharacterWithTools::checkCrop(Vec2 position) {
    int gx = position.x / gridWidth;
    int gy = position.y / gridHeight;
    Vec2 gp(gx, gy);

    return cropPositions.find(gp) != cropPositions.end() && cropPositions[gp];
}

// ==================== 对象池模式：新增plantcrop ====================
/**
 * 作物种植实现
 */
void CharacterWithTools::plantcrop(Vec2 position) {
    int gx = position.x / gridWidth;
    int gy = position.y / gridHeight;
    Vec2 gp(gx, gy);

    if (checkCrop(position)) {
        CCLOG("Crop already exists here!");
        return;
    }

    Crop* crop = getPooledCrop();
    crop->setPosition(Vec2(position.x, position.y - 50));
    crop->setVisible(true);

    this->getParent()->addChild(crop);
    cropPositions[gp] = true;
}
