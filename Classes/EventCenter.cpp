/********************************************************************************
 *
 *   Refactored with Observer Pattern:add EventCenter.cpp
 *
 ********************************************************************************/

// EventCenter.cpp
#include "EventCenter.h"

EventCenter* EventCenter::_instance = nullptr;

EventCenter* EventCenter::getInstance()
{
    if (!_instance) {
        _instance = new (std::nothrow) EventCenter();
        if (_instance && _instance->init()) {
            _instance->retain(); // 避免被 Cocos2d-X 自动释放
        } else {
            CC_SAFE_DELETE(_instance);
        }
    }
    return _instance;
}

EventCenter::EventCenter()
{
}

EventCenter::~EventCenter()
{
    _observers.clear();
}

bool EventCenter::init()
{
    return true;
}

void EventCenter::attach(Observer* observer)
{
    if (observer && !_observers.contains(observer)) {
        _observers.pushBack(observer);
    }
}

void EventCenter::detach(Observer* observer)
{
    if (observer) {
        _observers.eraseObject(observer);
    }
}

void EventCenter::publish(const EventData& event)
{
    // 简单遍历通知所有观察者
    for (auto obs : _observers) {
        if (obs) {
            obs->onNotify(event);
        }
    }
}

void EventCenter::publish(EventType type, void* sender, const cocos2d::Value& extra)
{
    EventData e(type, sender, extra);
    publish(e);
}
