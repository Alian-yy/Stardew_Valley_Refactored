#pragma once

#include "cocos2d.h"
#include <vector>

struct NPCSpec; // forward

class EntityManager : public cocos2d::Node {
public:
    static EntityManager* create(cocos2d::Node* parent);
    bool init(cocos2d::Node* parent);

    // animals
    void spawnSheep(int count, const std::string& texture = "animal/Sheep1.png");
    void spawnCow(const std::string& texture = "animal/Cow1.png", float scale = 3.0f);
    void spawnParrot(const std::string& texture = "animal/Parrot1.png", float scale = 3.0f);
    // spawn at specific position
    void spawnSheepAt(const cocos2d::Vec2& pos, const std::string& texture = "animal/Sheep1.png");
    void spawnCowAt(const cocos2d::Vec2& pos, const std::string& texture = "animal/Cow1.png", float scale = 3.0f);
    void spawnParrotAt(const cocos2d::Vec2& pos, const std::string& texture = "animal/Parrot1.png", float scale = 3.0f);

    // Spawn entities based on TMX object group (expects objects to have property 'type' or 'entity')
    void spawnFromMap(cocos2d::TMXTiledMap* tiledMap, const std::string& groupName = "objects");

    // crops placeholder
    void spawnCrops();

    // cleanup
    void clearAll();

private:
    cocos2d::Node* _parent;
    std::vector<cocos2d::Node*> _entities;
};
