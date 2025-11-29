/****************************************************************************
 * 
 *   使用状态模式重构后的新增的AnimalState.h
 * 
 ****************************************************************************/
#ifndef _ANIMAL_H_
#define _ANIMAL_H_

#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "AnimationStrategy.h"
USING_NS_CC;

class AnimalState;

class Animal : public Sprite {
protected:
    Vec2 targetPosition; 
    Rect Bounds; 
    float speed;
    std::string animPrefix;

    std::unique_ptr<AnimalState> currentState;
    std::unique_ptr<AnimationStrategy> currentAnimation;

public:
    Animal();
    virtual ~Animal();
    static Animal* create(const std::string& filename);
    virtual bool init(const std::string& filename) = 0;

    void generateNewTarget();
    void update(float delta);
    
    // 状态与行为动画控制
    void changeState(std::unique_ptr<AnimalState> newState);
    void setAnimationStrategy(AnimationStrategy* strategy);
    
    // 获取方法
    Vec2 getTargetPosition() const { return targetPosition; }
    void setTargetPosition(const Vec2& pos) { targetPosition = pos; }
    float getSpeed() const { return speed; }
    const std::string& getAnimPrefix() const { return animPrefix; }
    const Rect& getBounds() const { return Bounds; }
};

class Sheep :public Animal
{
public:
    static Sheep* create(const std::string& filename);
    Sheep();
    bool init(const std::string& filename)override;
};

class Cow :public Animal {
public:
    static Cow* create(const std::string& filename);
    Cow() {};
    bool init(const std::string& filename)override;
};

class Parrot :public Animal {
public:
    static Parrot* create(const std::string& filename);
    Parrot();
    bool init(const std::string& filename)override;
};




// 动物创建工厂
class AnimalFactory {
public:
    static Animal* createAnimal(const std::string& filename);
};

#endif // !_ANIMAL_H_
