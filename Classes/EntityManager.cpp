#include "EntityManager.h"
#include "Animal.h"
#include "Plantingcrops.h"
#include "cocos2d.h"

using namespace cocos2d;

USING_NS_CC;

EntityManager* EntityManager::create(Node* parent) {
    EntityManager* em = new (std::nothrow) EntityManager();
    if (em && em->init(parent)) {
        em->autorelease();
        return em;
    }
    CC_SAFE_DELETE(em);
    return nullptr;
}

bool EntityManager::init(Node* parent) {
    if (!Node::init()) return false;
    _parent = parent;
    return true;
}

void EntityManager::spawnSheep(int count, const std::string& texture) {
    for (int i = 0; i < count; ++i) {
        auto sheep = Sheep::create(texture);
        if (!sheep) {
            CCLOG("EntityManager: failed to create sheep");
            continue;
        }
        // Place sheep randomly near origin if no explicit position provided
        float rx = 300 + CCRANDOM_0_1() * 800;
        float ry = 300 + CCRANDOM_0_1() * 800;
        sheep->setPosition(Vec2(rx, ry));
        _parent->addChild(sheep);
        _entities.push_back(sheep);
    }
}

void EntityManager::spawnCow(const std::string& texture, float scale) {
    auto cow = Cow::create(texture);
    if (!cow) {
        CCLOG("EntityManager: failed to create cow");
        return;
    }
    cow->setScale(scale);
    // default random placement
    cow->setPosition(Vec2(500 + CCRANDOM_0_1() * 1000, 400 + CCRANDOM_0_1() * 800));
    _parent->addChild(cow);
    _entities.push_back(cow);
}

void EntityManager::spawnParrot(const std::string& texture, float scale) {
    auto parrot = Parrot::create(texture);
    if (!parrot) {
        CCLOG("EntityManager: failed to create parrot");
        return;
    }
    parrot->setScale(scale);
    parrot->setPosition(Vec2(600 + CCRANDOM_0_1() * 1200, 600 + CCRANDOM_0_1() * 900));
    _parent->addChild(parrot);
    _entities.push_back(parrot);
}

void EntityManager::spawnSheepAt(const Vec2& pos, const std::string& texture) {
    auto sheep = Sheep::create(texture);
    if (!sheep) return;
    sheep->setPosition(pos);
    _parent->addChild(sheep);
    _entities.push_back(sheep);
}

void EntityManager::spawnCowAt(const Vec2& pos, const std::string& texture, float scale) {
    auto cow = Cow::create(texture);
    if (!cow) return;
    cow->setScale(scale);
    cow->setPosition(pos);
    _parent->addChild(cow);
    _entities.push_back(cow);
}

void EntityManager::spawnParrotAt(const Vec2& pos, const std::string& texture, float scale) {
    auto parrot = Parrot::create(texture);
    if (!parrot) return;
    parrot->setScale(scale);
    parrot->setPosition(pos);
    _parent->addChild(parrot);
    _entities.push_back(parrot);
}

void EntityManager::spawnFromMap(TMXTiledMap* tiledMap, const std::string& groupName) {
    if (!tiledMap) return;
    auto objects = tiledMap->getObjectGroup(groupName);
    if (!objects) {
        CCLOG("EntityManager::spawnFromMap - object group '%s' not found", groupName.c_str());
        return;
    }

    auto vec = objects->getObjects();
    for (auto& v : vec) {
        auto dict = v.asValueMap();
        std::string type = "";
        if (dict.find("type") != dict.end()) type = dict["type"].asString();
        if (type.empty() && dict.find("entity") != dict.end()) type = dict["entity"].asString();
        // try name as fallback
        if (type.empty() && dict.find("name") != dict.end()) type = dict["name"].asString();

        float x = 0.0f, y = 0.0f;
        if (dict.find("x") != dict.end()) x = dict["x"].asFloat();
        if (dict.find("y") != dict.end()) y = dict["y"].asFloat();

        Vec2 pos = Vec2(x, y);

        if (type == "sheep" || type == "Sheep") {
            spawnSheepAt(pos);
        } else if (type == "cow" || type == "Cow") {
            spawnCowAt(pos);
        } else if (type == "parrot" || type == "Parrot") {
            spawnParrotAt(pos);
        } else if (type == "crop" || type == "Crop") {
            // Place a planting crop at the position
            auto crop = Plantingcrops::create();
            if (crop) {
                crop->setPosition(pos);
                _parent->addChild(crop);
                _entities.push_back(crop);
            }
        } else {
            // unknown type: skip or handle later
        }
    }
}

void EntityManager::spawnCrops() {
    // Placeholder: move Plantingcrops creation here when needed
    auto crop = Plantingcrops::create();
    if (crop) {
        _parent->addChild(crop);
        _entities.push_back(crop);
    }
}

void EntityManager::clearAll() {
    for (auto e : _entities) {
        if (e && e->getParent()) {
            e->removeFromParentAndCleanup(true);
        }
    }
    _entities.clear();
}
