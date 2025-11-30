// NPCManager.h
#ifndef __NPC_MANAGER_H__
#define __NPC_MANAGER_H__

#include "cocos2d.h"
#include <functional>
#include <vector>

struct NPCSpec {
    std::string normalTexture;
    std::string selectedTexture;
    cocos2d::Vec2 position;
    float scale = 1.0f;
    std::string dialogTexture;
    cocos2d::Vec2 dialogPosition;
    float proximityThreshold = 100.0f;
};

class NPCManager : public cocos2d::Ref {
public:
    // getPlayerPos: callback returning current player position
    // Added dialog callback: showDialog(dialogTexture, position, duration)
    NPCManager(cocos2d::Layer* parent, std::function<cocos2d::Vec2()> getPlayerPos,
               std::function<void(const std::string&, const cocos2d::Vec2&, float)> showDialogCallback);
    virtual ~NPCManager();

    void spawnNPC(const NPCSpec& spec);
    void clear();

private:
    cocos2d::Layer* _parent;
    std::function<cocos2d::Vec2()> _getPlayerPos;
    std::function<void(const std::string&, const cocos2d::Vec2&, float)> _showDialogCallback;
    std::vector<cocos2d::ui::Button*> _buttons;
};

#endif // __NPC_MANAGER_H__
