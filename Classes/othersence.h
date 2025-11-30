#ifndef _OTHERSENCE_H
#define _OTHERSENCE_H
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "outside.h"

class CharacterWithTools;

class othersence : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createothersenceScene();
    virtual bool init();

    CREATE_FUNC(othersence);
    //进入下一个游戏界面
    void setViewPointCenter(Point position, cocos2d::TMXTiledMap* tiledMap);
  
private:
    CharacterWithTools* characteraction;
};
#endif // !_INTOVALLEY.H

