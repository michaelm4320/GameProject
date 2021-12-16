/** @file ScreenManager.h
 *  @brief Header file for ScreenManager
 *
 * This program is responsible handling all screen types for the game.
 *
 *  @author Michael Martinez
 *  @bug Title selection screen movement is being triggered throughout all the screen
 * types when it should only be affected within the start screen. This causes the menu selection
 * to be incorrect sometimes.
 */
#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H
#include "Controls.h"
#include "PlayScreen.h"
#include "StartScreen.h"

/**
 * @brief The ScreenManager class
 * @author Michael Martinez
 *
 * ScreenManager class is used to handle create different screen types for the
 * game.
 *
 */
class ScreenManager {
 private:

  /** @brief enum for screens
   *
   * Used to create different types of screens for the game.
   *
   */
  enum SCREENS { start, play, controls };

  /** @brief Static instance variable
   *
   * Used within the Instance function to check if required to create a new screen manager.
   *
   */
  static ScreenManager* sInstance;

  /** @brief Input variable
   *
   * Used to handle keyboard inputs.
   *
   */
  InputManager* mInput;

  /** @brief Start screen variable
   *
   * Used to create the start screen for the game.
   *
   */
  StartScreen* mStartScreen;

  /** @brief Play screen variable
   *
   * Used to create the play screen for the game.
   *
   */
  PlayScreen* mPlayScreen;

  /** @brief Controls screen variable
   *
   * Used to create the controls screen for the game.
   *
   */
  Controls* mControls;

  /** @brief Current screen variable
   *
   * Used as a way to tell the program which screen is the game currently in.
   *
   */
  SCREENS mCurrentScreen;

 public:
  /** @brief Instance function
   *
   * Used to create and return a screen manager if the static instance is null.
   *
   */
  static ScreenManager* Instance();

  /** @brief Release function
   *
   * Frees the static instance.
   *
   *  @return void
   */
  static void Release() noexcept;

  /** @brief mode variable
   *
   * Used to keep track of the current mode for title screen selection.
   *
   */
  int mode = 1;

  /** @brief Update function
   *
   * Updating the type of screen that displays to the player.
   *
   *  @return void
   */
  void Update();

  /** @brief Render function
   *
   * Renders all screen types.
   *
   *  @return void
   */
  void Render();

 private:

  /** @brief Constructor
   *
   * Creating new screen types from enum.
   *
   */
  ScreenManager();

    /** @brief Deconstructor
   *
   * Freeing all entities.
   *
   */
  ~ScreenManager();
};

#endif
