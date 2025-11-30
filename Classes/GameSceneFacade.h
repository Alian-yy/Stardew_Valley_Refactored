/****************************************************************************
 * 
 * 使用Facade模式+适配器模式重构后的GameSceneFacade.h
 * 
 ****************************************************************************/

#ifndef _GAMESCENEFACADE_H_
#define _GAMESCENEFACADE_H_

#include "cocos2d.h"
// ==================== 适配器模式: 移除直接依赖，改为使用适配器 ====================
// 不再直接包含具体场景类，实现解耦
#include "SceneAdapter.h"

USING_NS_CC;

// ==================== 外观模式: 新增GameSceneFacade ====================
// ==================== 适配器模式: 通过适配器创建场景，实现解耦 ====================
/**
 * GameSceneFacade - 场景管理外观类
 * 提供统一的接口来管理所有场景的创建和切换，隐藏与Director交互的复杂性
 * 
 * 使用适配器模式解耦：
 * - 不再直接依赖具体场景类（valleybegin, menu, outside等）
 * - 通过 SceneAdapterManager 统一创建场景
 * - 未来添加新场景只需添加新的适配器，无需修改 Facade
 */
class GameSceneFacade
{
public:
    // ==================== 外观模式: 新增runWithBeginScene ====================
   
    //启动游戏，运行开场场景
    
    static void runWithBeginScene();
    
    // ==================== 外观模式: 新增showMenuScene ====================
    //从开场场景切换到菜单场景（带过渡动画）
    static void showMenuScene();
    
    // ==================== 外观模式: 新增enterFarmScene ====================
    /**
     * 从菜单场景进入农场场景
     * @param mapIndex 地图索引
     */
    static void enterFarmScene(int mapIndex);

    // ==================== 外观模式: 新增enterHouseScene ====================
    //从农场场景进入房屋场景
    static void enterHouseScene();
    
    // ==================== 外观模式: 新增enterOtherAreaScene ====================
    //从农场场景进入其他区域场景
    static void enterOtherAreaScene();
    
    // ==================== 外观模式: 新增returnToPreviousScene ====================
    //从子场景（房屋/其他区域）返回到上一个场景
    static void returnToPreviousScene();
    
private:
    // ==================== 适配器模式: 使用适配器管理器 ====================
    static SceneAdapterManager* getAdapterManager();
};

#endif // !_GAMESCENEFACADE_H_

