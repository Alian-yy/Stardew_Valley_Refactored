/****************************************************************************
 *
 * 使用工厂模式重构后的代码
 *
 ****************************************************************************/
#ifndef __CROP_H__
#define __CROP_H__

#include "outside.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "menu.h"
#include "characterAciton.h"


USING_NS_CC;

enum class State {
    seed,
    growing,
    matured,
    harvested,
    dead
};

class Crop :public Sprite {
protected:
    State state;
    double pregrowthTime;
    double growthTime;
    double matureTime;
    bool watered;
    // 按键事件处理
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {};
public:
    virtual bool init(const std::string& filename);
    static Crop* create();         
    Crop();
    ~Crop();
    void update(float delta);

    // 获取作物的状态
    State getState() const;

    // 收获作物
    void harvest();

    // 重置作物状态
    void resetState();

    // 供工厂初始化
    void setInitialTexture(const std::string& file) { this->setTexture(file); }
    void setMatureTime(double t) { matureTime = t; }
};

// ==================== 工厂模式：新增CropFactory ====================
class CropFactory {
public:
    static Crop* createCrop(const std::string& cropType);
    // 配置作物属性（用于对象池复用时初始化不同类型作物）
    static void configureCrop(Crop* crop, const std::string& cropType);
};

#endif // __CROP_H__