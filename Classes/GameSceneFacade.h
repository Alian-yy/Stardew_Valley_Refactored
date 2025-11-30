/****************************************************************************
 * 
 * Refactored with Facade Pattern + Adapter Pattern
 * GameSceneFacade.h
 * 
 ****************************************************************************/

#ifndef _GAMESCENEFACADE_H_
#define _GAMESCENEFACADE_H_

#include "cocos2d.h"
// ==================== Adapter Pattern: Remove direct dependencies, use adapter instead ====================
// No longer directly includes specific scene classes, achieving decoupling
#include "SceneAdapter.h"

USING_NS_CC;

// ==================== Facade Pattern: New GameSceneFacade ====================
// ==================== Adapter Pattern: Create scenes through adapter, achieving decoupling ====================
/**
 * GameSceneFacade - Scene management facade class
 * Provides a unified interface for creating and switching scenes, hiding the complexity of Director interactions
 * 
 * Using Adapter Pattern for decoupling:
 * - No longer directly depends on specific scene classes (valleybegin, menu, outside, etc.)
 * - Creates scenes uniformly through SceneAdapterManager
 * - Adding new scenes in the future only requires adding new adapters, no need to modify Facade
 */
class GameSceneFacade
{
public:
    // ==================== Facade Pattern: New runWithBeginScene ====================
   
    // Starts the game, running the beginning scene
    
    static void runWithBeginScene();
    
    // ==================== Facade Pattern: New showMenuScene ====================
    // Switches from the beginning scene to the menu scene (with transition animation)
    static void showMenuScene();
    
    // ==================== Facade Pattern: New enterFarmScene ====================
    /**
     * Enters the farm scene from the menu scene
     * @param mapIndex Map index
     */
    static void enterFarmScene(int mapIndex);

    // ==================== Facade Pattern: New enterHouseScene ====================
    // Enters the house scene from the farm scene
    static void enterHouseScene();
    
    // ==================== Facade Pattern: New enterOtherAreaScene ====================
    // Enters another area scene from the farm scene
    static void enterOtherAreaScene();
    
    // ==================== Facade Pattern: New returnToPreviousScene ====================
    // Returns to the previous scene from a sub-scene (house/other area)
    static void returnToPreviousScene();
    
private:
    // ==================== Adapter Pattern: Use adapter manager ====================
    static SceneAdapterManager* getAdapterManager();
};

#endif // !_GAMESCENEFACADE_H_
