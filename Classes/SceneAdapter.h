/****************************************************************************
 * 
 * 使用适配器模式重构后的场景创建系统
 * SceneAdapter.h - 统一不同场景的创建接口，解耦 GameSceneFacade
 * 
 ****************************************************************************/

#ifndef __SCENE_ADAPTER_H__
#define __SCENE_ADAPTER_H__

#include "cocos2d.h"
USING_NS_CC;

// ==================== 适配器模式：场景创建接口 ====================
/**
 * 场景创建接口 - 定义统一的场景创建接口
 * 适配器模式：将不同场景的创建方法适配到统一接口
 */
class ISceneCreator {
public:
    virtual ~ISceneCreator() = default;
    
    /**
     * 创建场景
     * @param params 场景参数（使用 ValueMap 支持不同类型的参数）
     * @return 创建的场景，失败返回 nullptr
     */
    virtual Scene* createScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) = 0;
    
    /**
     * 获取场景类型名称
     */
    virtual std::string getSceneType() const = 0;
    
    /**
     * 预加载场景资源（可选，用于优化）
     */
    virtual void preloadResources() {}
    
    /**
     * 检查场景是否可以创建
     */
    virtual bool canCreateScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) const {
        return true;
    }
};

// ==================== 适配器模式：开场场景适配器 ====================
/**
 * 开场场景适配器 - 适配 valleybegin::createvalleybeginScene()
 */
class ValleyBeginSceneAdapter : public ISceneCreator {
public:
    Scene* createScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) override;
    std::string getSceneType() const override { return "ValleyBegin"; }
};

// ==================== 适配器模式：菜单场景适配器 ====================
/**
 * 菜单场景适配器 - 适配 menu::createmenuScene()
 */
class MenuSceneAdapter : public ISceneCreator {
public:
    Scene* createScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) override;
    std::string getSceneType() const override { return "Menu"; }
};

// ==================== 适配器模式：农场场景适配器 ====================
/**
 * 农场场景适配器 - 适配 outside::createSceneWithMapIndex(int mapIndex)
 */
class FarmSceneAdapter : public ISceneCreator {
public:
    Scene* createScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) override;
    std::string getSceneType() const override { return "Farm"; }
    
    bool canCreateScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) const override;
};

// ==================== 适配器模式：房屋场景适配器 ====================
/**
 * 房屋场景适配器 - 适配 intovalley::createintovalleyScene()
 */
class HouseSceneAdapter : public ISceneCreator {
public:
    Scene* createScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) override;
    std::string getSceneType() const override { return "House"; }
};

// ==================== 适配器模式：其他区域场景适配器 ====================
/**
 * 其他区域场景适配器 - 适配 othersence::createothersenceScene()
 */
class OtherAreaSceneAdapter : public ISceneCreator {
public:
    Scene* createScene(const cocos2d::ValueMap& params = cocos2d::ValueMap()) override;
    std::string getSceneType() const override { return "OtherArea"; }
};

// ==================== 适配器模式：场景适配器管理器 ====================
/**
 * 场景适配器管理器 - 管理所有场景适配器，提供统一访问接口
 * 使用适配器模式解耦 GameSceneFacade 与具体场景类
 */
class SceneAdapterManager {
private:
    std::map<std::string, ISceneCreator*> adapters;
    
    SceneAdapterManager();
    ~SceneAdapterManager();
    
public:
    static SceneAdapterManager* getInstance();
    
    // 注册场景适配器
    void registerAdapter(const std::string& sceneType, ISceneCreator* adapter);
    
    // 获取场景适配器
    ISceneCreator* getAdapter(const std::string& sceneType);
    
    // 创建场景（统一接口）
    Scene* createScene(const std::string& sceneType, const cocos2d::ValueMap& params = cocos2d::ValueMap());
    
    // 预加载场景资源
    void preloadSceneResources(const std::string& sceneType);
    
    // 检查场景是否可以创建
    bool canCreateScene(const std::string& sceneType, const cocos2d::ValueMap& params = cocos2d::ValueMap());
};

#endif // __SCENE_ADAPTER_H__

