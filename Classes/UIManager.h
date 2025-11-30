// UIManager.h
#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Observer.h"

class UIManager : public Observer {
public:
    UIManager(cocos2d::Layer* parent);
    virtual ~UIManager();

    // Observer interface
    virtual void onNotify(const EventData& event) override;

    // Expose for outside if needed
    cocos2d::Label* getTimeLabel() const { return _timeLabel; }

    // Personal interface controls
    void showPersonalInterface(const cocos2d::Vec2& characterPosition);
    void hidePersonalInterface();
    void selectImage(int index);

    // New window dialog used by personal interface
    void showNewWindow(int clickedIndex);

    // NPC dialog display (outside or NPCManager should call this)
    void showNPCDialog(const std::string& dialogTexture, const cocos2d::Vec2& position, float duration = 3.0f);

    // Fishing UI
    void toggleFishing();
    void showFishing();
    void hideFishing();

private:
    // 私有辅助方法
    void showVerticalButtons();
    void showVerticalButtons2();
    void removeVerticalButtons();
    cocos2d::Layer* _parent;
    cocos2d::Label* _dayLabel;
    cocos2d::Label* _timeLabel;
    // personal interface state
    cocos2d::Layer* _personalInterfaceLayer;
    cocos2d::Sprite* _menuWindow;
    cocos2d::MenuItemImage* _closeButton;
    bool _isPersonalInterfaceVisible;
    int _currentImageIndex;
    int _clickedButtonIndex;
    std::map<int, int> _buttonClickCounts;
    // fishing UI
    cocos2d::Layer* _fishingLayer;
    cocos2d::ui::ImageView* _fishImage;
    cocos2d::Sprite* _spriteFish;
    cocos2d::Sprite* _fishman;
    bool _isFishingVisible;
};

#endif // __UI_MANAGER_H__
