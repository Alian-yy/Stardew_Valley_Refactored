/********************************************************************************
 *
  *   使用观察者模式重构后新增的EventType.h
 *
 ********************************************************************************/

// EventType.h
#ifndef __EVENT_TYPE_H__
#define __EVENT_TYPE_H__

// 根据 valley-main 现有事件整理出的事件类型：
// - 作物成长阶段变化（发芽 / 成长 / 成熟 / 枯萎）
// - 作物被收获
// - 游戏时间更新（分钟标签变化）
enum class EventType {
    MinuteChanged,   // outside::updateTime 中每次更新时间
    CropGerminated,  // Crop: seed -> growing
    CropGrowing,     // Crop: growing 中间过程（可选事件）
    CropMatured,     // Crop: growing -> matured
    CropHarvested,   // 作物被系统或玩家收获
    CropDead         // 作物因未浇水死亡
};

#endif // __EVENT_TYPE_H__
