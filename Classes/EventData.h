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

// 简单事件载体：事件类型 + 事件来源 + 可选附加信息
struct EventData {
    EventType type;
    void* sender;          // 事件发起者指针（如 Crop* / outside*）
    cocos2d::Value extra;  // 附加信息，例如时间字符串

    EventData(EventType t, void* s, const cocos2d::Value& e = cocos2d::Value())
        : type(t), sender(s), extra(e) {}
};

#endif // __EVENT_DATA_H__
