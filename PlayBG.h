/** @file PlayBG.h
 *  @brief Header file for player level background
 *
 * This program is responsible handling level backgrounds. These include
 * displaying the level's animated background, status HUD, and player lives.
 *
 *  @author Michael Martinez
 *  @bug No known bugs.
 */

#ifndef _PLAYHEALTH_H
#define _PLAYHEALTH_H
#include <gsl/util>
#include <vector>

#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "StartScreen.h"
#include "Timer.h"

/**
 * @brief The PlayBG class
 * @author Michael Martinez
 *
 * PlayBG class inheriting from GameEntity which is used to program textures for
 * level's animated background and status HUD
 *
 */
class PlayBG : public GameEntity {
 private:
  /** @brief Timer variable
   *
   * Used to keep track of time between resets.
   *
   */
  Timer* mTimer;

  /** @brief Audio variable
   *
   * Used to add audio for the game.
   *
   */
  AudioManager* mAudio;

  /** @brief Background texture
   *
   * Creating texture for background.
   *
   */
  Texture* mBackground;

  /** @brief Animated background texture
   *
   * Creating an animated background texture.
   *
   */
  AnimatedTexture* mAnimatedBackground;

  /** @brief Stage texture
   *
   * Creates platform texture for player and enemy movement.
   *
   */
  Texture* mStage;

  /** @brief Status texture
   *
   * Creates texture for status used to show lives and current stage level.
   *
   */
  Texture* mStatus;

  /** @brief Megaman's maximum texture lives
   *
   * Used to initialize maximum number of textures display at status HUD.
   *
   */
  static const int MAX_MM_TEXTURES = 2;

  /** @brief Lives variable
   *
   * Entity used with assistance with player lives texture.
   *
   */
  GameEntity* mLives;

  /** @brief Lives texture variable
   *
   * Texture used for player lives
   *
   */
  Texture* mLivesTextures[MAX_MM_TEXTURES];

  /** @brief Total lives function
   *
   * Total number of player lives
   *
   */
  int mTotalLives = 0;

  /** @brief Stage flags variable
   *
   * Used in conjunction with stage flags textures for displaying current level
   * on status HUD.
   *
   */
  GameEntity* mFlags;

  // LO7 An iterator is an object that points to some element in a range of
  // elements using specific operators, such as the dereference operator.
  /** @brief Flag texture
   *
   * Creating textures for stage flags.
   *
   */
  std::vector<Texture*> mFlagTextures;

  /** @brief Remaining levels variable
   *
   * Keeping track of remaining levels to render stage flags texture. Flag
   * generated depends on value.
   *
   */
  int mRemainingLevels = 0;

  /** @brief Flag offset variable
   *
   * Used for flag position.
   *
   */
  float mFlagXOffset = 0.0;

  /** @brief Flag timer variable
   *
   * Used to update flag using 'AddNextFlag' function.
   *
   */
  float mFlagTimer;

  /** @brief Flag interval variable
   *
   * Compares with flagtimer to decide to update flag.
   *
   */
  float mFlagInterval;

 private:
  /** @brief Clearing flags function
   *
   * Deletes flag textures.
   *
   *  @return void
   */
  void ClearFlags() noexcept;

  /** @brief Adding flag function
   *
   * Used to add stage flag textures.
   *
   *  @return void
   */
  void AddNextFlag();

  /** @brief Adding flag function
   *
   * Sets position for setting flag and plays a SFX when flag is set.
   *
   *  @param filename, width, value
   *  @return void
   */
  void AddFlag(std::string filename, float width, int value);

 public:
  /** @brief Constructor
   *
   * Creates the textures for the animated background, status HUD, and lives.
   *
   */
  PlayBG();

  /** @brief Deconstructor
   *
   * Freeing all entities
   *
   */
  virtual ~PlayBG();

  /** @brief Setting lives function
   *
   * Sets the total lives to equal to the parameter in order to control total
   * number of renders.
   *
   *  @param lives
   *  @return void
   */
  void SetLives(int lives) noexcept;

  /** @brief Setting level function
   *
   * Sets the level by clearing all flags.
   *
   *  @param level
   *  @return void
   */
  void SetLevel(int level) noexcept;

  /** @brief Update function
   *
   * Updates animated background and flag additions.
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