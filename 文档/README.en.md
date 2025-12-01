# Stardew Valley Project Documentation

###### **Directory:** 

- [Project Overview](#project-overview)  
  - [Project Background](#project-background)  
  - [Project Introduction](#project-introduction)  
  - [Main Functions of the Project](#main-functions-of-the-project)  
- [Preliminary Refactoring](#preliminary-refactoring)  
- [Refactoring Using Design Patterns](#refactoring-using-design-patterns)  
  - [Refactoring with Creational Patterns](#refactoring-with-creational-patterns)  
  - [Refactoring with Structural Patterns](#refactoring-with-structural-patterns)  
  - [Refactoring with Behavioral Patterns](#refactoring-with-behavioral-patterns)  
  - [Refactoring with Design Patterns Not Covered in the Course](#refactoring-with-design-patterns-not-covered-in-the-course)  
- [Explanation of AI Tool Usage](#explanation-of-ai-tool-usage)  
  - [Exploration and Selection of Design Patterns](#exploration-and-selection-of-design-patterns)  
  - [Refactoring and Generation of Specific Code](#refactoring-and-generation-of-specific-code)  
  - [Reflection and Discussion](#reflection-and-discussion)  
- [The Value Proposition of Refactoring: A Design Patterns Perspective](#the-value-proposition-of-refactoring-a-design-patterns-perspective)  
- [Summary](#summary)


##### **Project Name**: Stardew Valley ( 2024 Tongji University Programming Paradigms Course Project )
##### **Team Number**: Group 15

##### **Team Members**:

|name|Student number|Contact information|Email|
| --- | ------- | ----------- | --------------------- |
|Mu Yingxue|2351758|13163530936|a05100936@163.com|
|Yu Elian|2352993|18168165803|2352993@tongji.edu.cn|
|Zhang Shikou|2353240|18980433878|2987991635@qq.com|
|Wang Yixin|2353733|18966812958|807576942@qq.com|
|Lin Qingying|2354356|15259577899|2354356@tongji.edu.cn|

## **Project overview**

### Project Background

In recent years, as the pace of life accelerates and digital pressure increases, more and more players tend to choose "slow games" with a soothing rhythm and healing graphics to relax their body and mind. Farm simulation games represented by "Stardew Valley" have become a phenomenon-level work in the field of independent games due to their high degree of freedom, rich gameplay, and delicate emotions. This type of game not only integrates various elements such as planting, breeding, construction, social interaction, and exploration, but also builds a vibrant virtual rural world through mechanisms such as the change of seasons, day and night cycles, and daily behaviors of NPCs, allowing players to gain a sense of accomplishment and emotional resonance through cultivation and companionship.

In this context, the project implements a 2D simulation game with complete farm ecology, character interaction and scene switching functions, placing players in a pixel-style rural world full of vitality and warmth. They can feel the passage of time during sowing and harvesting, and experience the warmth of human kindness in interactions with villagers, truly realizing the game vision of "escaping the city and returning to the countryside".

### Project Introduction

This project is a 2D farm simulation game developed based on the Cocos2d-x 3.17.2 engine, inspired by the classic independent game "Stardew Valley". The game is presented in a pixel style. Players play the role of a protagonist who comes to live in the countryside and start a new pastoral life on a land to be cultivated.

The game contains multiple explorable areas and supports seamless scene switching and character position memory; NPCs have basic AI behaviors and can move within a limited range and trigger conversations with players; at the same time, auxiliary function modules such as a backpack system, check-in interface, and fishing mini-games are designed to enhance the richness of the game. At the audio-visual level, the project integrates background music, environmental sound effects, UI animations and weather effects to create an immersive rural atmosphere.

On the basis of faithfully restoring the classic farm simulation gameplay, this project incorporates a number of innovations and enhanced functions to create a rural life experience that is both interesting and immersive. Key features include:

- **Immersive farm management system**: Completely realize the full cycle management of crops from sowing, watering, growing to harvesting, combining day and night changes and weather changes to create a real farming rhythm.
- **Interactive NPCs and plot triggers**: Villagers and animals have basic AI behaviors, and conversations can be triggered when players approach them. The tasks and favorability system can be expanded in the future.
- **Multifunctional backpack and item management**: Design a multi-tab backpack interface that supports dragging, classifying, and using items to improve resource management efficiency.
- **Seamless switching between multiple scenes**: Through the scene state manager, realize smooth jumps between farms, houses, lakes and other areas, and automatically save and restore player positions.
- **Rich leisure gameplay**: Integrate lightweight modules such as daily check-in, fishing mini-games, and animal interactions to increase the diversity and fun of daily play.
- **Warm audio-visual experience**: Combined with soothing background music, dynamic environmental particles and smooth UI animations, you can build a healing pixel-style world.

These features together form a free, warm and vibrant virtual pastoral, allowing players to feel the charm of slow life while cultivating and exploring.
### Main Functions of the Project
1. **Menu system**:
* Game entrance and navigation, responsible for game startup, navigation and basic settings. It provides a user-friendly interface that allows players to easily access various functional modules of the game. The menu system includes multiple submenus such as main menu, settings menu, and about menu.
2. **farm scene**:
* The main game area, the scene contains a complete farm environment, containing various game objects such as terrain, buildings, crops, animals, etc., and supports multi-layer maps and collision detection.
3. **role system**:
* Players can interact with the game world by controlling characters. The character system includes character attributes, character actions, character status and other aspects. Characters will level up as the game progresses.
4. **animal system**:
* Animal system manages various animals on the farm, each animal has some basic attributes.
5. **planting system**:
* This system simulates the real agricultural process, including planting, growing, harvesting and other stages. Crops will grow over time in the game, and players will need to take care of them to ensure they grow properly.
6. **time system**:
* The game has its own time system, which is different from real-world time. The speed at which game time passes is configurable and is often much faster than real-life time. The time system includes multiple time units such as minutes, hours, days, seasons, etc.
7. **scene system**:
* The game is not played in a single big scene, but consists of multiple different scenes. Each scene has its own map, objects, logic, etc. The scene system is responsible for switching between scenes, resource loading and unloading, etc.
8. **audio system**:
* The audio system provides functions such as play, pause, stop, and volume adjustment. Different scenes and events in the game have corresponding audio, and the audio system is responsible for playing these audios at the appropriate time. Various events and operations in the game produce different sound effects.

## **Preliminary Refactoring**
#### Original Problem
A preliminary review of the projects we wrote last year found that some files were very large and took on too many responsibilities, making the code highly coupled and difficult to maintain. For example `ouside.cpp` file, this file also manages UI display (various menus, buttons, dialog boxes), player input (keyboard events), NPC logic, scene entities (animals, crops), game logic (fishing), etc. We first need to split and encapsulate the components of the code in these files to facilitate our subsequent reconstruction.
#### Necessity of Refactoring
1.**High maintenance costs and “fragility”** 
- **Move one hair and move the whole body**: Assume that the NPC dialogue triggering distance needs to be modified. This logic is buried in `init()` in a huge lambda expression in the function. When modifying, it is very likely that the logic of the unrelated sign-in button next to it is unintentionally destroyed, or the calculation of viewport following is affected.
- **Difficulty understanding**: Facing a question with thousands of lines `outside.cpp`, it is difficult for people who do not understand this project to quickly understand the full picture of the system. This greatly increases the time to get started and the chance of making mistakes. Therefore, we need to carry out preliminary reconstruction so that teammates who did not know this project before can get started faster.
2.**Seriously hinders team collaboration** 
- **merge conflicts**: In team development, each of us has a different division of labor. If all responsibilities are `outside.cpp` file type implementation, all team members work on `outside.cpp` on this huge file, version control merge conflicts will occur frequently, and resolving conflicts will be very painful.
- **Unclear responsibilities**: Unable to clearly assign tasks. The division of labor like "you are responsible for the game logic and I am responsible for the UI" cannot be realized under the current architecture because the logic and UI are deeply coupled.
Therefore, we first need to split and encapsulate the components of the code in these files, which not only improves the code quality, but also facilitates our subsequent cooperation in reconstructing the code.
#### Proposed Solution
We systematically split and encapsulated the highly coupled and mixed-responsibility logic in the original scene class, and rebuilt it into the following independent functional modules with single responsibilities:
1. **Enter the management module (`InputManager`)** 
- Change keyboard event handling from `outside` separation within class
- Specially handles the logic of E key triggering UI switching
- Provides a unified enable/disable interface
```cpp
class InputManager {
public:
InputManager(cocos2d::Node* owner);
void enable();
void disable();
private:
void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
cocos2d::Node* _owner;
};
```

2. **UI management module (`UIManager`)** 
- Extract all UI related functions: personal interface, fishing interface, NPC dialog box
- Realize `Observer` the interface receives time update events
- Unified management of UI status and life cycle
```cpp
classUIManager {
public:
UIManager(cocos2d::Layer* parent);
void showPersonalInterface(const cocos2d::Vec2& position);
void hidePersonalInterface();
void showDialog(const std::string& imagePath, const cocos2d::Vec2& pos, float durationSec = 3.0f);
void onMinuteChanged(const std::string& timeStr);
private:
cocos2d::Layer* _parent;
cocos2d::Layer* _personalLayer = nullptr;
};
```

3. **NPC management module (`NPCManager`)** 
- Encapsulates NPC creation and interaction logic
- Use `NPCSpec` structure configuration NPC parameters
- Handling distance detection and dialogue triggering
```cpp
class NPCManager {
public:
NPCManager(cocos2d::Layer* parent);
void spawnNPC(const std::string& spritePath, const cocos2d::Vec2& pos);
void update(float dt);
private:
cocos2d::Layer* _parent;
std::vector<cocos2d::Node*> _npcs;
};
```

4. **time release system (`TimePublisher`)** 
- Separate time calculation logic
- Publish time change events periodically
- Other modules subscribe to updates through the observer pattern
```cpp
class TimeManager {
public:
static TimeManager* getInstance();
void start();
void stop();
void update(float dt);
void setGameStartTime(std::chrono::high_resolution_clock::time_point t);
private:
TimeManager() = default;
std::chrono::high_resolution_clock::time_point gameStartTime;
bool running = false;
};
```
5. **Entity Management Module (`EntityManager`)**:
- Responsible for the creation of animals, crops, NPCs, players and other entities
- responsible `update` scheduling (responsible for `spawn`, unified `update` remove)
```cpp
class EntityManager {
public:
EntityManager(cocos2d::Layer* parent);
void spawnSheep(int count);
void spawnCow();
void spawnParrot();
void update(float dt);
private:
cocos2d::Layer* _parent;
std::vector<cocos2d::Sprite*> _entities;
};
```
## Refactoring with Design Patterns

### Refactoring Using Creational Patterns

### Refactoring the Character Animation System Using the Builder Pattern
#### Original Problem

1. **Frequent creation/destruction causes performance jitters** 

* Tool animation (with axe, pickaxe) every time it is called `Sprite::create()` → Play → `removeFromParent()`.

```cpp
void CharacterWithTools::usetools(const std::string& filename)
{
auto tool = Sprite::create(filename);
if (tool == nullptr) {
CCLOG("Error: Failed to create axe sprite!");
return;
}

//Set the relative position of the tool
Vec2 relative_position(50, 20);
tool->setPosition(relative_position);


tool->setAnchorPoint(Vec2(0, 0));//Set the anchor point to the lower left corner


//Add the ax as a child node of the character
this->addChild(tool);

tool->runAction(Sequence::create(
RotateBy::create(0.3f, 90), // Rotate -90°
RotateBy::create(0.3f, -90), //Restore rotation to 90°
DelayTime::create(0.1f),
delayTime::create(0.1f), CallFunc::create([tool]() { tool->removeFromParent(); }),
nullptr ));
}
```
* Crops are recreated after being planted/harvested, resulting in frequent allocations and releases.

2. **Status residual problems occur frequently** 

When different objects (tools, crops) are reused, if they are not reset correctly:

* Texture is still the same as last time.
* Action is not stopped.
* The scheduler (scheduleUpdate) is still running.
* Visible, Scale, Rotation may be in old status.

3. **High maintenance costs** 

Creation, destruction, and initialization logic are scattered in many places in the code:

* `Sprite::create()` 
* `removeFromParent()` 
* `stopAllActions()` 
* `setVisible(false)` 
* `unscheduleUpdate()` 

Developers tend to forget certain steps, leading to reuse errors.

#### Necessity of Refactoring
This reconstruction also covers the animation system's problems of repeated creation methods, complex initialization, hard-coded attributes, and weak scalability. The generator mode can be used to uniformly encapsulate animation construction logic and avoid repeated creation processes. Only prefix (path), frames (frame range), and delay (speed) need to be specified, and chain calls can improve code readability and facilitate expansion.

#### UML Class Diagram
<p align="center">
<img src="diagram/CharacterWithTools.svg" alt="Presentation Layer" style="width:80%; max-width:1200px; height:auto;"/>
</p>

#### Refactoring Steps

1. **Add AnimationBuilder class** ：
```cpp
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
for (int i = s; i <= e; i++) {
anim->addSpriteFrameWithFile(prefix + std::to_string(i) +".png");
}
anim->setDelayPerUnit(delayUnit);
anim->setLoops(-1);
return anim;
}
};
```
2. **Use Builder in the character class to build animations** 
* All direction animation creation logic is unified and chain calls are clear.
```cpp
walkLeftAnimation = AnimationBuilder()
.from("character/Danaleft")
.frames(1, 3)
.delay(0.1f)
.build();
walkLeftAnimate = Animate::create(walkLeftAnimation);
walkLeftAnimate->retain();
```  

#### Improvements and Benefits
Use the generator pattern to reconstruct the animation creation part, effectively solving the problems of duplicate code, poor scalability, and insufficient flexibility; the animation creation logic is decoupled from the character logic, and maintenance and expansion costs are significantly reduced.
1. **avoid duplication**: The improved animation logic is encapsulated in `Builder`, avoid duplicating animation creation code.
2. **Logical decoupling**: Animation construction is divided into independent classes, with clear responsibilities and decoupling from role logic.
3. **Easy maintenance**: To modify any animation resource, just change the corresponding `Builder` class and call it.
4. **Very low cost of expansion**: Adding a new animation only takes one line `Builder` call.

<br></br>
---

### Reconstructing animal and crop systems using the factory model

#### Original question
1. **Inconsistent interfaces and scattered initialization methods** 
* animals (`Sheep`,`Cow`,`Parrot` etc.) and crops (`Wheat`,`Corn`,`Tomato` etc.) have similar problems:

```cpp
static Sheep* create(const std::string& filename);
bool Sheep::init(const std::string& filename);

static Crop* create(const std::string& filename);
bool Crop::init(const std::string& filename);
```
Question:

* Each subclass must implement it by itself `create()` and `init()` 
* The initialization process is scattered in different categories, violating the "opening and closing principle" 

2. **Object creation mixed with business logic** 

The logic of animal creation and initialization (such as setting speed, boundary, animation prefix) is not separated, and too many creation details need to be paid attention to in the business code.

The creation process of different animals is repeated. For example, the memory allocation, initialization call, automatic release pool management and other steps in the create method are the same but written repeatedly.

3. **Poor scalability and high maintenance costs** 

When adding a new animal type, you need to modify multiple codes for creation and calling at the same time, which is easy to miss and increases the risk of errors.
* Add class
* write new `init` 
* write new `create` 
* Manually called in business logic `Sheep::create()` or `Wheat::create()` 


The animal creation process cannot be managed uniformly. If you need to make global adjustments to the creation logic (such as adding logs and cache), you need to modify the create method of each animal class one by one.

#### Necessity of refactoring 
* If no reconstruction is carried out, the system will face a series of serious problems in the long term:`create`/`init` the logic needs to be written repeatedly in dozens of places, making the code redundant and difficult to maintain. Whenever a new animal or crop type is added, multiple codes must be modified at the same time, resulting in a high degree of coupling and greatly increasing the risk of errors. More importantly, the current architecture cannot support data-driven design, so the expansion of animal and crop systems must rely on hard coding, which greatly increases the cost of subsequent functional iterations.

* Therefore, the factory pattern is used to abstract and encapsulate the animal creation logic, create objects through a unified factory interface, and isolate the dependencies of specific classes. When adding new animal types, you only need to extend the factory class without modifying the original code. At the same time, the creation process is unified and managed to reduce maintenance costs.

#### UML class diagram
<p align="center">
<img src="diagram/Factory.svg" alt="Presentation Layer" style="width:100%; max-width:1200px; height:auto;"/>
</p>


#### Refactoring steps

1. **Define abstract factory and concrete factory class** 

```cpp
 class AnimalFactory {
    public:
    virtual ~AnimalFactory() = default;
    virtual Animal* createAnimal(const std::string& filename) = 0;
 };

  class SheepFactory : public AnimalFactory {
    public:
    Animal* createAnimal(const std::string& filename) override;
 };
……
 ```
2. **Implement unified management and creation of factory manager** 

```cpp
class AnimalFactoryManager {
private:
static std::unordered_map<std::string, std::unique_ptr<AnimalFactory>> factories;
public:
static void registerFactory(const std::string& animalType, std::unique_ptr<AnimalFactory> factory);
static Animal* createAnimal(const std::string& animalType, const std::string& filename);
static void initializeFactories();
};
```
3. **Create animals through factory manager in business code** 
```cpp
 AnimalFactoryManager::initializeFactories();
 Animal* sheep = AnimalFactoryManager::createAnimal("sheep", "sheep.png");
……
```
#### Improvements and Benefits

After using the factory pattern to reconstruct the animal creation system, the abstraction of creation logic and the decoupling of business code have been achieved. Specific improvements are reflected in the following aspects:

1. **Decoupled creation**: By introducing the factory interface, the business code no longer directly depends on the specific animal class, but is programmed towards the abstract interface AnimalFactory and Animal, which reduces the code coupling.

2. **Easy to expand**: When you need to add new animals, you only need to implement the corresponding specific factory class and register it in the factory manager. There is no need to modify the existing creation logic. It complies with the "opening and closing principle" and improves the scalability of the system.

3. **Centralized management**: Encapsulate repetitively created codes that were originally scattered everywhere into factory classes, and let the factory manager centrally manage all factories, which improves code reusability and cohesion.

4. **global control**: Unified logic such as logging, object caching, and permission verification can be easily added to the factory class or factory manager to facilitate centralized management and control of the creation process.

Through the above improvements, the system effectively solves the coupling problem in the object creation process, significantly improves maintainability and flexibility, and reduces the cost and risk of subsequent maintenance.


## Refactor using structural patterns
### Refactoring the scene manager using appearance mode
#### Original question
1. **Scene switching logic is scattered** 
* Scene creation and switching logic is scattered in multiple files, and each scene class needs to be called directly `Director` and create other scenarios that result in code duplication and difficulty to maintain:

```cpp
// AppDelegate.cpp 
bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
        glview = GLViewImpl::create("Valley Game");
        director->setOpenGLView(glview);
    }
    
    register_all_packages();
    
    auto scene = valleybegin::createvalleybeginScene();
    director->runWithScene(scene);
    
    return true;
}
```
```cpp
// valleybegin.cpp 
void valleybegin::Startgame(Ref* obj) {
    // 直接依赖 menu 类和 Director
    Scene* scene = menu::createmenuScene();
    Director::getInstance()->replaceScene(
        TransitionCrossFade::create(0.5, scene)
    );
    timerunning = true;
}
```
```cpp
// menu.cpp 
void menu::onMapRadioButtonSelected(RadioButton* radioButton, int index) {
    selectedMapIndex = index;
    log("Selected Map Index: %d", selectedMapIndex);
    
    auto newScene = outside::createSceneWithMapIndex(selectedMapIndex);
    Director::getInstance()->replaceScene(newScene);
}
```
```cpp
// outside.cpp 
void outside::loadMapBackground(int mapIndex) {
    
    ...

    if (characterPosition.x >= 3460 && characterPosition.x <= 3500 &&
        characterPosition.y >= 3570 && characterPosition.y <= 3610) {
        Scene* scene = intovalley::createintovalleyScene();
        Director::getInstance()->pushScene(scene);
        inZones["zone1"] = true;
    }
    
    if (characterPosition.x >= 3000 && characterPosition.x <= 3060 &&
        characterPosition.y >= 4740 && characterPosition.y <= 4770) {
        Scene* scene = othersence::createothersenceScene();
        Director::getInstance()->pushScene(scene);
        inZones["zone2"] = true;
    }
}
```
```cpp
// intovalley.cpp 
void intovalley::init() {
    ... 
    
    button->addClickEventListener([&](Ref* sender) {
        Director::getInstance()->popScene();
    });
}
```
```cpp
// othersence.cpp
void othersence::init() {
    ... 
    
    button->addClickEventListener([&](Ref* sender) {
        Director::getInstance()->popScene();
    });
}
```

2. **Tightly coupled design** 
Each scene class directly depends on `cocos2d::Director` and other scene classes, forming a complex dependency network. Scene classes depend on each other, and modifying one scene class may affect multiple other classes.

3. **Violation of the Single Responsibility Principle** 
The scene class must not only handle its own business logic (such as character movement, NPC interaction), but also be responsible for the infrastructure logic of scene switching (calling Director, creating other scenes), and its responsibilities are confusing.

4. **Difficult to test and maintain** 
The scene switching logic is tightly coupled with the Director singleton, making it difficult to unit test. Modifying scene switching logic requires modifications in multiple files, which results in high maintenance costs.

5. **Code duplication** 
Same Director calling pattern (`runWithScene`,`replaceScene`,`pushScene`,`popScene`) appears repeatedly in multiple files, violating the DRY principle.

#### Necessity of Refactoring

* Without reconstruction, the system will face the following problems: scene switching logic is scattered in 6 different files, and each modification needs to be updated synchronously in multiple places, which is easy to miss and introduce inconsistencies; each scene class directly depends on Director and other scene classes, forming a highly coupled dependency network, and changes to any scene class may affect other classes; as the number of scenes increases, this scattered switching logic will make the code more and more difficult to maintain, violating the opening and closing principle.
* Therefore, use the appearance pattern to centralize scene management logic into `GameSceneFacade` in the class, a unified interface is provided to manage the creation and switching of all scenes, hiding the complexity of interaction with Director, reducing the coupling between scene classes, and making the system easier to maintain and expand.

#### UML class diagram
<p align="center">
<img src="diagram/Facade.svg" alt="Facade Pattern UML" style="width:100%; max-width:1200px; height:auto;"/>
</p>

#### Refactoring steps

1. **Create GameSceneFacade appearance class**:

* Define a unified scene management interface to encapsulate all scene switching logic:

```cpp
class GameSceneFacade {
public:
// Launch the game and run the opening scene
static void runWithBeginScene();

// Switch from the opening scene to the menu scene (with transition animation)
static void showMenuScene();

// Enter the farm scene from the menu scene
static void enterFarmScene(int mapIndex);

// Enter the house scene from the farm scene
static void enterHouseScene();

// Enter other area scenes from the farm scene
static void enterOtherAreaScene();

// Return from a sub-scene to the previous scene
static void returnToPreviousScene();
};
```

2. **Implement the GameSceneFacade method**:

* in `GameSceneFacade.cpp` implement all methods in and uniformly encapsulate calls to Director:

```cpp
void GameSceneFacade::runWithBeginScene() {
    auto scene = valleybegin::createvalleybeginScene();
    Director::getInstance()->runWithScene(scene);
}

void GameSceneFacade::showMenuScene() {
    Scene* scene = menu::createmenuScene();
    Director::getInstance()->replaceScene(
        TransitionCrossFade::create(0.5, scene)
    );
}

void GameSceneFacade::enterFarmScene(int mapIndex) {
    auto newScene = outside::createSceneWithMapIndex(mapIndex);
    Director::getInstance()->replaceScene(newScene);
}

void GameSceneFacade::enterHouseScene() {
    Scene* scene = intovalley::createintovalleyScene();
    Director::getInstance()->pushScene(scene);
}

void GameSceneFacade::enterOtherAreaScene() {
    Scene* scene = othersence::createothersenceScene();
    Director::getInstance()->pushScene(scene);
}

void GameSceneFacade::returnToPreviousScene() {
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->popScene();
    }
}
```

3. **Refactor all scene switch calls**:

* Will all direct calls `Director` and replace the code that creates the scene with `GameSceneFacade` the call:

```cpp
// AppDelegate.cpp - Before Refactoring
auto scene = valleybegin::createvalleybeginScene();
director->runWithScene(scene);

// AppDelegate.cpp - After Refactoring
GameSceneFacade::runWithBeginScene();

// valleybegin.cpp - After Refactoring
void valleybegin::Startgame(Ref* obj) {
    GameSceneFacade::showMenuScene();
}

// menu.cpp - After Refactoring
void menu::onMapRadioButtonSelected(...) {
    GameSceneFacade::enterFarmScene(selectedMapIndex);
}

// outside.cpp - After Refactoring
if (!inZones["zone1"]) {
    GameSceneFacade::enterHouseScene();
    inZones["zone1"] = true;
}
```

#### Improvements and Benefits
After refactoring the scene management using the appearance pattern, the system has achieved significant improvements in structural clarity, maintainability and testability:
* The scene switching logic was originally scattered in six different files, making modification and tracking difficult; after reconstruction, all switching logic was unified into `GameSceneFacade` in the class, centralized management is implemented.
* Before reconstruction, each scene class directly depends on `Director` and the specific implementations of each other, forming a complex network of dependencies; now, the scene class only needs to depend on `GameSceneFacade` this high-level interface greatly reduces the coupling between modules.
* Originally, each scene class had to handle its own business logic, and was also responsible for infrastructure operations such as loading, unloading, and transition. The responsibilities were unclear; by handing over these common processes to `GameSceneFacade` unified processing allows scene classes to focus on core business logic and comply with the single responsibility principle.
* Due to the highly dispersed logic and tight coupling, it is difficult to write effective unit tests under the old architecture; now the scenario switching path is clear and well-encapsulated, and test cases can be targeted `GameSceneFacade` accurately covers various switching scenarios, significantly improving testability and maintainability.
*Recurring in multiple scenes `Director` calling code (such as `pushScene`,`popScene`,`replaceScene`) has been abstracted and encapsulated into `Facade` internally, not only is redundancy eliminated, but the calling behavior is ensured to be consistent and safe.

**Core advantages:** 
1. **Reduce coupling**:
* Before refactoring: 6 files directly depended on Director
* After refactoring: Only 1 file (GameSceneFacade) depends on Director
* Reduced Director dependencies by 83%

2. **Centralized management**:
*All scene transition logic is managed in one place
*The complete game flow is clearly visible in GameSceneFacade
*Scene flow is easier to understand and modify

3. **Improved Maintainability**:
* Adding a new scene only requires adding a method in GameSceneFacade
* Modifying scene transition logic only requires changing one file
* Other scene classes remain unaffected

4. **Clear Separation of Responsibilities**:
* Scene classes: Focus on "when" to switch (game rules)
* GameSceneFacade: Focuses on "how" to switch (Director calls)
* Adheres to the Single Responsibility Principle

5. **Easier Testing**:
* Scene transitions can be tested through the Facade interface
* GameSceneFacade can be mocked for testing
* Centralized logic is easier to test

6. **Support for Future Enhancements**:
* The Facade can be extended to log scene transitions
* Analytics and tracking can be added
* A state machine pattern can be introduced
* Command pattern support (undo/redo) can be implemented



Effectively solves the problems of scene management logic being dispersed, highly coupled, and difficult to maintain; scene switching logic is decoupled from business logic, and maintenance and expansion costs are significantly reduced.

---
### Refactoring the Scene Manager Using the Adapter Pattern
#### Original Problem
1. **Interface is inconsistent**:
* The upper-layer caller cannot rely on a unified interface and can only call specific classes one by one, resulting in redundant calling code and difficulty in maintaining. As the number of scenarios increases, this inconsistency will result in a large number of repeated judgments and branching logic, making the creation process more confusing.
```cpp
// The creation method interfaces in different scenarios are not unified.
valleybegin::createvalleybeginScene() // no parameters
menu::createmenuScene()                      
outside::createSceneWithMapIndex(int) // Parameters required
intovalley::createintovalleyScene() // no parameters
othersence::createothersenceScene() // no parameters
```

2. **High coupling**:
* `GameSceneFacade` directly related to all specific scene classes, forming strong coupling. Any change to the scene class (file name, method name, construction parameters) will force `GameSceneFacade` recompile. This structure does not comply with the opening and closing principle.
```cpp
// GameSceneFacade.h directly depends on all scene classes
#include "valleybegin.h" 
#include "menu.h" 
#include "outside.h" 
#include "intovalley.h" 
#include "othersence.h" 
```
3. **Difficult to scale**:
* Adding new scenes requires modification `GameSceneFacade`, violating the principle of "open for extension, closed for modification".
* The scene creation logic is scattered. As the number of scenes increases, the branch judgment (if/else or switch) on the calling side will become larger and larger, and the maintenance cost will increase exponentially.
* Unable to add unified pre-processing for scene creation (such as resource preloading, parameter verification, etc.)

#### UML Class Diagram
<p align="center">
<img src="diagram/SceneAdapter.svg" alt="Presentation Layer" style="width:100%; max-width:1200px; height:auto;"/>
</p>

#### Refactoring Steps

1. **Define unified interface**:
In order for all game scenarios to pass **unified interface** to create, we define `ISceneCreator` serves as an abstract base class for scene building.
```cpp
class ISceneCreator {
public:
virtual ~ISceneCreator() = default;
virtual Scene* createScene(const cocos2d::ValueMap& params) = 0;
virtual std::string getSceneType() const = 0;
virtual void preloadResources() {}
virtual bool canCreateScene(const cocos2d::ValueMap& params) const {
return true;
}
};
```
- `createScene()`: Responsible for creating specific scene instances and supporting `params` parameters.
- `getSceneType()`: Returns the scene type string, such as `"Farm"`/`"Shop"`.
- `preloadResources()`: Scene resource preloading interface, optional implementation.
- `canCreateScene()`: Used to verify parameters before creating a scene to improve robustness.
2. **Create specific adapter**:
Adapters are used to bridge the game logic layer and specific scene classes, shielding the creation differences of different scenes.
```cpp
//Farm scene adapter
class FarmSceneAdapter : public ISceneCreator {
public:
Scene* createScene(const cocos2d::ValueMap& params) override {
int mapIndex = 0;
if (params.find("mapIndex") != params.end()) {
mapIndex = params.at("mapIndex").asInt();
}
return outside::createSceneWithMapIndex(mapIndex);
}
...
};
```
3. **adapter manager**:
The manager centrally saves and schedules all scene adapters
```cpp
class SceneAdapterManager {
private:
std::map<std::string, ISceneCreator*> adapters;
public:
static SceneAdapterManager* getInstance();
void registerAdapter(const std::string& sceneType, ISceneCreator* adapter);
Scene* createScene(const std::string& sceneType, const cocos2d::ValueMap& params = cocos2d::ValueMap());
};
```
- `registerAdapter()` all scenarios are registered uniformly during the project initialization phase.
- `createScene()` will automatically find the adapter of the corresponding type and call it `createScene()`.
4. **Create a farm scene**:
```cpp
//Use adapter to unify interface
ValueMap params;
params["mapIndex"] = Value(2);
Scene* farmScene = SceneAdapterManager::getInstance()->createScene("Farm", params);
```
5. **Add new scene**:
```cpp
// 1. Create a new scene adapter
class ShopSceneAdapter : public ISceneCreator {
public:
Scene* createScene(const ValueMap& params) override {
// Adapt to new scene creation method
return ShopScene::createShopScene();
}
std::string getSceneType() const override { return "Shop"; }
};

// 2. Register the adapter (in the SceneAdapterManager constructor)
registerAdapter("Shop", new ShopSceneAdapter());

// 3. Add a method in Facade (optional, you can also call the adapter directly)
void GameSceneFacade::enterShopScene() {
Scene* scene = getAdapterManager()->createScene("Shop");
Director::getInstance()->pushScene(scene);
}
```
6. **Scene preloading**:
```cpp
// Preload resources before entering the scene
void GameSceneFacade::enterFarmScene(int mapIndex) {
// Preload farm scene resources
getAdapterManager()->preloadSceneResources("Farm");

//Create scene
ValueMap params;
params["mapIndex"] = Value(mapIndex);
Scene* scene = getAdapterManager()->createScene("Farm", params);
// ...
}
```
#### Improvements and Benefits
1. **unified interface**:
By introducing a unified `createScene(sceneName, params)` interface, the caller no longer needs to pay attention to the construction methods, parameter differences or initialization processes of different scenes, and only needs to pass in the scene name and parameters. This kind of interface unification not only reduces the judgment logic of the business layer, but also makes the upper-layer code clearer, more intuitive, and easier to maintain.
2. **decoupling**:
 `GameSceneFacade` no longer directly relies on each specific scene class, but only relies on abstract interfaces `ISceneCreator`. This reduces the coupling between modules, making `Facade` it is no longer affected by scene class changes, and scene implementations can be added or replaced without modifying the business code. Complies with the dependency inversion principle.
3. **Easy to expand**:
Through the adapter pattern, each new scenario only needs to write a corresponding adapter and register it to take effect. without modification `GameSceneFacade`, avoiding the continuous addition of `if/else` or `switch` the redundant logic greatly reduces the cost of adding new scenarios, and also facilitates developers to introduce more scenario types in subsequent iterations, greatly improving scalability and system flexibility.
4. **Unified processing of parameters**:
Different scenarios may require different parameters. To avoid interface splitting, the parameters are uniformly encapsulated as `ValueMap`, parsed and converted internally by the adapter. This not only ensures the uniformity of external calls, but also provides flexibility for subsequent expansion, such as supporting more parameters, default value processing, parameter verification, etc.

## Refactoring Using Behavioral Patterns

### Refactoring Using the Strategy Pattern + State Pattern

#### Original Problem

1. **code duplication problem**:
 * **DRY principle violation**: The same animation creation logic is repeated 3 times.
 * **Difficult to maintain**: Animation parameters are scattered in multiple places. To modify one place, you need to change three places. It is easy to miss and introduce inconsistencies. In the end, it requires a lot of testing and verification.

```cpp
bool Sheep::init(const std::string& filename){
if (!Sprite::initWithFile(filename)) {
CCLOG("Error: Failed to load animal image: %s", filename.c_str());
return false;
}

animalmoveAnimation = Animation::create();
for (int i = 1; i <= 4; i++) {
std::string frameName ="animal/Sheep"+ std::to_string(i) +".png";
animalmoveAnimation->addSpriteFrameWithFile(frameName);
}
animalmoveAnimation->setDelayPerUnit(0.1f);
animalmoveAnimation->setLoops(-1);
animalmoveAnimate = Animate::create(animalmoveAnimation);
this->runAction(animalmoveAnimate);
this->scheduleUpdate();
return true;
}

bool Cow::init(const std::string& filename) {
if (!Sprite::initWithFile(filename)) {
CCLOG("Error: Failed to load animal image: %s", filename.c_str());
return false;
}

animalmoveAnimation = Animation::create();
for (int i = 1; i <= 4; i++) {
std::string frameName ="animal/Cow"+ std::to_string(i) +".png";
animalmoveAnimation->addSpriteFrameWithFile(frameName);
}
animalmoveAnimation->setDelayPerUnit(0.1f);
animalmoveAnimation->setLoops(-1);
animalmoveAnimate = Animate::create(animalmoveAnimation);
this->runAction(animalmoveAnimate);
this->scheduleUpdate();
return true;
}

bool Parrot::init(const std::string& filename) {
if (!Sprite::initWithFile(filename)) {
CCLOG("Error: Failed to load animal image: %s", filename.c_str());
return false;
}

animalmoveAnimation = Animation::create();
for (int i = 1; i <= 4; i++) {
std::string frameName ="animal/Parrot"+ std::to_string(i) +".png";
animalmoveAnimation->addSpriteFrameWithFile(frameName);
}
animalmoveAnimation->setDelayPerUnit(0.1f);
animalmoveAnimation->setLoops(-1);
animalmoveAnimate = Animate::create(animalmoveAnimation);
this->runAction(animalmoveAnimate);
this->scheduleUpdate();
return true;
}
```

2. **lack of behavioral abstraction**: The behavior of different objects in the system is not abstracted into interfaces or base classes, but is hard-coded in specific classes.
- **Behavior is fixed and cannot be extended**: All animals use the same movement logic, and it is impossible to customize different behaviors for different objects and implement different movement methods.
- **Difficult to test**: Behavior and data are tightly coupled. Behaviors directly access and modify data members. Behaviors and data cannot be tested independently, and behaviors cannot be reused.


```cpp
void Animal::update(float delta) {
Vec2 direction = targetPosition - this->getPosition();
this->setPosition(this->getPosition() + direction * delta * speed);

if (this->getPosition().distance(targetPosition) < 10.0f) {
generateNewTarget();
}
}
```

3. **Chaotic state management**:
- **state implicit**: There is no explicit state management in the original code, the behavior of the animal is completely determined by the update() method
- **Behavior is difficult to understand**: There is no method to obtain the status, and it is impossible to clearly understand the status of the current object. State and data are mixed together and cannot be clearly distinguished.
- **Unable to convert**: In the original code, the animal can only be in one implicit state: moving to the target. Inability to flexibly switch between different states.

```cpp
void Animal::update(float delta) {
Vec2 direction = targetPosition - this->getPosition();
this->setPosition(this->getPosition() + direction * delta * speed);

if (this->getPosition().distance(targetPosition) < 10.0f) {
generateNewTarget();
}
}
```

4. **Tightly coupled design**:
<p align="center">
<img src="diagram/Coupled p.svg" alt="Presentation Layer" style="width:70%; max-width:700px; height:auto;"/>
</p>

* Sheep, cattle, parrot subtypes `init()` function with `Sprite`,`Animation`,` Animate` class coupling, changes in one module will directly affect other modules, causing a ripple effect of modifications, making the code difficult to maintain and expand. In terms of testing, it is impossible to isolate test subcategories independently, and the test speed is slow and the test is unstable.

5. **Difficulty adding new features**:
* All animal behaviors are in a single `update()` the responsibilities included in the method are: calculating direction, updating position, checking distance, and generating new target. This is a "God method" that does too many things for the reader to understand. After adding new functions, the code will expand rapidly, and the condition judgment will be complicated, violating the "opening and closing principle".

```cpp
void Animal::update(float delta) {
Vec2 direction = targetPosition - this->getPosition();
this->setPosition(this->getPosition() + direction * delta *speed);

if (this->getPosition().distance(targetPosition) < 10.0f) {
generateNewTarget();
}
}
```

6. **Single animation and poor visual effects**:
* Each animal type has only one fixed animation, currently only the "default walking" animation. Without the ability to reflect the visual differences of different behaviors, players will not be able to intuitively perceive their behavioral intentions through the character's movements - they are still moving when resting, there is no change in speed during pursuit, and there is no sense of tension in the movements. This seriously weakens the sense of immersion and feedback clarity, causing the character's behavior to be "inconsistent" and reducing the expressiveness and credibility of the game.

#### Necessity of Refactoring
 * **Business needs driven**: Currently there are only 3 types of animals (sheep, cows, parrots), 1 type of behavior (wandering), and 1 type of animation; in the future, more animals, behavior types (wandering, resting, tracking, foraging, escaping) and a variety of dynamic animation switching need to be expanded. The original code did not meet these needs and can be easily extended after refactoring.
 * **technical debt**: When the code duplication rate is as high as 30-40%, there are many decision-making points in the code, complex paths, high coupling between modules, and high probability of errors, making testing and maintenance more difficult. After reconstruction, maintenance costs can be reduced and development efficiency improved.
 * **Development efficiency**: The original code requires writing 50+ lines of repeated code to add new animals, modifying animation parameters in 3 places, and adding new behaviors requires modification.`update()` method, making the method verbose. Adding new animals after refactoring: You only need to write 10 lines of code, modify animation parameters in only one place, and add new behaviors by creating a new state class. The efficiency improvement effect is obvious.
 * **game vision**: The animal behavior of the original code is simple and direct, suitable for the initial stage of development, and the art resources may not be in place. After reconstruction, on the basis of strategy mode and behavior mode, animation and behavior are decoupled, so that the animation display of animals changes with the change of state, enhancing the game experience and visual enjoyment.

#### UML类图
* Strategy pattern class diagram
<p align="center">
<img src="diagram/Strategy.svg" alt="Presentation Layer" style="width:100%; max-width:1200px; height:auto;"/>
</p>


* State pattern class diagram
<p align="center">
<img src="diagram/State.svg" alt="Presentation Layer" style="width:100%; max-width:1200px; height:auto;"/>
</p>


#### 重构步骤
In order to solve the above problems, the strategy mode and state mode will be used to reconstruct "all animals share a fixed set of initialization and movement logic" into "each animal can choose its own animation strategy and movement state". Let the code better serve the business so that it can be developed and maintained more efficiently in the future.

1. **Clear refactoring goals**:
 * **Follow the single responsibility principle**: `Animal` it is only responsible for holding state/strategy, and refactoring other classes to focus on behavioral logic and visual performance.
 * **Follow the open-close principle**: Makes it easier to add new animal types, new movement behaviors, and change animation styles.
 * **Decoupling concrete implementation and relying on abstraction**: When the underlying graphics engine changes, `Animal` there is almost no need to change.
 * **Decoupling behavior and animation**: Each animal supports three behavioral states, and the same animal can have multiple strategies and switch as needed.
2. **Establish an animation strategy system**:
* New `AnimationStrategy.h` 
* Define abstract interface `AnimationStrategy` 
```cpp
class AnimationStrategy {
public:
virtual ~AnimationStrategy() = default;
virtual void applyAnimation(Sprite* sprite) = 0;
};
```
* Implement general strategy class `GenericAnimationStrategy`, supports loading frame sequences by prefix
```cpp
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
std::string frameName = prefix + std::to_string(i) +".png";
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
```

3. **Define behavioral state machine**:
* New `AnimalState.h` 
* Declare abstract base class `AnimalState` 
```cpp
class AnimalState {
public:
virtual ~AnimalState() = default;
virtual void enter(Animal* animal) = 0;
virtual void update(Animal* animal, float delta) = 0;
virtual void exit(Animal* animal) = 0;
virtual std::string getName() const = 0;
};
```
* Achieve three specific states:
    * `WanderingState`: Random movement + wander animation
    * `ChasingState`: Move towards the target + chase animation (chasing point can be set)
    * `RestingState`: Still + rest animation, automatically switch back to wandering after 3 seconds
```cpp
// ------------------ Wandering ------------------
class WanderingState : public AnimalState {
public:
void enter(Animal* animal) override {
animal->setAnimationStrategy(
std::make_unique<GenericAnimationStrategy>(animal->getAnimPrefix() +"_wander")
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
std::make_unique<GenericAnimationStrategy>(animal->getAnimPrefix() +"_chase")
);
}

void update(Animal* animal, float delta) override {
Vec2 dir = chaseTarget - animal->getPosition();
if (dir.length() > 5.0f) {
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
const float MAX_REST = 3.0f;

public:
void enter(Animal* animal) override {
animal->setAnimationStrategy(
std::make_unique<GenericAnimationStrategy>y(animal->getAnimPrefix() +"_rest")
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

```

4. **Transform the Animal base class**:
* in `Animal.h` medium:
    * Add members:`unique_ptr<AnimalState> currentState` and `unique_ptr<AnimationStrategy> currentAnimation` 
    * Add method:`changeState()`,`setAnimationStrategy()` 
    * Declare virtual function `getAnimPrefix()` for subclasses to specify resource prefixes

```cpp
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

// State & Animation Control
void changeState(std::unique_ptr<AnimalState> newState);
void setAnimationStrategy(AnimationStrategy* strategy);

// Getters
Vec2 getTargetPosition() const { return targetPosition; }
void setTargetPosition(const Vec2& pos) { targetPosition = pos; }
float getSpeed() const { return speed; }
const std::string& getAnimPrefix() const { return animPrefix; }
const Rect& getBounds() const { return Bounds; }
};
```
* in `Animal.cpp` medium:
    * Implementation `update()` forward to current state
    * Implement state switching logic (call exit → enter)
    * in `setAnimationStrategy()` apply new animation in and stop old action
```cpp
void Animal::update(float delta) {
if (currentState) {
currentState->update(this, delta);
}
}

void Animal::changeState(std::unique_ptr<AnimalState> newState) {
if (currentState) {
currentState->exit(this);
}
currentState = std::move(newState);
if (currentState) {
currentState->enter(this);
}
}

void Animal::setAnimationStrategy(AnimationStrategy* strategy) {
currentAnimation.reset(strategy);
if (strategy && this->isRunning()) {
strategy->applyAnimation(this);
}
}
```

5. **Update specific animal classes** 
* Modify `Sheep`,`Cow`,`Parrot` constructor:
* Set their own `animPrefix` 
* Called during initialization `changeState(std::make_unique<WanderingState>())` 
* Remove original hard-coded animation logic

```cpp
bool Sheep::init(const std::string& filename){
if (!Sprite::initWithFile(filename)) {
CCLOG("Error: Failed to load Sheep image: %s", filename.c_str());
return false;
}
animPrefix ="animal/Sheep";
changeState(std::make_unique<WanderingState>());
return true;
}

```
```cpp
bool Cow::init(const std::string& filename) {
if (!Sprite::initWithFile(filename)) {
CCLOG("Error: Failed to load Cow image: %s", filename.c_str());
return false;
}
animPrefix="animal/Cow";
changeState(std::make_unique<WanderingState>());
return true;
}
```

```cpp
bool Parrot::init(const std::string& filename) {
if (!Sprite::initWithFile(filename)) {
CCLOG("Error: Failed to load Parrot image: %s", filename.c_str());
return false;
}
animPrefix="animal/Parrot";
changeState(std::make_unique<WanderingState>());
return true;
}
```

#### Improvements and Benefits
1. **Reduce code duplication rate**:
* It turns out that each subclass has to create its own animation, but the creation logic is exactly the same. The subclass inherits all the code of the base class, but cannot reuse the logic of the base class and can only implement it repeatedly. Centralized management with an abstraction layer avoids rewriting the same code in many places
2. **Reduce coupling**:
* After reconstruction `Animal` coupling `AnimationStrategy` and `AnimalState`, with `Sprite`,`Animation`,`Animate` loose coupling. Animal is only responsible for the high-level logic of the "animal", and the animation and movement details are left to the strategy/state, in line with the single responsibility principle.
3. **Enhance scalability**:
* Add new animal behavior status, just add `AnimalState.h` added status class in . Code can change animation strategies and states at runtime.
4. **Improve code readability**:
* Separate strategies and states into classes, making the code structure clearer, clearer intentions, and fewer places requiring comments.
5. **“Status” really drives “performance”**:
* Animation strategies are aligned with "state" rather than bound to "animal type". Each animal supports three behavioral states, and the same animal can have multiple strategies and switch as needed. The corresponding animation is automatically switched when the state is switched. The animation resources correspond to the behavioral state one-to-one. A common strategy with parameters is clearly used instead of creating a new class for each combination, which can prevent the explosion of classes.

---
### Refactor using the observer pattern

#### Original question

1. **Crop maturity logic and UI logic coupling**:
 * **Tightly coupled**: After crop maturity occurs, texture updates and UI expressions are performed directly within this class. The visualization layer and business layer are mixed and cannot be reused and expanded.
 * **Lack of external event notification mechanism**: Mature events are only processed internally. The task system, statistics system, and sound effect module cannot know the event. New requirements must directly modify this type, which violates the principle of openness and closure.


```cpp
if (state == State::growing) {
    growthTime += delta;
    if (growthTime >= matureTime) {
        state = State::matured;
        this->setTexture("plant/matured.png");   
        log("Crop matured!");                    
    }
}
```

2. **Automatic harvesting logic is crude**:
 * **No signal prompt**: No signal is sent to the system after automatic harvesting, the UI will not display a disappearing prompt, the sound effects will not be triggered, and the task count will not be updated.
 * **Event semantics cannot be distinguished**: The system cannot distinguish between manual harvesting and automatic harvesting or withering event types.

```cpp
else if (state == State::matured) {
    growthTime += delta;
    if (growthTime >= matureTime * 3) {
        state = State::harvested;
        this->setTexture("plant/cropharvested.png");
    }
}
```

3. **Time lapse is strongly coupled with UI** 
 * **Violates the single responsibility principle**:`outside` responsible for both the time system and UI display, taking on multiple responsibilities.
 * **UI depends on outside**: If you join in the future `InDoorScene` or `TownScene` the same logic must be copied, and the code duplication is serious.

```cpp
void outside::updateTime(float dt) {
    totalTime += dt;
    if (totalTime >= 60) {
        minute++;
        totalTime = 0;
        auto label = dynamic_cast<Label*>(getChildByName("timeLabel"));
        label->setString(StringUtils::format("%d", minute));  // 直接操作UI
    }
}
```

#### Necessity of refactoring

current `valley-main` the event system is tightly coupled, difficult to expand, and the event propagation chain is incomplete. Therefore, it is necessary to introduce the observer pattern to decouple event publishing and event processing to achieve unified event flow.
Observer pattern passes `EventCenter` unified management of event subscription and distribution to achieve:
- Events are propagated from the trigger source to multiple observers
- Separation of event logic and performance logic
- Supports dynamic expansion of modules without modifying existing code
This significantly improves system scalability and maintainability.

#### UML class diagram

* Observer pattern class diagram
<p align="center">
<img src="diagram/ObserverPatternUML.svg" alt="Presentation Layer" style="width:100%; max-width:1200px; height:auto;"/>
</p>

#### Refactoring steps

Refactoring to use the observer pattern `valley-main` for the event system, we decouple event processing logic from crops, time systems, UI managers and other classes, so that they are only responsible for state changes and event publishing, while event processing is uniformly undertaken by observers. In the current version of the system, except for crops, time events are represented by independent `TimePublisher` responsible for generating and passing global `EventCenter` broadcast to `outside`,`UIManager` wait for the observer.

1. **Define observer interface** 

* Create a `Observer` interface defines the methods that all observers need to implement.

```cpp
class Observer {
public:s
    virtual ~Observer() = default;
    virtual void onNotify(const EventData& event) = 0;
};
```


2. **Define event types and event data structures** 

* Implement the enumeration types and event encapsulation objects required by the event system.

```cpp
enum class EventType {
    MinuteChanged,
    CropMatured,
    CropHarvested,
    CropDead
};

class EventData {
public:
    EventType type;
    void* sender;

    EventData(EventType t, void* s) : type(t), sender(s) {}
};
```


3. **Create a unified event center** 

* Design the event center as an observer, responsible for maintaining the list of observers and notifying observers when events are released.
*`EventCenter` designed as a global singleton, it ensures that all event sources and observers in the system always share the same event center.

```cpp
class EventCenter {
public:
    static EventCenter* getInstance();

    void attach(Observer* obs) { observers.pushBack(obs); }
    void detach(Observer* obs) { observers.eraseObject(obs); }

    void publish(EventType type, void* sender) {
        EventData event(type, sender);
        for (auto obs : observers) {
            obs->onNotify(event);
        }
    }

private:
    cocos2d::Vector<Observer*> observers;
};
```

4. **Modify `Crop` class**:

* All logic that originally directly modified the UI has been removed and replaced by publishing events, which are responded to by observers.


```cpp
if (state == State::matured) {
    // add：Publish maturity event
    EventCenter::getInstance()->publish(EventType::CropMatured, this);
}
```

```cpp
void Crop::harvest() {
    state = State::harvested;

    // add：Publish manual harvest event
    EventCenter::getInstance()->publish(EventType::CropHarvested, this);
}
```


5. **Modify `outside` Class: From "Event Source" to "Observer"**:
* `outside` no longer responsible for generating time events, only responsible for responding to UI updates:

```cpp
class outside : public cocos2d::Layer, public Observer {
public:
    virtual void onNotify(const EventData& event) override;
};

```

* Sample response:

```cpp
void outside::onNotify(const EventData& event) {
    if (event.type == EventType::MinuteChanged) {
        auto label = dynamic_cast<Label*>(getChildByName("timeLabel"));
        if (label) label->setString(this->getFormattedTime());
    }
}

```


6. **Add UIManager as observer**:
* `UIManager` it is also an observer, responsible for unified management of UI components, such as crop prompts, animation display, etc.

```cpp
void UIManager::onNotify(const EventData& event) {
    if (event.type == EventType::CropMatured) {
        showMatureIcon(static_cast<Crop*>(event.sender));
    }
}

```

7. **Observer registration**:
* in `outside::init()` observer registration is performed in `outside` become an observer of the global event system and be able to respond `Crop` and scene events.
```cpp
bool outside::init() {
    EventCenter::getInstance()->attach(this);
    ...
    return true;
}
```
8. **Introducing time event source: TimePublisher**:
* Added `TimePublisher`, used to uniformly manage the passage of time and publish time change events to observers.

* `TimePublisher` it does not undertake UI updates, but focuses on event publishing:
```cpp
EventCenter::getInstance()->publish(EventType::MinuteChanged, this);
```

#### Improvements and Benefits

1. **Decoupling and abstraction**: by definition `Observer` the interface completely separates the event processing logic from the crop class and scene class, making the UI update, task processing and other logic that were originally mixed inside independent, forming a clear observer architecture.
2. **single responsibility principle**:`Crop is only responsible for life cycle and event publishing, TimePublisher is only responsible for time advancement and event publishing, and outside/UIManager is only responsible for UI response. The boundaries of responsibilities are obvious and the code is clearer.
3. **Improve scalability**: No modification is required when adding new observers in the future.`Crop`,`outside` etc. Event source code, the system has good scalability.
4. **Dynamic event response mechanism**:`EventCenter` support runtime `attach/detach` observers allow the system to flexibly control which functions are enabled or disabled.
5. **Improve code reusability**: Unified event entrance `onNotify` the sharing mechanism with the event center eliminates the duplication of cross-module logic such as UI updates, sound effects, task statistics, etc., and the related processing is concentrated in the respective observer classes.
6. **Reduce coupling and make the system structure clearer**: The event source no longer directly operates the UI, no longer relies on external module code, eliminating the confusing reference of "who calls whom", and the overall code hierarchy is more intuitive.
7. **More event types will be supported in the future**: Regardless of new events such as holiday triggers, weather changes, NPC behaviors, etc., you only need to define new `EventType` and publish it in the event source, the existing system will be automatically compatible.

## Refactor using design patterns not covered in the course

### Refactoring using the object pool pattern

#### pattern explanation
 Object pool pattern it is a creational design pattern that uses Pre-create and reuse a set of initialized objects, avoid frequently creating and destroying objects at runtime. When the client needs an object, it "borrows" it from the pool; after using it, it "returns" the object to the pool instead of destroying it directly. This mode is particularly suitable for High creation cost, frequent use, short life cycle object management.

#### core idea
- **Reuse is better than rebuilding**: Objects are not thrown away after use, but recycled and reused.
- **Resource preallocation**: Pre-create a batch of objects when the system is idle or started to reduce runtime overhead.
- **Control the total amount of resources**: Limit the number of concurrent objects through the pool size to prevent memory explosion.

#### Workflow
1. **Initialization pool**: Create a batch of objects and put them into the "idle queue".
2. **Get object**:
    - If the idle queue is not empty → retrieve an object, reset its state (e.g., position, properties), and return it to the client.
    - If the queue is empty → optional:
        - Block and wait;
        - Dynamically create a new object (optional);
        - Throw an exception (strict pool).

3. **Return object**: Client call `release()`, the object is put back into the free queue (memory is not cleared).
4. **destruction pool**: Release all objects uniformly when the program ends.

#### Advantages
 * **Improve performance**:Avoid frequent `new/delete` or `malloc/free` overhead (especially for complex objects).
 * **Reduce memory fragmentation**: The object address is relatively fixed, reducing heap memory fragmentation.
 * **Control resource usage**: Limit the maximum number of objects to prevent system overload (such as database connection pool).
 * **Reduce GC pressure**: Reduce the generation of temporary objects and reduce the burden of garbage collection.
 * **Improve response speed**: Obtaining an object is an O(1) operation with no initialization delay.

#### Disadvantages
 * **Increased memory usage**: The object is resident in memory and takes up space even if it is not used.
 * **Status management is complex**: The returned object must completely reset its state, otherwise it will contaminate the next use.
 * **Thread safety issues**: Locking is required in a multi-threaded environment, which may become a performance bottleneck.
 * **Not suitable for long-lived objects**: If the object is occupied for a long time, the advantages of the pool cannot be reflected.
 * **Difficulty debugging**: Object reuse may lead to difficult-to-track logic errors (such as residual data).

#### Application scenarios
 * **game development**: Bullets, particles, enemies, animated objects (frequently created/destroyed).
 * **Web backend**: Database connection pool (such as HikariCP), HTTP client pool.
 * **network programming**: Socket connection, buffer (Buffer) multiplexing.
 * **scientific computing**: Cache of large data structures such as matrices and vectors.
 * **Mobile terminal**: ViewHolder reuse of RecyclerView/ListView (Android).
 * **AI/simulation system**: Sensor data packet, event object pool.

---

#### Original Problem
1. **Risk of resource exhaustion** 
- New threads are created for each request or task, and the number of threads may grow without limit.
- A large number of threads can exhaust memory, resulting in `OutOfMemoryError`.

```cpp
void CharacterWithTools::plantcrop(Vec2 position)
{
int gridX = static_cast<int>(position.x / gridWidth);
int gridY = static_cast<int>(position.y / gridHeight);
Vec2 gridPosition(gridX, gridY);
if (checkCrop(position))
{
CCLOG("Error: Crop already exists at this location!");
return;
}
auto crop = Crop::create("plant/cropseed.png");
if (crop == nullptr) {
CCLOG("Error: Failed to plant crop!");
return;
}
crop->setPosition(Vec2(position.x, position.y - 50));
this->getParent()->addChild(crop);
cropPositions[gridPosition] = true;
}
```

2. **High performance overhead** 
- Thread creation/destruction costs are high, involving kernel scheduling, memory allocation, context switching, etc.
- Frequently creating threads will cause a lot of CPU time to be spent on scheduling rather than business logic.
- Response latency increases and throughput decreases.

3. **Lack of control and management** 
- The maximum number of concurrencies cannot be limited, which can easily cause an avalanche effect.
- Unable to monitor the number of active threads and task queue status.
- Unable to shut down gracefully, wait for task completion, reject overloaded tasks, etc.

4. **Lack of advanced feature support** 
- Unable to implement scheduled tasks and periodic tasks (requires cooperation `Timer` or implemented manually).
- Task return results are not supported (`Future`), timeout control, batch submission, etc.

#### Necessity of Refactoring

- Reduce frequent creation/destruction and improve performance and stability

- `Sprite`/`Node` after reuse:

* The number of allocations is significantly reduced (generally reduced by 20 to 60 times)
*`Autorelease` pressure drops → FSP fluctuations decrease
* Unifiedly reset object status to prevent residual bugs
* Called uniformly after being removed from the pool, and restored uniformly when recycled into the pool

#### UML Class Diagram
* Object pool class diagram
<p align="center">
<img src="diagram/Action.svg" alt="Presentation Layer" style="width:80%; max-width:1200px; height:auto;"/>
</p>

#### Refactoring Steps

1. **Get object**:

```cpp
static Sprite* getPooledTool(const std::string& filename) {
auto& list = toolPool[filename];

if (!list.empty()) {
Sprite* tool = list.back();
list.pop_back();

// reset
tool->stopAllActions();
tool->setVisible(true);
tool->setOpacity(255);
tool->setRotation(0);
tool->setScale(1.0f);

return tool;
}

// Pool is empty → create new object
Sprite* tool = Sprite::create(filename);
tool->retain(); // Pool resources need to be retained
return tool;
}
```
2. **Recycle objects**:

```cpp
static void recycleTool(Sprite* tool, const std::string& filename) {
tool->stopAllActions();
tool->setVisible(false);
tool->removeFromParent();
toolPool[filename].push_back(tool);
}
```
#### Improvements and benefits

1. After reconstruction by introducing the object pool mechanism, multi-dimensional optimization and improvement has been achieved in the operation scenarios of characters using tools, planting crops and harvesting crops:

- When using the tool, call `getPooledTool` get the pooling tool object and pass it after use `recycleTool` recycling;
- When planting crops, call `getPooledCrop` get the pooled crop object and execute `resetState` reset state, called during harvest phase `recycleCrop` recycle crop objects.

2. The transformation model of the object pool has brought significant effect improvements:

- **performance level**: The original implementation caused significant jitter in FPS due to frequent dynamic creation and destruction of objects; after reconstruction, memory allocation operations were reduced by object reuse, making FPS performance more stable.

- **Memory level**:Original dependency `autorelease` the mechanism manages objects, resulting in greater memory management pressure; after reconstruction, the number of object allocations is significantly reduced (20 to 60 times), effectively alleviating the memory fluctuation problem.

- **status management level**: Object reuse in the original code is prone to state residues, causing common bugs; after reconstruction, through unified `resetState` the reset mechanism ensures that the object status is clean and improves system stability.

- **maintainability level**: The original object creation and deletion logic was scattered in multiple codes, resulting in high maintenance costs; after reconstruction, object acquisition, recycling and other logic are centralized in the object pool for unified management, making the code structure clearer and facilitating subsequent maintenance and expansion.


## Explanation of AI Tool Usage

### Exploration and Selection of Design Patterns
* In the early stages of the project, we found that there were a large number of direct calls between various game modules (such as time, animals, plants), and the code was highly coupled and difficult to maintain. In particular, event propagation logic is highly dispersed.`Crop` directly operate the UI,`outside` responsible for time logic and UI at the same time, resulting in business logic and presentation logic being mixed together. With the increase in demand (weather system, festival activities, multi-scene UI pages, achievement statistics, etc.), the original architecture can no longer carry it, and a mechanism that can unify event flow and reduce dependence is needed.
* In the process of exploring design ideas, we used AI tools to analyze the root causes of coupling problems in the existing architecture and referred to the pattern selection suggestions it gave. The AI ​​tool demonstrates the overall structural characteristics of the observer pattern, and points out that inter-module communication can be unified and cross-module references can be reduced through the "event center-observer" approach. Based on this inspiration, we chose to use the observer pattern to reconstruct `valley-main` event streaming system, and with `EventCenter` as a unified event scheduling core.

### Refactoring and Generation of Specific Code
* During the specific code reconstruction process, AI tools assisted us in generating some basic skeletons. For example, in the animal module, each animal has only one fixed "default walking" animation, which cannot reflect different behavioral states. We tried to use AI tools to generate a reconstruction plan for the State Pattern: AI automatically generated `AnimalState` abstract interface and `ChasingState`,`WalkingState` and other basic state skeletons. On this basis, we combined the API of Cocos2d-x for secondary improvement and function filling, so that behavioral logic and state management can be decoupled.
* Similarly, in the reconstruction of the event system, AI assisted us in generating `Observer` interface,`EventData` the basic framework code of data structure and event center. These template codes allow us to quickly start the refactoring work and further adjust it according to the engine environment to make it meet the needs of valley-main.

### Reflection and Discussion
 * **best practices**: We’ve found that the most effective role for AI in this process is as a “pair programming partner.” It can quickly provide a framework for design patterns, generate sample code, explain complex structures, and assist in verifying whether the design direction is reasonable. However, the final architectural decisions, module boundary division, and engine API adaptation still need to be completed by us.
 * **limitations**: AI cannot understand `valley-main` the overall architecture of the system also cannot actively identify which classes belong to the "God class" (such as the early `outside.cpp`). At the same time, its knowledge may vary between versions, and the generated code occasionally uses deprecated or incompatible APIs. Sometimes, AI will provide code that is theoretically correct but cannot be run directly in the Cocos2d-x environment and requires manual correction. "
 * **Challenges and Solutions**: The biggest challenge is that the code generated by AI cannot be directly used in the project. We must read the official Cocos2d-x documentation, check the specific class inheritance relationship, and verify the actual behavior of each API through debugging to ensure that the final code runs correctly. This process made us realize that human judgment and architectural understanding are the core, and AI is more suitable as an auxiliary tool. The final process is: humans formulate the design, then use AI to generate a reference skeleton, and then humans perform in-depth tailoring and adjustment.

## The Value Proposition of Refactoring: A Design Patterns Perspective

### Creational Patterns

* In the creative reconstruction process, the generator mode, factory mode and object pool mode are not stacked into the system in isolation, but a complete collaborative process is established around core objects such as characters, animals, crops and tools. The initial problem with the animation build phase is that something like `buildWalkLeft()`,`buildWalkRight()` the same frame splicing and delay setting logic appears repeatedly in animation creation functions, which is not only redundant but also difficult to modify uniformly. introduce `AnimationBuilder::from().frames().delay().build()` after that, all animation resources are generated through standardized chain construction. Whether it is a character walking animation or an animal wandering animation, a consistent initialization method can be maintained, making the animation creation itself a highly standardized process.
* On this basis, the creation of animals and crops is no longer directly called in the business code `Sheep::create()` or `Wheat::create()`, but handed over to `AnimalFactoryManager::createAnimal()` with `CropFactoryManager::createCrop()` unified processing. The factory not only completes the new/init of the object, but also binds the animation built by AnimationBuilder to the object according to the type. For example `SheepFactory::createAnimal()` the built one will be automatically called internally `buildDefaultWalkAnimation()` or set its `initState()`. In this way, animation construction and object initialization form a natural connection, and the business code does not need to care about the details of object construction.
* However, when the game is running, a large number of objects have extremely short life cycles, such as Sprites when tools are used, residual nodes after harvesting crops, etc. Even though the factory creation process has been regulated, frequent calls `Sprite::create()` still results in significant performance jitter. Therefore, the object pool pattern becomes an important complement to the runtime phase.`ToolPool::getPooledTool()` objects in the pool will be reused first. If the object is new, it will still be initialized by the factory (or native constructor); after use, it will be initialized through `ToolPool::recycleTool()` return and recall `resetState()`, ensuring that the object state is clean and consistent. The premise for the object pool to operate smoothly is that the factory construction process itself is standardized, predictable, and repeatable, which in turn relies on the standardization of animation generators and initialization logic.
* In the end, a clear chain of division of labor was formed between the three:`AnimationBuilder::build()` responsible for standardizing resource construction;`AnimalFactoryManager::createAnimal()` with `CropFactoryManager::createCrop()` responsible for unified object initialization;`ToolPool::getPooledTool()` with `recycleTool()` responsible for high-frequency reuse during runtime. The relationship of build → create → reuse is naturally connected together, realizing a complete closed loop from resources to objects to life cycle management.

### Structural Patterns
* When we first started to reconstruct the scene system, we gave priority to Facade to uniformly encapsulate the scene switching process. The reason is that scene creation, resource preloading, parameter processing and `Director` the switching method is seriously scattered in the business logic, which is not only scattered but also highly repetitive, resulting in any scene-related changes requiring synchronous maintenance in multiple modules. Appearance mode can solve this problem very well: through a `GameSceneFacade` centrally manage the scene switching process and expose a highly simplified unified entrance to the outside world, so that the upper-layer logic does not need to touch any underlying implementation details, thereby significantly reducing the call complexity and improving the readability and consistency of the code.
* However, when the appearance mode was initially implemented, we found that the creation interfaces inside different scenes varied widely, and some needed `mapIndex` parameters, some are needed `SaveData`, some even need to initialize several managers first. When the appearance mode needs to directly call these specific scene classes, it has to contain a lot of branch judgments and specific type logic, making the appearance class itself become more and more bloated, and even fall back into a strong dependence on specific scene classes. What's more serious is that adding new scenes means that the internal code of the appearance mode must be modified, which obviously violates the opening and closing principle and makes it difficult for the appearance mode to maintain its original intention of "stable entry".
* Therefore, we introduced the adapter mode (Adapter) to cooperate with the appearance mode. The adapter pattern isolates the complex and independent construction logic within each scene, and uses a unified `ISceneCreator` the interface is encapsulated to standardize the scene creation interface. Appearance mode no longer needs to know the details of each scene, it only needs to call the corresponding adapter according to the scene type.
* Ultimately, the appearance pattern is responsible for unifying the entrance and shielding complexity, while the adapter pattern is responsible for absorbing differences and providing a unified interface. The two cooperate with each other, making the entire scene system not only easy to call, but also enhancing the scalability and decoupling of the entire system.

### Behavioral Patterns
* In the initial refactoring phase, we adopted the strategy pattern and state pattern for code transformation. However, it was quickly discovered that since each animal has only one fixed "default walking" animation, the strategy mode is actually useless, resulting in a strong coupling between animation and behavior. Even if we create something like `SheepAnimationStrategy` for such a class, once Sheep needs to support three different animations, it has to stuff all related logic into the same strategy class, which obviously violates the single responsibility principle. When we adopt a more fine-grained design, the advantages of the state model really emerge: the same animal can have multiple states, each state accurately corresponds to an animation form, with clear logic and clear responsibilities.
* Therefore, the purpose of refactoring the code should never stop at simply stacking multiple design patterns, but should let them collaborate with each other and complement each other's advantages, pay attention to whether the relationship between them is clear, and whether the collaboration is smooth, to form a set of overall solutions with reasonable structure, clear responsibilities, maintainability and scalability, so as to achieve completeness and elegance in design.

## Summary
Through this systematic reconstruction of the overall project code, we not only solved partial technical debt, but also established a set of sustainable evolution engineering paradigms. The following is our core understanding gained from practice:
1. **Design patterns must serve overall architectural goals and not be used in isolation**: In the early refactoring, we used strategies, singletons, observers and other patterns sporadically in different modules. As a result, styles were fragmented and the cost of understanding increased. Later, we unified the guiding ideology of "layering + combination": the bottom layer uses factory methods to manage the object life cycle, the middle layer uses state machines to coordinate business processes, and the upper layer uses observers to implement event broadcasting. Patterns are no longer siled, but work together in a clear architectural hierarchy to form a consistent design language.

2. **The essence of decoupling is to reduce the chain reaction of cross-module changes**: Before reconstruction, modifying a UI component may require changing the data model, and adjusting a network request will affect the local cache logic. By introducing the interface abstraction layer, we make high-level modules only rely on abstraction and are not bound to specific implementations.

3. **Performance and maintainability are not opposites, but goals that can be optimized together**: For example, in terms of resource loading, the object pool is reused in the operation scenarios of characters using tools, planting crops, and harvesting crops, achieving multi-dimensional optimization and improvement, and simplifying the caller code. This proves that good design often brings dual benefits of performance and readability.

4. **Tool chain and engineering specifications are the cornerstone of large-scale reconstruction**: We conduct project management on github (https://github.com/Alian-yy/Stardew_Valley_Refactored). Every submission is checked, and every merge is accompanied by a visual difference comparison. It is these "invisible infrastructures" that support us in safely and efficiently advancing refactoring across hundreds of files.

5. **Technology decisions should be based on evolutionary costs, not short-term convenience**: Use composition instead of inheritance, use configuration instead of hard coding, and use interfaces instead of concrete classes. Although it takes 20% more time in the initial stage, the subsequent development speed of each new requirement is increased by more than 50%. This makes us firmly believe that a good architecture does not save time, but saves future trouble.

This full-stack refactoring made us realize that excellent software is not a masterpiece created overnight, but a living entity that constantly corrects itself through continuous feedback and iteration. Only when design patterns, architectural principles, and engineering practices are integrated into the daily development habits of the team can they truly be transformed into the long-term competitiveness of the project.