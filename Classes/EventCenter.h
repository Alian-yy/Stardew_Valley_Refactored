// EventCenter.h
#ifndef __EVENT_CENTER_H__
#define __EVENT_CENTER_H__

#include "cocos2d.h"
#include "Observer.h"

/********************************************************************************
 *
 *   使用观察者模式重构后新增的EventCenter.h
 *
 ********************************************************************************/


// 统一事件中心（单例）：负责维护观察者列表并分发事件
class EventCenter : public cocos2d::Ref {
public:
    // 获取全局唯一实例
    static EventCenter* getInstance();

    // 注册 / 取消注册 观察者
    void attach(Observer* observer);
    void detach(Observer* observer);

    // 发布事件（两种重载）
    void publish(const EventData& event);
    void publish(EventType type, void* sender,
                 const cocos2d::Value& extra = cocos2d::Value());

private:
    EventCenter();
    virtual ~EventCenter();

    bool init();

    static EventCenter* _instance;

    // 使用 cocos2d::Vector 管理指针，和引擎内存模型一致
    cocos2d::Vector<Observer*> _observers;
};

#endif // __EVENT_CENTER_H__
