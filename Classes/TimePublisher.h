// TimePublisher.h
#ifndef __TIME_PUBLISHER_H__
#define __TIME_PUBLISHER_H__

#include "cocos2d.h"

class TimePublisher : public cocos2d::Ref {
public:
    static TimePublisher* getInstance();
    void start(float interval = 1.0f);
    void stop();

private:
    TimePublisher();
    virtual ~TimePublisher();

    void tick(float dt);
    bool _running;
    float _interval;
};

#endif // __TIME_PUBLISHER_H__
