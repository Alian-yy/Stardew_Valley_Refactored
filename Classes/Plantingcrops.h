/****************************************************************************
 *
 * Refactored with Factory Method design pattern.
 *
 ****************************************************************************/
#ifndef __CROP_H__
#define __CROP_H__

#include "outside.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "menu.h"


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
    // Key event handling
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {};
public:
    virtual bool init(const std::string& filename);
    static Crop* create();
    Crop();
    ~Crop();
    void update(float delta);

    // Get crop state
    State getState() const;

    // Harvest crop
    void harvest();

    // Reset crop state
    void resetState();

    // For factory initialization
    void setInitialTexture(const std::string& file) { this->setTexture(file); }
    void setMatureTime(double t) { matureTime = t; }
};

// ==================== Factory Pattern: Add CropFactory ====================
class CropFactory {
public:
    static Crop* createCrop(const std::string& cropType);
    // Configure crop properties (for initializing different crop types when reusing object pool)
    static void configureCrop(Crop* crop, const std::string& cropType);
};

#endif // __CROP_H__