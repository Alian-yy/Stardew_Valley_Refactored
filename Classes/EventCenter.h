/********************************************************************************
 *
 *    Refactored with Observer Pattern:add EventCenter.h
 *
 ********************************************************************************/

// EventCenter.h
#ifndef __EVENT_CENTER_H__
#define __EVENT_CENTER_H__

#include "cocos2d.h"
#include "Observer.h"



// Centralized event dispatcher (singleton): maintains the observer list and distributes events
class EventCenter : public cocos2d::Ref {
public:
    // Retrieve the global unique instance
    static EventCenter* getInstance();

    // Register / unregister observers
    void attach(Observer* observer);
    void detach(Observer* observer);

    // Publish events (two overloads)
    void publish(const EventData& event);
    void publish(EventType type, void* sender,
                 const cocos2d::Value& extra = cocos2d::Value());

private:
    EventCenter();
    virtual ~EventCenter();

    bool init();

    static EventCenter* _instance;

    // Manage pointers using cocos2d::Vector to align with the engine's memory model
    cocos2d::Vector<Observer*> _observers;
};

#endif // __EVENT_CENTER_H__

