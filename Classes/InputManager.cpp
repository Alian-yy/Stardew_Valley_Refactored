// InputManager.cpp
#include "InputManager.h"

USING_NS_CC;

InputManager::InputManager(Node* owner, std::function<void()> toggleUICallback)
    : _owner(owner), _keyboardListener(nullptr), _toggleUICallback(toggleUICallback)
{

}

InputManager::~InputManager()
{
    disable();
}

void InputManager::enable()
{
    if (_keyboardListener) return;
    _keyboardListener = EventListenerKeyboard::create();
    _keyboardListener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
    if (_owner && _keyboardListener) {
        _owner->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_keyboardListener, _owner);
    }
}

void InputManager::disable()
{
    if (!_keyboardListener) return;
    if (_owner && _keyboardListener) {
        _owner->getEventDispatcher()->removeEventListener(_keyboardListener);
    }
    _keyboardListener = nullptr;
}

void InputManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_E) {
        if (_toggleUICallback) {
            _toggleUICallback();
        }
    }
}
