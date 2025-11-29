/****************************************************************************
 * 
 * 使用装饰器模式重构后的作物效果系统实现
 * CropDecorator.cpp
 * 
 ****************************************************************************/

#include "CropDecorator.h"
#include "EventCenter.h"
#include "EventType.h"

// ==================== 视觉效果装饰器实现 ====================
VisualEffectDecorator::VisualEffectDecorator(ICropComponent* comp, const std::string& effectType)
    : CropDecorator(comp), effectParticle(nullptr), glowEffect(nullptr) {
    
    if (component && component->getSprite()) {
        Sprite* cropSprite = component->getSprite();
        Node* parent = cropSprite->getParent();
        
        if (effectType == "glow") {
            // 创建光环效果
            glowEffect = Sprite::create("effects/glow.png");
            if (glowEffect && parent) {
                glowEffect->setPosition(cropSprite->getPosition());
                glowEffect->setScale(1.2f);
                glowEffect->setOpacity(180);
                parent->addChild(glowEffect, cropSprite->getLocalZOrder() - 1);
                
                // 添加呼吸动画效果
                auto fadeOut = FadeOut::create(1.0f);
                auto fadeIn = FadeIn::create(1.0f);
                auto sequence = Sequence::create(fadeOut, fadeIn, nullptr);
                auto repeat = RepeatForever::create(sequence);
                glowEffect->runAction(repeat);
            }
        }
        else if (effectType == "particle") {
            // 创建粒子效果
            effectParticle = ParticleSystemQuad::create("effects/sparkle.plist");
            if (effectParticle && parent) {
                effectParticle->setPosition(cropSprite->getPosition());
                parent->addChild(effectParticle, cropSprite->getLocalZOrder() + 1);
            }
        }
    }
}

VisualEffectDecorator::~VisualEffectDecorator() {
    if (effectParticle) {
        effectParticle->removeFromParent();
    }
    if (glowEffect) {
        glowEffect->removeFromParent();
    }
}

