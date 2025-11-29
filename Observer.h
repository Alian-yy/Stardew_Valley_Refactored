/********************************************************************************
 *
 *   使用观察者模式重构后新增的Observer.h
 *
 ********************************************************************************/

// Observer.h
#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "EventData.h"

// 观察者抽象接口，所有需要“监听事件”的类都要实现这个接口
class Observer {
public:
    virtual ~Observer() {}
    virtual void onNotify(const EventData& event) = 0;
};

#endif // __OBSERVER_H__
