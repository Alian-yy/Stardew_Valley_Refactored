// TimePublisher.cpp
#include "TimePublisher.h"
#include "GameTimeSystem.h"
#include "EventCenter.h"
#include "EventType.h"
#include <ctime>

USING_NS_CC;

TimePublisher* s_timePublisher = nullptr;

TimePublisher* TimePublisher::getInstance()
{
    if (!s_timePublisher) {
        s_timePublisher = new (std::nothrow) TimePublisher();
        if (s_timePublisher)
            s_timePublisher->retain();
    }
    return s_timePublisher;
}

TimePublisher::TimePublisher()
: _running(false), _interval(1.0f)
{
}

TimePublisher::~TimePublisher()
{
    stop();
    if (s_timePublisher == this) s_timePublisher = nullptr;
}

void TimePublisher::start(float interval)
{
    if (_running) return;
    _running = true;
    _interval = interval;
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(TimePublisher::tick), this, _interval, false);
}

void TimePublisher::stop()
{
    if (!_running) return;
    _running = false;
    Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(TimePublisher::tick), this);
}

void TimePublisher::tick(float dt)
{
    // 使用 GameTimeSystem 作为时间来源（返回秒数自游戏开始）
    long elapsedSeconds = GameTimeSystem::getInstance()->getElapsedTime();

    // 将现实时间转换为游戏内时间（每0.7秒等于游戏内的一分钟）
    int inGameMinutes = static_cast<int>(elapsedSeconds / 0.7f);

    // 获取当前真实时间并加上游戏内经过的分钟数
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);
    if (timeinfo) {
        // 正确地将分钟数累加并规范化
        timeinfo->tm_min += inGameMinutes;
        mktime(timeinfo);

        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%H:%M", timeinfo);

        // 发布事件
        cocos2d::Value timeStr(buffer);
        EventCenter::getInstance()->publish(EventType::MinuteChanged, nullptr, timeStr);
    }
}
