/****************************************************************************
 * 
 * 使用Facade模式+适配器模式重构后的GameSceneFacade.cpp
 * 
 ****************************************************************************/

#include "GameSceneFacade.h"
#include "cocos2d.h"

USING_NS_CC;

// ==================== 适配器模式: 获取适配器管理器 ====================
SceneAdapterManager* GameSceneFacade::getAdapterManager() {
    return SceneAdapterManager::getInstance();
}

// ==================== 外观模式: 新增runWithBeginScene ====================
// ==================== 适配器模式: 通过适配器创建场景 ====================
//启动游戏，运行开场场景

void GameSceneFacade::runWithBeginScene()
{
    // 使用适配器创建场景，不再直接依赖 valleybegin 类
    Scene* scene = getAdapterManager()->createScene("ValleyBegin");
    if (scene) {
        Director::getInstance()->runWithScene(scene);
    }
}

// ==================== 外观模式: 新增showMenuScene ====================
// ==================== 适配器模式: 通过适配器创建场景 ====================
//从开场场景切换到菜单场景（带过渡动画）
 
void GameSceneFacade::showMenuScene()
{
    // 使用适配器创建场景，不再直接依赖 menu 类
    Scene* scene = getAdapterManager()->createScene("Menu");
    if (scene) {
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
    }
}

// ==================== 外观模式: 新增enterFarmScene ====================
// ==================== 适配器模式: 通过适配器创建场景，传递参数 ====================
//从菜单场景进入农场场景
void GameSceneFacade::enterFarmScene(int mapIndex)
{
    // 使用适配器创建场景，通过 ValueMap 传递参数
    // 不再直接依赖 outside 类
    ValueMap params;
    params["mapIndex"] = Value(mapIndex);
    
    Scene* scene = getAdapterManager()->createScene("Farm", params);
    if (scene) {
        Director::getInstance()->replaceScene(scene);
    }
}

// ==================== 外观模式: 新增enterHouseScene ====================
// ==================== 适配器模式: 通过适配器创建场景 ====================
//从农场场景进入房屋场景
void GameSceneFacade::enterHouseScene()
{
    // 使用适配器创建场景，不再直接依赖 intovalley 类
    Scene* scene = getAdapterManager()->createScene("House");
    if (scene) {
        Director::getInstance()->pushScene(scene);
    }
}

// ==================== 外观模式: 新增enterOtherAreaScene ====================
// ==================== 适配器模式: 通过适配器创建场景 ====================
//从农场场景进入其他区域场景

void GameSceneFacade::enterOtherAreaScene()
{
    // 使用适配器创建场景，不再直接依赖 othersence 类
    Scene* scene = getAdapterManager()->createScene("OtherArea");
    if (scene) {
        Director::getInstance()->pushScene(scene);
    }
}

// ==================== 外观模式: 新增returnToPreviousScene ====================
//从子场景（房屋/其他区域）返回到上一个场景

void GameSceneFacade::returnToPreviousScene()
{
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->popScene();
    }
}

