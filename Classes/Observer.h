/********************************************************************************
 *
 *   Refactored with Observer Pattern:add Observer.h
 *
 ********************************************************************************/

// Observer.h
#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "EventData.h"

// Abstract observer interface; any class that needs to listen to events must implement this
class Observer {
public:
    virtual ~Observer() {}
    virtual void onNotify(const EventData& event) = 0;
};

#endif // __OBSERVER_H__
