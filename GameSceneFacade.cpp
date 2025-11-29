/****************************************************************************
 * 使用Facade模式重构后的代码
 * GameSceneFacade.cpp - 场景管理外观类实现
 * 提供统一的接口来管理所有场景的创建和切换，隐藏与Director交互的复杂性
 ****************************************************************************/

#include "GameSceneFacade.h"
#include "cocos2d.h"
#include "valleybegin.h"
#include "menu.h"
#include "outside.h"
#include "intovalley.h"
#include "othersence.h"

USING_NS_CC;

// ==================== 外观模式: 新增runWithBeginScene ====================

//启动游戏，运行开场场景

void GameSceneFacade::runWithBeginScene()
{
    auto scene = valleybegin::createvalleybeginScene();
    Director::getInstance()->runWithScene(scene);
}

// ==================== 外观模式: 新增showMenuScene ====================

//从开场场景切换到菜单场景（带过渡动画）
 
void GameSceneFacade::showMenuScene()
{
    Scene* scene = menu::createmenuScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}

// ==================== 外观模式: 新增enterFarmScene ====================
//从菜单场景进入农场场景
void GameSceneFacade::enterFarmScene(int mapIndex)
{
    auto newScene = outside::createSceneWithMapIndex(mapIndex);
    Director::getInstance()->replaceScene(newScene);
}

// ==================== 外观模式: 新增enterHouseScene ====================
//从农场场景进入房屋场景
void GameSceneFacade::enterHouseScene()
{
    Scene* scene = intovalley::createintovalleyScene();
    Director::getInstance()->pushScene(scene);
}

// ==================== 外观模式: 新增enterOtherAreaScene ====================

//从农场场景进入其他区域场景

void GameSceneFacade::enterOtherAreaScene()
{
    Scene* scene = othersence::createothersenceScene();
    Director::getInstance()->pushScene(scene);
}

// ==================== 外观模式: 新增returnToPreviousScene ====================
//从子场景（房屋/其他区域）返回到上一个场景

void GameSceneFacade::returnToPreviousScene()
{
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->popScene();
    }
}

