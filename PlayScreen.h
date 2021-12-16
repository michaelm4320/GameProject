/** @file PlayScreen.h
 *  @brief Header file for PlayScreen
 *
 * This program is responsible handling creating play screens for levels.
 *
 *  @author Michael Martinez
 *  @bug No known bugs.
 */
#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H
#include "InputManager.h"
#include "Level.h"
#include "PlayBG.h"
#include "Player.h"
#include "StartScreen.h"

/**
 * @brief The PlayScreen class
 * @author Michael Martinez
 *
 * PlayScreen class inheriting from GameEntity which is used to handle player
 * screen time for levels.
 *
 */
class PlayScreen : public GameEntity {
 private:
  /** @brief Timer variable
   *
   * Used to keep track of time between resets.
   *
   */
  Timer* mTimer;

  /** @brief Input variable
   *
   * Used to handle keyboard inputs.
   *
   */
  InputManager* mInput;

  /** @brief Audio variable
   *
   * Used to add audio for the game.
   *
   */
  AudioManager* mAudio;

  /** @brief Playscreen background variable
   *
   * Used to create a playscreen background for levels.
   *
   */
  PlayBG* mPlayBG;

  /** @brief Start label texture
   *
   * Used to create texture for start label.
   *
   */
  Texture* mStartLabel;

  /** @brief Start level timer variable
   *
   * Used to assist with delaying starting the level.
   *
   */
  float mLevelStartTimer = 0.0;

  /** @brief Start delay variable
   *
   * Delays the start of the the level.
   *
   */
  float mLevelStartDelay;

  /** @brief Game started variable
   *
   * Used to check whether the game has started or not.
   *
   */
  bool mGameStarted = false;

  /** @brief Level variable
   *
   * Used to create the player, current stage, and background for the level.
   *
   */
  Level* mLevel;

  /** @brief Level started variable
   *
   * Used to check whether the level has started.
   *
   */
  bool mLevelStarted;

  /** @brief Current stage variable.
   *
   * Used to keep track of the current level player is in.
   *
   */
  int mCurrentStage = 0;

  /** @brief Player variable
   *
   * Used to create the player for the level.
   *
   */
  Player* mPlayer;

 private:
  /** @brief Starting next level function
   *
   * Function used to start the next level for the player.
   *
   *  @return void
   */
  void StartNextLevel();

 public:
  /** @brief Constructor
   *
   * Creating textures as well as instances for timer, audio, and input.
   *
   */
  PlayScreen();

  /** @brief Deconstructor
   *
   * Freeing all entities
   *
   */
  virtual ~PlayScreen();

  /** @brief New game function
   *
   * Starts new game
   *
   *  @return void
   */
  void StartNewGame();

  /** @brief Game over variable
   *
   * Used to check if game over is true or false.
   *
   *  @return bool
   */
  bool GameOver() noexcept;

  /** @brief Update function
   *
   * Used to update the screen into the playscreen after selecting new game.
   *
   *  @return voidE
   */
  void Update();

  /** @brief Render function
   *
   * Renders all textures
   *
   *  @return void
   */
  void Render();
};

#endif
