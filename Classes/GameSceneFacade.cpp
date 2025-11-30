/****************************************************************************
 * 
 * Refactored with Facade Pattern + Adapter Pattern
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
//启动游戏，运行开场场景

void GameSceneFacade::runWithBeginScene()
{
    // 使用适配器创建场景，不再直接依赖 valleybegin 类
    Scene* scene = getAdapterManager()->createScene("ValleyBegin");
    if (scene) {
        Director::getInstance()->runWithScene(scene);
    }
}

// ==================== Facade Pattern: New showMenuScene ====================
// ==================== Adapter Pattern: Create scene through adapter ====================
//从开场场景切换到菜单场景（带过渡动画）
 
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
//从菜单场景进入农场场景
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
//从农场场景进入房屋场景
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
//从农场场景进入其他区域场景

void GameSceneFacade::enterOtherAreaScene()
{
    // Create scene using adapter, no longer directly depends on othersence class
    Scene* scene = getAdapterManager()->createScene("OtherArea");
    if (scene) {
        Director::getInstance()->pushScene(scene);
    }
}

// ==================== Facade Pattern: New returnToPreviousScene ====================
//从子场景（房屋/其他区域）返回到上一个场景

void GameSceneFacade::returnToPreviousScene()
{
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->popScene();
    }
}

