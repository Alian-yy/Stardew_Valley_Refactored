/********************************************************************************
 *
 *   使用策略模式重构后新增的AnimationStrategy.h
 *
 ********************************************************************************/

#ifndef _ANIMATION_STRATEGY_H_
#define _ANIMATION_STRATEGY_H_

#include "cocos2d.h"
USING_NS_CC;

class AnimationStrategy {
public:
    virtual ~AnimationStrategy() = default;
    virtual void applyAnimation(Sprite* sprite) = 0;
};

class GenericAnimationStrategy : public AnimationStrategy {
private:
    std::string prefix;   
    int frameCount;
    float delay;

public:
    GenericAnimationStrategy(const std::string& animPrefix, int count = 4, float d = 0.1f)
        : prefix(animPrefix), frameCount(count), delay(d) {}

    void applyAnimation(Sprite* sprite) override {
        auto animation = Animation::create();
        bool hasValidFrame = false;
        for (int i = 1; i <= frameCount; ++i) {
            std::string frameName = prefix + std::to_string(i) + ".png";
            auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
            if (!frame) {
                auto texture = Director::getInstance()->getTextureCache()->addImage(frameName);
                if (texture) {
                    Rect rect = Rect::ZERO;
                    rect.size = texture->getContentSizeInPixels();
                    frame = SpriteFrame::createWithTexture(texture, rect);
                    hasValidFrame = true;
                }
            } else {
                hasValidFrame = true;
            }
            if (frame) {
                animation->addSpriteFrame(frame);
            }
        }

        if (!hasValidFrame) {
            CCLOG("Warning: No valid frames for animation prefix: %s", prefix.c_str());
            return;
        }

        animation->setDelayPerUnit(delay);
        animation->setLoops(-1); // loop forever
        auto animate = Animate::create(animation);
        sprite->stopAllActions();
        sprite->runAction(animate);
    }
};

#endif // _ANIMATION_STRATEGY_H_