/****************************************************************************
* 使用生成器模式和对象池模式重构后的代码
* characterAction.h - 带工具的角色类定义
* 提供角色移动、工具使用、作物种植功能，通过对象池优化资源复用，生成器模式简化动画构建
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

// ==================== 对象池模式：新增getPooledCrop ====================
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

// ==================== 对象池模式：新增recycleCrop ====================
static void recycleCrop(Crop* crop) {
    crop->stopAllActions();
    crop->setVisible(false);
    cropPool.push_back(crop);
}

// ==================== 对象池模式：新增getPooledTool ====================
/**
* 从工具对象池获取指定类型的工具实例
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

// ==================== 对象池模式：新增recycleTool ====================
static void recycleTool(Sprite* tool, const std::string& filename) {
    tool->stopAllActions();
    tool->setVisible(false);
    toolPool[filename].push_back(tool);
}

// ==================== 生成器模式：新增AnimationBuilder动画构建器 ====================
/**
* 构建动画实例
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
