/****************************************************************************
 * 
 * 使用适配器模式重构后的场景创建系统实现
 * SceneAdapter.cpp
 * 
 ****************************************************************************/

#include "SceneAdapter.h"
#include "valleybegin.h"
#include "menu.h"
#include "outside.h"
#include "intovalley.h"
#include "othersence.h"

// ==================== 开场场景适配器实现 ====================
Scene* ValleyBeginSceneAdapter::createScene(const cocos2d::ValueMap& params) {
    // 适配 valleybegin::createvalleybeginScene()
    return valleybegin::createvalleybeginScene();
}

// ==================== 菜单场景适配器实现 ====================
Scene* MenuSceneAdapter::createScene(const cocos2d::ValueMap& params) {
    // 适配 menu::createmenuScene()
    return menu::createmenuScene();
}

// ==================== 农场场景适配器实现 ====================
Scene* FarmSceneAdapter::createScene(const cocos2d::ValueMap& params) {
    // 适配 outside::createSceneWithMapIndex(int mapIndex)
    // 从参数中获取 mapIndex，如果没有则使用默认值 0
    int mapIndex = 0;
    if (params.find("mapIndex") != params.end()) {
        mapIndex = params.at("mapIndex").asInt();
    }
    
    return outside::createSceneWithMapIndex(mapIndex);
}

bool FarmSceneAdapter::canCreateScene(const cocos2d::ValueMap& params) const {
    // 可以添加验证逻辑，例如检查地图索引是否有效
    if (params.find("mapIndex") != params.end()) {
        int mapIndex = params.at("mapIndex").asInt();
        return mapIndex >= 0 && mapIndex < 4; // 假设有4个地图
    }
    return true; // 如果没有指定 mapIndex，使用默认值，允许创建
}

// ==================== 房屋场景适配器实现 ====================
Scene* HouseSceneAdapter::createScene(const cocos2d::ValueMap& params) {
    // 适配 intovalley::createintovalleyScene()
    return intovalley::createintovalleyScene();
}

// ==================== 其他区域场景适配器实现 ====================
Scene* OtherAreaSceneAdapter::createScene(const cocos2d::ValueMap& params) {
    // 适配 othersence::createothersenceScene()
    return othersence::createothersenceScene();
}

// ==================== 场景适配器管理器实现 ====================
SceneAdapterManager* SceneAdapterManager::getInstance() {
    static SceneAdapterManager instance;
    return &instance;
}

SceneAdapterManager::SceneAdapterManager() {
    // 注册所有场景适配器
    registerAdapter("ValleyBegin", new ValleyBeginSceneAdapter());
    registerAdapter("Menu", new MenuSceneAdapter());
    registerAdapter("Farm", new FarmSceneAdapter());
    registerAdapter("House", new HouseSceneAdapter());
    registerAdapter("OtherArea", new OtherAreaSceneAdapter());
}

SceneAdapterManager::~SceneAdapterManager() {
    // 清理所有适配器
    for (auto& pair : adapters) {
        delete pair.second;
    }
    adapters.clear();
}

void SceneAdapterManager::registerAdapter(const std::string& sceneType, ISceneCreator* adapter) {
    if (adapter) {
        adapters[sceneType] = adapter;
    }
}

ISceneCreator* SceneAdapterManager::getAdapter(const std::string& sceneType) {
    auto it = adapters.find(sceneType);
    return (it != adapters.end()) ? it->second : nullptr;
}

Scene* SceneAdapterManager::createScene(const std::string& sceneType, const cocos2d::ValueMap& params) {
    ISceneCreator* adapter = getAdapter(sceneType);
    if (adapter) {
        return adapter->createScene(params);
    }
    CCLOG("Error: Scene adapter not found for type: %s", sceneType.c_str());
    return nullptr;
}

void SceneAdapterManager::preloadSceneResources(const std::string& sceneType) {
    ISceneCreator* adapter = getAdapter(sceneType);
    if (adapter) {
        adapter->preloadResources();
    }
}

bool SceneAdapterManager::canCreateScene(const std::string& sceneType, const cocos2d::ValueMap& params) {
    ISceneCreator* adapter = getAdapter(sceneType);
    if (adapter) {
        return adapter->canCreateScene(params);
    }
    return false;
}

