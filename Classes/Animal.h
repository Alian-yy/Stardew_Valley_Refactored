/****************************************************************************
 * 
 * Refactored with Factory Method, Strategy and State design patterns.
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
    
    void changeState(std::unique_ptr<AnimalState> newState);
    void setAnimationStrategy(std::unique_ptr<AnimationStrategy> strategy);
    
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


// ====================Factory Pattern: add AnimalFactory====================

class AnimalFactory {
public:
    virtual ~AnimalFactory() = default;
    virtual Animal* createAnimal(const std::string& filename) = 0;
};

// Concrete factory class: Sheep Factory
class SheepFactory : public AnimalFactory {
public:
    Animal* createAnimal(const std::string& filename) override;
};

// Concrete factory class: Cow Factory
class CowFactory : public AnimalFactory {
public:
    Animal* createAnimal(const std::string& filename) override;
};

// Concrete factory class: Parrot Factory
class ParrotFactory : public AnimalFactory {
public:
    Animal* createAnimal(const std::string& filename) override;
};

// Factory manager class
class AnimalFactoryManager {
private:
    static std::unordered_map<std::string, std::unique_ptr<AnimalFactory>> factories;

public:
    static void registerFactory(const std::string& animalType, std::unique_ptr<AnimalFactory> factory);
    static Animal* createAnimal(const std::string& animalType, const std::string& filename);
    static void initializeFactories();
};

#endif // !_ANIMAL_H_


