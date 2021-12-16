/** @file Levels.h
 *  @brief Header file for player levels.
 *
 * This program is responsible handling level entities. These include displaying
 * messages at the start, game over, and handling player damage.
 *
 *  @author Michael Martinez
 *  @bug No known bugs.
 */
#ifndef _LEVEL_H
#define _LEVEL_H
#include "InputManager.h"
#include "PlayBG.h"
#include "Player.h"

/**
 * @brief The Level class
 * @author Michael Martinez
 *
 * Level's class inheriting from GameEntity which is used to program in game
 * levels menu.
 */
class Level : public GameEntity {
 public:
  /** @brief enum for level states
   *
   * Used to create different states for levels.
   *
   */
  enum LEVEL_STATES { running, finished, gameover };

 private:
  /** @brief Timer variable
   *
   * Used to keep track of time between resets.
   *
   */
  Timer* mTimer;

  /** @brief Playscreen background variable
   *
   * Used to set the stage and lives for level.
   *
   */
  PlayBG* mPlayBG;

  /** @brief Stage variable
   *
   * Used for the 'HandleStartLabels' function.
   *
   */
  int mStage;

  /** @brief Stage started variabl
   *
   * Checks whether or not stage has started.
   *
   */
  bool mStageStarted;

  /** @brief Label timer variable
   *
   * Used as a comparison to render the mReadyLabel texture.
   *
   */
  float mLabelTimer;

  /** @brief Label on screen variable
   *
   * Used as a comparison to render the mReadyLabel texture.
   *
   */
  float mStageLabelOnScreen;

  /** @brief Label off screen variable
   *
   * Used as a comparison to render the mReadyLabel texture.
   *
   */
  float mStageLabelOffScreen;

  /** @brief Ready label texture
   *
   * Creates a ready label texture.
   *
   */
  Texture* mReadyLabel;

  /** @brief Ready label on screen variable
   *
   * Used as a comparison to render the mReadyLabel texture.
   *
   */
  float mReadyLabelOnScreen;

  /** @brief Ready label off screen
   *
   * Used as a comparison to render the mReadyLabel texture.
   *
   */
  float mReadyLabelOffScreen;

  Player* mPlayer;

  /** @brief Player hit variable
   *
   * Checks whether player is hit or not.
   *
   */
  bool mPlayerHit;

  /** @brief Player respawn delay variable
   *
   * Time it delays for player to respawn.
   *
   */
  float mPlayerRespawnDelay;

  /** @brief Respawn timer variable
   *
   * Timer for respawn delay
   *
   */
  float mPlayerRespawnTimer;

  /** @brief respawn label on screen
   *
   * Used to render ready label.
   *
   */
  float mPlayerRespawnLabelOnScreen;

  /** @brief Game over texture
   *
   * Creates game over texture for whenever player lives reaches zero.
   *
   */
  Texture* mGameOverLabel;

  /** @brief game over variable
   *
   * Checks if whether level is game over.
   *
   */
  bool mGameOver;

  /** @brief Game over delay variable
   *
   * Variable used to delay game over screen.
   *
   */
  float mGameOverDelay;

  /** @brief Game over timer variable
   *
   * Timer used to count to game over delay.
   *
   */
  float mGameOverTimer;

  /** @brief Game over label screen variable
   *
   * Used to compare with timer to redner game over.
   *
   */
  float mGameOverLabelOnScreen;

  /** @brief Current state variable
   *
   * Used to assign different level states for the game.
   *
   */
  LEVEL_STATES mCurrentState;

 private:
  /** @brief Start stage function
   *
   * Sets stage started to true.
   *
   *  @return void
   */
  void StartStage() noexcept;
  /** @brief Handle start label function
   *
   * Used to handle start label for level.
   *
   *  @return void
   */
  void HandleStartLabels();

  /** @brief Handle collision function
   *
   * Used to handle player damage, as well handle keyboard input to die
   * manually.
   *
   *  @return void
   */
  void HandleCollisions();

  /** @brief Handle player death function
   *
   * Used to handle player lives as well as handling game over.
   *
   *  @return void
   */
  void HandlePlayerDeath();

 public:
  /** @brief Constructor
   *
   * Creates textures, handles all timers and delays, and sets the current state
   * of the stage to running.
   *
   *  @param stage, playBG, player
   */
  // LO1b
  Level(int stage, PlayBG* playBG, Player* player);

  /** @brief Deconstructor
   *
   * Freeing all entities
   *
   */
  virtual ~Level();

  /** @brief State function
   *
   * Used to return current state.
   *
   */
  LEVEL_STATES State() noexcept;

  /** @brief Update
   *
   * Updates player damage, stage labels, and updates currentstate to finish
   * level.
   *
   *  @return void
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
