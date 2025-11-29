/****************************************************************************
 *
 * ʹ�ù���ģʽ�ع���Ĵ���
 *
 ****************************************************************************/
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "Animal.h"

USING_NS_CC;

Animal::Animal(){
    targetPosition=Vec2(2400,700); // Ŀ���
    Bounds = Rect(2000, 790, 600, 300);
    speed=1.0f;
}

Animal* Animal::create(const std::string& filename) {
    return nullptr;
}
void Animal::generateNewTarget() {
    // �ڵ�ͼ��Χ���������Ŀ���
    float x = CCRANDOM_0_1() * Bounds.size.width + Bounds.origin.x;
    float y = CCRANDOM_0_1() * Bounds.size.height + Bounds.origin.y;
    targetPosition = Vec2(x, y);
}

/// ==================================
///  ʹ����Ϊģʽ�Ͳ���ģʽ�ع���Ĵ���
///  1.����update,changeStat,setAnimationStrategy
///  2.�޸Ķ���create����
/// ==================================

void Animal::update(float delta) {
    if (currentState) {
        currentState->update(this, delta);
    }
}

// ==================== ״̬ģʽ������changeState ====================
void Animal::changeState(std::unique_ptr<AnimalState> newState) {
    if (currentState) {
        currentState->exit(this);
    }
    currentState = std::move(newState);
    if (currentState) {
        currentState->enter(this);
    }
}

// ==================== ����ģʽ������setAnimationStrategy ====================
void Animal::setAnimationStrategy(AnimationStrategy* strategy) {
    currentAnimation.reset(strategy);
    if (strategy && this->isRunning()) {
        strategy->applyAnimation(this);
    }
}

// ==================== ���� ====================
Sheep* Sheep::create(const std::string& filename) {
    auto animal = new (std::nothrow) Sheep();
    if (animal && animal->init(filename)) {
        animal->autorelease();
        return animal;
    }
    CC_SAFE_DELETE(animal);
    return nullptr;
}

Sheep::Sheep() {
    speed = 1.0f;
    Bounds = Rect(2000, 790, 600, 300);
}

bool Sheep::init(const std::string& filename){
   if (!Sprite::initWithFile(filename)) {
        CCLOG("Error: Failed to load Sheep image: %s", filename.c_str());
        return false;
    }
    animPrefix = "animal/Sheep";
    changeState(std::make_unique<WanderingState>());
    this->scheduleUpdate();
    return true;
}

// ==================== ţ ====================
Cow* Cow::create(const std::string& filename) {
    auto animal = new (std::nothrow) Cow();
    if (animal && animal->init(filename)) {
        animal->autorelease();
        return animal;
    }
    CC_SAFE_DELETE(animal);
    return nullptr;
}

Cow::Cow() {
    speed = 0.8f;
    Bounds = Rect(2000, 790, 600, 300);
}

bool Cow::init(const std::string& filename) {
    if (!Sprite::initWithFile(filename)) {
        CCLOG("Error: Failed to load Cow image: %s", filename.c_str());
        return false;
    }
    animPrefix = "animal/Cow";
    changeState(std::make_unique<WanderingState>());
    this->scheduleUpdate();
    return true;
}

// ==================== ���� ====================
Parrot* Parrot::create(const std::string& filename) {
    auto animal = new (std::nothrow) Parrot();
    if (animal && animal->init(filename)) {
        animal->autorelease();
        return animal;
    }
    CC_SAFE_DELETE(animal);
    return nullptr;
}

Parrot::Parrot() {
    speed=3;
    Bounds = Rect(2000, 790, 1000, 1000);

};

bool Parrot::init(const std::string& filename) {
     if (!Sprite::initWithFile(filename)) {
        CCLOG("Error: Failed to load Parrot image: %s", filename.c_str());
        return false;
    }
    animPrefix = "animal/Parrot";
    changeState(std::make_unique<WanderingState>());
    this->scheduleUpdate();
    return true;
}

// ==================== ����ģʽ ====================
Animal* AnimalFactory::createAnimal(const std::string& filename)
{
    std::string lower = filename;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (lower.find("sheep") != std::string::npos) {
        return Sheep::create(filename);
    }
    else if (lower.find("cow") != std::string::npos) {
        return Cow::create(filename);
    }
    else if (lower.find("parrot") != std::string::npos) {
        return Parrot::create(filename);
    }

    CCLOG("SimpleAnimalFactory: Unknown animal type for file: %s", filename.c_str());
    return nullptr;
}
