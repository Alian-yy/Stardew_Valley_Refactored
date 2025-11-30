/****************************************************************************
 * 
 * GameSceneFacade.h refactored using Facade Pattern + Adapter Pattern
 * 
 ****************************************************************************/

#ifndef _GAMESCENEFACADE_H_
#define _GAMESCENEFACADE_H_

#include "cocos2d.h"

// ==================== Adapter Pattern: Remove direct dependencies ====================
#include "SceneAdapter.h"

USING_NS_CC;

// ==================== Facade Pattern: GameSceneFacade ====================
// ==================== Adapter Pattern: Scene creation via adapters ====================
class GameSceneFacade
{
public:
    // ==================== Facade: runWithBeginScene ====================
    // Start the game and run the opening scene
    static void runWithBeginScene();
    
    // ==================== Facade: showMenuScene ====================
    // Switch from the opening scene to the menu scene (with transition animation)
    static void showMenuScene();
    
    // ==================== Facade: enterFarmScene ====================
    // Enter the farm scene from the menu scene
    static void enterFarmScene(int mapIndex);

    // ==================== Facade: enterHouseScene ====================
    // Enter the house scene from the farm scene
    static void enterHouseScene();
    
    // ==================== Facade: enterOtherAreaScene ====================
    // Enter the other-area scene from the farm scene
    static void enterOtherAreaScene();
    
    // ==================== Facade: returnToPreviousScene ====================
    // Return from a child scene (house/other area) to the previous scene
    static void returnToPreviousScene();
    
private:
    // ==================== Adapter Pattern: Use the adapter manager ====================
    static SceneAdapterManager* getAdapterManager();
};

#endif // !_GAMESCENEFACADE_H_
