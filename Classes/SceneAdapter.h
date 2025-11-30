/****************************************************************************
 * 
 * Refactored with Adapter Pattern
 * 
 ****************************************************************************/

#ifndef __SCENE_ADAPTER_H__
#define __SCENE_ADAPTER_H__

#include "cocos2d.h"
USING_NS_CC;

// ==================== Adapter Pattern: Scene Creation Interface ====================
class ISceneCreator {
public:
    virtual ~ISceneCreator() = default;
    
    /**
     * Create a scene.
     * @param params Scene parameters (ValueMap supports various parameter types)
     * @return Created scene, or nullptr on failure.
     */
    virtual Scene* createScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) = 0;
    
    /**
     * Get scene type name.
     */
    virtual std::string getSceneType() const = 0;
    
    /**
     * Preload scene resources (optional, improves performance).
     */
    virtual void preloadResources() {}
    
    /**
     * Check whether the scene can be created.
     */
    virtual bool canCreateScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) const {
        return true;
    }
};

// ==================== Adapter: Valley Begin Scene ====================
class ValleyBeginSceneAdapter : public ISceneCreator {
public:
    Scene* createScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) override;
    std::string getSceneType() const override { return "ValleyBegin"; }
};

// ==================== Adapter: Menu Scene ====================
class MenuSceneAdapter : public ISceneCreator {
public:
    Scene* createScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) override;
    std::string getSceneType() const override { return "Menu"; }
};

// ==================== Adapter: Farm Scene ====================
class FarmSceneAdapter : public ISceneCreator {
public:
    Scene* createScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) override;
    std::string getSceneType() const override { return "Farm"; }
    
    bool canCreateScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) const override;
};

// ==================== Adapter: House Scene ====================
class HouseSceneAdapter : public ISceneCreator {
public:
    Scene* createScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) override;
    std::string getSceneType() const override { return "House"; }
};

// ==================== Adapter: Other Area Scene ====================
class OtherAreaSceneAdapter : public ISceneCreator {
public:
    Scene* createScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) override;
    std::string getSceneType() const override { return "OtherArea"; }
};

// ==================== Adapter Manager: Scene Adapter Manager ====================
class SceneAdapterManager {
private:
    std::map<std::string, ISceneCreator*> adapters;
    
    SceneAdapterManager();
    ~SceneAdapterManager();
    
public:
    static SceneAdapterManager* getInstance();
    
    // Register a scene adapter
    void registerAdapter(const std::string& sceneType, ISceneCreator* adapter);
    
    // Get a scene adapter
    ISceneCreator* getAdapter(const std::string& sceneType);
    
    // Unified scene creation interface
    Scene* createScene(const std::string& sceneType, const cocos2d::ValueMap& params = cocos2d::ValueMap());
    
    // Preload resources for a scene
    void preloadSceneResources(const std::string& sceneType);
    
    // Check if scene can be created
    bool canCreateScene(const std::string& sceneType, const cocos2d::ValueMap& params = cocos2d::ValueMap());
};

#endif // __SCENE_ADAPTER_H__
