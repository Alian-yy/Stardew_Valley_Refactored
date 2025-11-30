/********************************************************************************
 *
 * Refactored with State : add AnimalState.h
 *
 ********************************************************************************/

#ifndef _ANIMAL_STATE_H_
#define _ANIMAL_STATE_H_

#include "cocos2d.h"
#include "Animal.h"
#include "AnimationStrategy.h"
#include <memory>
USING_NS_CC;

class AnimalState {
public:
    virtual ~AnimalState() = default;
    virtual void enter(Animal* animal) = 0;
    virtual void update(Animal* animal, float delta) = 0;
    virtual void exit(Animal* animal) = 0;
    virtual std::string getName() const = 0;
};

// ------------------ Wandering ------------------
class WanderingState : public AnimalState {
public:
    void enter(Animal* animal) override {
        animal->setAnimationStrategy(
            std::make_unique<GenericAnimationStrategy>(animal->getAnimPrefix() + "_wander")        
        );
        animal->generateNewTarget();
    }

    void update(Animal* animal, float delta) override {
        Vec2 dir = animal->getTargetPosition() - animal->getPosition();
        if (dir.length() < 10.0f) {
            animal->generateNewTarget();
        } else {
            animal->setPosition(animal->getPosition() + dir.getNormalized() * animal->getSpeed() * delta);
        }
    }

    void exit(Animal* animal) override {}
    std::string getName() const override { return "Wandering"; }
};

// ------------------ Chasing ------------------
class ChasingState : public AnimalState {
private:
    Vec2 chaseTarget;
public:
    void setChaseTarget(const Vec2& target) { chaseTarget = target; }

    void enter(Animal* animal) override {
        animal->setAnimationStrategy(
            std::make_unique<GenericAnimationStrategy>(animal->getAnimPrefix() + "_chase")
        );
    }

    void update(Animal* animal, float delta) override {
        Vec2 dir = chaseTarget - animal->getPosition();
        float dist = dir.length();
        if (dist > 5.0f) {
            animal->setPosition(animal->getPosition() + dir.getNormalized() * animal->getSpeed() * 1.8f * delta);
        }
    }

    void exit(Animal* animal) override {}
    std::string getName() const override { return "Chasing"; }
};

// ------------------ Resting ------------------
class RestingState : public AnimalState {
private:
    float restTime = 0.0f;
    const float MAX_REST = 3.0f; // 休息3秒

public:
    void enter(Animal* animal) override {
        animal->setAnimationStrategy(
            std::make_unique<GenericAnimationStrategy>(animal->getAnimPrefix() + "_rest")
        );
        restTime = 0.0f;
    }

    void update(Animal* animal, float delta) override {
        restTime += delta;
        if (restTime >= MAX_REST) {
            animal->changeState(std::make_unique<WanderingState>());
        }
    }

    void exit(Animal* animal) override {}
    std::string getName() const override { return "Resting"; }
};

#endif // _ANIMAL_STATE_H_