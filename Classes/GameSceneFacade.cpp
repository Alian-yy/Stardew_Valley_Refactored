/****************************************************************************
 * 
 * Refactored with Facade Pattern + Adapter Pattern:add GameSceneFacade.cpp
 * 
 ****************************************************************************/

#include "GameSceneFacade.h"
#include "cocos2d.h"

USING_NS_CC;

// ==================== Adapter Pattern: Get Adapter Manager ====================
SceneAdapterManager* GameSceneFacade::getAdapterManager() {
    return SceneAdapterManager::getInstance();
}

// ==================== Facade Pattern: New runWithBeginScene ====================
// ==================== Adapter Pattern: Create scene through adapter ====================
// Starts the game, running the beginning scene

void GameSceneFacade::runWithBeginScene()
{
    // Create scene using adapter, no longer directly depends on valleybegin class
    Scene* scene = getAdapterManager()->createScene("ValleyBegin");
    if (scene) {
        Director::getInstance()->runWithScene(scene);
    }
}

// ==================== Facade Pattern: New showMenuScene ====================
// ==================== Adapter Pattern: Create scene through adapter ====================
// Switches from the beginning scene to the menu scene (with transition animation)
 
void GameSceneFacade::showMenuScene()
{
    // Create scene using adapter, no longer directly depends on menu class
    Scene* scene = getAdapterManager()->createScene("Menu");
    if (scene) {
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
    }
}

// ==================== Facade Pattern: New enterFarmScene ====================
// ==================== Adapter Pattern: Create scene through adapter, pass parameters ====================
// Enters the farm scene from the menu scene
void GameSceneFacade::enterFarmScene(int mapIndex)
{
    // Create scene using adapter, pass parameters through ValueMap
    // No longer directly depends on outside class
    ValueMap params;
    params["mapIndex"] = Value(mapIndex);
    
    Scene* scene = getAdapterManager()->createScene("Farm", params);
    if (scene) {
        Director::getInstance()->replaceScene(scene);
    }
}

// ==================== Facade Pattern: New enterHouseScene ====================
// ==================== Adapter Pattern: Create scene through adapter ====================
// Enters the house scene from the farm scene
void GameSceneFacade::enterHouseScene()
{
    // Create scene using adapter, no longer directly depends on intovalley class
    Scene* scene = getAdapterManager()->createScene("House");
    if (scene) {
        Director::getInstance()->pushScene(scene);
    }
}

// ==================== Facade Pattern: New enterOtherAreaScene ====================
// ==================== Adapter Pattern: Create scene through adapter ====================
// Enters another area scene from the farm scene

void GameSceneFacade::enterOtherAreaScene()
{
    // Create scene using adapter, no longer directly depends on othersence class
    Scene* scene = getAdapterManager()->createScene("OtherArea");
    if (scene) {
        Director::getInstance()->pushScene(scene);
    }
}

// ==================== Facade Pattern: New returnToPreviousScene ====================
// Returns to the previous scene from a sub-scene (house/other area)

void GameSceneFacade::returnToPreviousScene()
{
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->popScene();
    }
}
