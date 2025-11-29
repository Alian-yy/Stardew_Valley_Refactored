/****************************************************************************
 * 
 * 使用装饰器模式重构后的作物效果系统
 * CropDecorator.h - 动态给作物添加各种效果
 * 
 ****************************************************************************/

#ifndef __CROP_DECORATOR_H__
#define __CROP_DECORATOR_H__

#include "Plantingcrops.h"
#include "EventCenter.h"
#include "EventType.h"
#include "cocos2d.h"
USING_NS_CC;

// ==================== 装饰器模式：作物组件接口 ====================
/**
 * 作物组件接口 - 定义作物的基本操作
 * 装饰器模式：这是被装饰的对象接口
 */
class ICropComponent {
public:
    virtual ~ICropComponent() = default;
    
    // 更新作物（生长逻辑）
    virtual void update(float delta) = 0;
    
    // 获取生长速度倍数（1.0为正常速度）
    virtual float getGrowthSpeedMultiplier() const = 0;
    
    // 获取作物状态
    virtual State getState() const = 0;
    
    // 收获作物
    virtual void harvest() = 0;
    
    // 获取作物精灵（用于显示）
    virtual Sprite* getSprite() = 0;
    
    // 获取成熟时间
    virtual double getMatureTime() const = 0;
    
    // 设置成熟时间
    virtual void setMatureTime(double time) = 0;
};

// ==================== 装饰器模式：具体组件（被装饰的作物） ====================
/**
 * 具体作物组件 - 包装原始的 Crop 类
 */
class ConcreteCropComponent : public ICropComponent {
private:
    Crop* crop;
    
public:
    ConcreteCropComponent(Crop* c) : crop(c) {}
    
    void update(float delta) override {
        if (crop) crop->update(delta);
    }
    
    float getGrowthSpeedMultiplier() const override {
        return 1.0f; // 基础作物正常速度
    }
    
    State getState() const override {
        return crop ? crop->getState() : State::dead;
    }
    
    void harvest() override {
        if (crop) crop->harvest();
    }
    
    Sprite* getSprite() override {
        return crop;
    }
    
    double getMatureTime() const override {
        // 需要通过其他方式获取，这里简化处理
        return 1.0;
    }
    
    void setMatureTime(double time) override {
        // 需要通过其他方式设置，这里简化处理
    }
};

// ==================== 装饰器模式：装饰器基类 ====================
/**
 * 作物装饰器基类 - 所有具体装饰器的基类
 * 装饰器模式：这是装饰器的抽象类
 */
class CropDecorator : public ICropComponent {
protected:
    ICropComponent* component; // 被装饰的组件
    
public:
    CropDecorator(ICropComponent* comp) : component(comp) {}
    
    virtual ~CropDecorator() {
        // 注意：这里不删除 component，因为它可能被其他装饰器共享
    }
    
    // 默认实现：直接转发给被装饰的组件
    void update(float delta) override {
        if (component) component->update(delta);
    }
    
    float getGrowthSpeedMultiplier() const override {
        return component ? component->getGrowthSpeedMultiplier() : 1.0f;
    }
    
    State getState() const override {
        return component ? component->getState() : State::dead;
    }
    
    void harvest() override {
        if (component) component->harvest();
    }
    
    Sprite* getSprite() override {
        return component ? component->getSprite() : nullptr;
    }
    
    double getMatureTime() const override {
        return component ? component->getMatureTime() : 1.0;
    }
    
    void setMatureTime(double time) override {
        if (component) component->setMatureTime(time);
    }
};

// ==================== 装饰器模式：加速生长装饰器 ====================
/**
 * 加速生长装饰器 - 使作物生长速度加快
 */
class FastGrowthDecorator : public CropDecorator {
private:
    float speedMultiplier; // 速度倍数，例如 1.5 表示 1.5 倍速
    
public:
    FastGrowthDecorator(ICropComponent* comp, float multiplier = 1.5f)
        : CropDecorator(comp), speedMultiplier(multiplier) {}
    
    void update(float delta) override {
        // 加速生长：将时间增量乘以速度倍数
        if (component) {
            component->update(delta * speedMultiplier);
        }
    }
    
    float getGrowthSpeedMultiplier() const override {
        float baseMultiplier = component ? component->getGrowthSpeedMultiplier() : 1.0f;
        return baseMultiplier * speedMultiplier;
    }
};

// ==================== 装饰器模式：防虫装饰器 ====================
/**
 * 防虫装饰器 - 防止作物因虫害死亡
 */
class PestResistantDecorator : public CropDecorator {
private:
    bool isProtected;
    
public:
    PestResistantDecorator(ICropComponent* comp)
        : CropDecorator(comp), isProtected(true) {}
    
    void update(float delta) override {
        if (component) {
            // 在更新前检查状态，防止因虫害死亡
            State currentState = component->getState();
            component->update(delta);
            
            // 如果作物因未浇水死亡，但处于保护状态，可以延迟死亡
            // （这里简化处理，实际可以更复杂）
        }
    }
    
    // 可以添加其他防虫相关的方法
    bool isPestProtected() const { return isProtected; }
};

// ==================== 装饰器模式：产量提升装饰器 ====================
/**
 * 产量提升装饰器 - 收获时获得更多产量
 */
class HighYieldDecorator : public CropDecorator {
private:
    float yieldMultiplier; // 产量倍数
    
public:
    HighYieldDecorator(ICropComponent* comp, float multiplier = 2.0f)
        : CropDecorator(comp), yieldMultiplier(multiplier) {}
    
    void harvest() override {
        if (component) {
            // 收获前可以添加产量提升逻辑
            // 例如：发布事件通知产量提升
            EventCenter::getInstance()->publish(
                EventType::CropHarvested,
                component->getSprite(),
                cocos2d::Value(yieldMultiplier)
            );
            component->harvest();
        }
    }
    
    float getYieldMultiplier() const { return yieldMultiplier; }
};

// ==================== 装饰器模式：视觉效果装饰器 ====================
/**
 * 视觉效果装饰器 - 给作物添加视觉特效（如光环、粒子效果）
 */
class VisualEffectDecorator : public CropDecorator {
private:
    ParticleSystem* effectParticle; // 粒子效果
    Sprite* glowEffect; // 光环效果
    
public:
    VisualEffectDecorator(ICropComponent* comp, const std::string& effectType);
    ~VisualEffectDecorator();
    
    void update(float delta) override {
        if (component) {
            component->update(delta);
            
            // 更新视觉效果位置，跟随作物
            if (component->getSprite()) {
                Vec2 cropPos = component->getSprite()->getPosition();
                if (effectParticle) {
                    effectParticle->setPosition(cropPos);
                }
                if (glowEffect) {
                    glowEffect->setPosition(cropPos);
                }
            }
        }
    }
    
    Sprite* getSprite() override {
        return component ? component->getSprite() : nullptr;
    }
};

#endif // __CROP_DECORATOR_H__

