/****************************************************************************
 * 
 * Refactored with Facade Pattern + Adapter Pattern:add GameSceneFacade.cpp
 * 
 ****************************************************************************/

#include "GameSceneFacade.h"
#include "cocos2d.h"

USING_NS_CC;

// ==================== Adapter Pattern: Get Adapter Manager =================
SceneAdapterManager* GameSceneFacade::getAdapterManager() {
    return SceneAdapterManager::getInstance();
}

// ==================== Facade: runWithBeginScene =============================
// ==================== Adapter Pattern: Create scene via adapter =============
// Start the game and run the opening scene

void GameSceneFacade::runWithBeginScene()
{
    // Create scene using adapter instead of directly depending on valleybegin
    Scene* scene = getAdapterManager()->createScene("ValleyBegin");
    if (scene) {
        Director::getInstance()->runWithScene(scene);
    }
}

// ==================== Facade: showMenuScene ==================================
// ==================== Adapter Pattern: Create scene via adapter ==============
// Switch from opening scene to menu scene with transition animation
 
void GameSceneFacade::showMenuScene()
{
    // Create scene using adapter instead of directly depending on menu class
    Scene* scene = getAdapterManager()->createScene("Menu");
    if (scene) {
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
    }
}

// ==================== Facade: enterFarmScene =====================================
// ==================== Adapter Pattern: Create scene via adapter with parameters ========
// Enter the farm scene from the menu scene
void GameSceneFacade::enterFarmScene(int mapIndex)
{
    // Use ValueMap to pass parameters, no longer directly depend on outside class
    ValueMap params;
    params["mapIndex"] = Value(mapIndex);
    
    Scene* scene = getAdapterManager()->createScene("Farm", params);
    if (scene) {
        Director::getInstance()->replaceScene(scene);
    }
}

// ==================== Facade: enterHouseScene =====================================
// ==================== Adapter Pattern: Create scene via adapter ====================
// Enter house scene from farm scene
void GameSceneFacade::enterHouseScene()
{
    // Create scene using adapter instead of directly depending on intovalley class
    Scene* scene = getAdapterManager()->createScene("House");
    if (scene) {
        Director::getInstance()->pushScene(scene);
    }
}

// ==================== Facade: enterOtherAreaScene ==============================
// ==================== Adapter Pattern: Create scene via adapter ====================
// Enter other area scene from farm scene

void GameSceneFacade::enterOtherAreaScene()
{
    // Create scene using adapter instead of directly depending on othersence class
    Scene* scene = getAdapterManager()->createScene("OtherArea");
    if (scene) {
        Director::getInstance()->pushScene(scene);
    }
}

// ==================== Facade: returnToPreviousScene ====================
// Return from child scenes (house/other area) back to the previous scene

void GameSceneFacade::returnToPreviousScene()
{
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->popScene();
    }
}
