/********************************************************************************
 *
 *   Refactored with Observer Pattern:add EventType.h
 *
 ********************************************************************************/

// EventType.h
#ifndef __EVENT_TYPE_H__
#define __EVENT_TYPE_H__

// Event types derived from the existing valley-main event system:
// - Crop growth stage transitions (germination / growing / matured / dead)
// - Crop being harvested
// - Game time updates (minute label changes)
enum class EventType {
    MinuteChanged,   // Triggered each time outside::updateTime updates the time
    CropGerminated,  // Crop: seed -> growing
    CropGrowing,     // Crop: intermediate growing stage (optional event)
    CropMatured,     // Crop: growing -> matured
    CropHarvested,   // Crop harvested by system or player
    CropDead         // Crop dies due to lack of watering
};

#endif // __EVENT_TYPE_H__

