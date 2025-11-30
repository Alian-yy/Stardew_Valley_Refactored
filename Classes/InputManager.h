// InputManager.h
#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "cocos2d.h"
#include <functional>

class InputManager : public cocos2d::Ref {
public:
    // toggleUICallback: called when user presses the UI toggle key (E)
    InputManager(cocos2d::Node* owner, std::function<void()> toggleUICallback);
    virtual ~InputManager();

    void enable();
    void disable();

private:
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    cocos2d::Node* _owner;
    cocos2d::EventListenerKeyboard* _keyboardListener;
    std::function<void()> _toggleUICallback;
};

#endif // __INPUT_MANAGER_H__
