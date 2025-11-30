/****************************************************************************
*
* Refactored with Builder Pattern and Object Pool Pattern
* 
****************************************************************************/
#pragma once
#ifndef __CHARACTER_WITH_TOOLS_H__
#define __CHARACTER_WITH_TOOLS_H__
#include "cocos2d.h"

USING_NS_CC;

class Crop;

extern std::map<Vec2, bool> cropPositions;

#define gridWidth 150.0f
#define gridHeight 120.0f

// ==================== Object Pool Pattern: Add getPooledCrop ====================
static std::vector<Crop*> cropPool;
static std::map<std::string, std::vector<Sprite*>> toolPool;

static Crop* getPooledCrop() {
    if (!cropPool.empty()) {
        Crop* c = cropPool.back();
        cropPool.pop_back();
        c->setVisible(true);
        return c;
    }
    return Crop::create("plant/cropseed.png");
}

// ==================== Object Pool Pattern: Add recycleCrop ====================
static void recycleCrop(Crop* crop) {
    crop->stopAllActions();
    crop->setVisible(false);
    cropPool.push_back(crop);
}

// ==================== Object Pool Pattern: Add getPooledTool ====================
/**
* Get tool instance of specified type from tool object pool
*/
static Sprite* getPooledTool(const std::string& filename) {
    auto& list = toolPool[filename];
    if (!list.empty()) {
        Sprite* tool = list.back();
        list.pop_back();
        tool->setVisible(true);
        return tool;
    }
    return Sprite::create(filename);
}

// ==================== Object Pool Pattern: Add recycleTool ====================
static void recycleTool(Sprite* tool, const std::string& filename) {
    tool->stopAllActions();
    tool->setVisible(false);
    toolPool[filename].push_back(tool);
}

// ==================== Builder Pattern: Add AnimationBuilder ====================
/**
* Build animation instance
*/
class AnimationBuilder {
public:
    std::string prefix;
    int s, e;
    float delayUnit;

    AnimationBuilder& from(const std::string& p) { prefix = p; return *this; }
    AnimationBuilder& frames(int a, int b) { s = a; e = b; return *this; }
    AnimationBuilder& delay(float d) { delayUnit = d; return *this; }

    Animation* build() {
        auto anim = Animation::create();
        for (int i = s; i <= e; i++)
            anim->addSpriteFrameWithFile(prefix + std::to_string(i) + ".png");
        anim->setDelayPerUnit(delayUnit);
        anim->setLoops(-1);
        return anim;
    }
};

// =============================
// Character Class
// =============================
class CharacterWithTools : public Sprite {
public:
    static CharacterWithTools* create(const std::string& filename);

    CharacterWithTools();
    ~CharacterWithTools();

    virtual bool init(const std::string& filename);
    void move();
    void update(float delta) override;
    bool checkCrop(Vec2 position);
    void plantcrop(Vec2 position);

private:
    Vec2 velocity;
    Animation* walkLeftAnimation;
    Animation* walkRightAnimation;
    Animation* walkUpAnimation;
    Animation* walkDownAnimation;
    Animate* walkLeftAnimate;
    Animate* walkRightAnimate;
    Animate* walkUpAnimate;
    Animate* walkDownAnimate;

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void usetools(const std::string& filename);
};

#endif