/********************************************************************************
 *
 *    Refactored with Observer Pattern:add EventData.h
 *
 ********************************************************************************/


// EventData.h
#ifndef __EVENT_DATA_H__
#define __EVENT_DATA_H__

#include "cocos2d.h"
#include "EventType.h"

// Simple event payload: event type + event sender + optional extra data
struct EventData {
    EventType type;
    void* sender;          // Pointer to the event sender (e.g., Crop* / Outside*)
    cocos2d::Value extra;  // Additional data, such as a formatted time string

    EventData(EventType t, void* s, const cocos2d::Value& e = cocos2d::Value())
        : type(t), sender(s), extra(e) {}
};

#endif // __EVENT_DATA_H__

