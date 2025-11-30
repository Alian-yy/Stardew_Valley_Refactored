/****************************************************************************
 * 
 * Scene Creation System Implementation Refactored with Adapter Pattern
 * 
 ****************************************************************************/

#include "SceneAdapter.h"
#include "valleybegin.h"
#include "menu.h"
#include "outside.h"
#include "intovalley.h"
#include "othersence.h"

// ==================== Valley Begin Scene Adapter Implementation ====================
Scene* ValleyBeginSceneAdapter::createScene(const cocos2d::ValueMap& params) {
    return valleybegin::createvalleybeginScene();
}

// ==================== Menu Scene Adapter Implementation ====================
Scene* MenuSceneAdapter::createScene(const cocos2d::ValueMap& params) {

    return menu::createmenuScene();
}

// ==================== Farm Scene Adapter Implementation ====================
Scene* FarmSceneAdapter::createScene(const cocos2d::ValueMap& params) {

    int mapIndex = 0;
    if (params.find("mapIndex") != params.end()) {
        mapIndex = params.at("mapIndex").asInt();
    }
    
    return outside::createSceneWithMapIndex(mapIndex);
}

bool FarmSceneAdapter::canCreateScene(const cocos2d::ValueMap& params) const {
    // Optional validation logic, e.g., check if map index is valid
    if (params.find("mapIndex") != params.end()) {
        int mapIndex = params.at("mapIndex").asInt();
        return mapIndex >= 0 && mapIndex < 4; // Assume 4 maps exist
    }
    return true; // If no mapIndex provided, allow creation
}

// ==================== House Scene Adapter Implementation ====================
Scene* HouseSceneAdapter::createScene(const cocos2d::ValueMap& params) {

    return intovalley::createintovalleyScene();
}

// ==================== Other Area Scene Adapter Implementation ====================
Scene* OtherAreaSceneAdapter::createScene(const cocos2d::ValueMap& params) {

    return othersence::createothersenceScene();
}

// ==================== Scene Adapter Manager Implementation ====================
SceneAdapterManager* SceneAdapterManager::getInstance() {
    static SceneAdapterManager instance;
    return &instance;
}

SceneAdapterManager::SceneAdapterManager() {
    // Register all scene adapters
    registerAdapter("ValleyBegin", new ValleyBeginSceneAdapter());
    registerAdapter("Menu", new MenuSceneAdapter());
    registerAdapter("Farm", new FarmSceneAdapter());
    registerAdapter("House", new HouseSceneAdapter());
    registerAdapter("OtherArea", new OtherAreaSceneAdapter());
}

SceneAdapterManager::~SceneAdapterManager() {
    // Cleanup all adapters
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
