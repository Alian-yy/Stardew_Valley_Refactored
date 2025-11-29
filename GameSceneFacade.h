/****************************************************************************
 * 使用Facade模式重构后的代码
 * GameSceneFacade.h - 场景管理外观类
 * 提供统一的接口来管理所有场景的创建和切换，隐藏与Director交互的复杂性
 ****************************************************************************/

#ifndef _GAMESCENEFACADE_H_
#define _GAMESCENEFACADE_H_

#include "cocos2d.h"
#include "valleybegin.h"
#include "menu.h"
#include "outside.h"
#include "intovalley.h"
#include "othersence.h"

USING_NS_CC;

// ==================== 外观模式: 新增GameSceneFacade ====================
/**
 * GameSceneFacade - 场景管理外观类
 * 提供统一的接口来管理所有场景的创建和切换，隐藏与Director交互的复杂性
 */
class GameSceneFacade
{
public:
    // ==================== 外观模式: 新增runWithBeginScene ====================
    /**
     * 启动游戏，运行开场场景
     */
    static void runWithBeginScene();
    
    // ==================== 外观模式: 新增showMenuScene ====================
    /**
     * 从开场场景切换到菜单场景（带过渡动画）
     */
    static void showMenuScene();
    
    // ==================== 外观模式: 新增enterFarmScene ====================
    /**
     * 从菜单场景进入农场场景
     * @param mapIndex 地图索引
     */
    static void enterFarmScene(int mapIndex);

    // ==================== 外观模式: 新增enterHouseScene ====================
    /**
     * 从农场场景进入房屋场景
     */
    static void enterHouseScene();
    
    // ==================== 外观模式: 新增enterOtherAreaScene ====================
    /**
     * 从农场场景进入其他区域场景
     */
    static void enterOtherAreaScene();
    
    // ==================== 外观模式: 新增returnToPreviousScene ====================
    /**
     * 从子场景（房屋/其他区域）返回到上一个场景
     */
    static void returnToPreviousScene();
};

#endif // !_GAMESCENEFACADE_H_

