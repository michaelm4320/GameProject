/** @file StartScreen.h
 *  @brief Header file for StartScreen
 *
 * This program is responsible handling the title screen after first playing the
 * game.
 *
 *  @author Michael Martinez
 *  @bug No known bugs.
 */
#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace QuickSDL;

/**
 * @brief The StartScreen class
 * @author Michael Martinez
 *
 * StartScreen class inheriting from GameEntity which is used for the title
 * screen for the game.
 *
 */
class StartScreen : public GameEntity {
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

  /** @brief Logo texture
   *
   * Used to create logo texture.
   *
   */
  Texture* mLogo;

  /** @brief Animated logo texture
   *
   * Used to create animated logo texture.
   *
   */
  AnimatedTexture* mAnimatedLogo;

  /** @brief Game entity variable
   *
   * Used to create new game entity for positioning the textures on window.
   *
   */
  GameEntity* mPlayModes;

  /** @brief New game menu texture
   *
   * Used to create new game texture for the player to select and start game.
   *
   */
  Texture* mNewGame;

  /** @brief Controls menu texture
   *
   * Used to create controls texture for the player to select and view ingame
   * controls.
   *
   */
  Texture* mControls;

  /** @brief Animated cursor texture
   *
   * Used to create animated cursor texture.
   *
   */
  AnimatedTexture* mAnimatedCursor;

  /** @brief Cursor start position variable
   *
   * Variable used to create starting position for cursor.
   *
   */
  Vector2 mCursorStartPos;

  /** @brief Cursor offset variable
   *
   * Variable used to create offset position for cursor.
   *
   */
  Vector2 mCursorOffset;

  /** @brief Mode selection variable
   *
   * Used to keep track of value for selecting mode.
   *
   */
  float mSelectedMode;

  /** @brief Game entity variable
   *
   * Used to create new game entity for positioning the textures on window.
   *
   */
  GameEntity* mBotBar;

  /** @brief Rights texture
   *
   * Used to create Capcom rights texture.
   *
   */
  Texture* mRights;

  /** @brief Animation start position variable
   *
   * Vector variable used to create starting position for animation.
   *
   */
  Vector2 mAnimationStartPos;

  /** @brief Animation end position variable
   *
   * Vector variable used to create ending position for animation.
   *
   */
  Vector2 mAnimationEndPos;

  /** @brief Total animation time variable
   *
   * Used to keep track of total animation.
   *
   */
  float mAnimationTotalTime = 0.0;

  /** @brief Animation timer variable
   *
   * Variable used to keep track how much time passed to go through animation.
   *
   */
  float mAnimationTimer = 0.0;

  /** @brief Boolean variable for animations
   *
   * Used to check of animation is done.
   *
   */
  bool mAnimationDone = true;

 public:
  /** @brief Constructor
   *
   * Creating textures and setting them into position.
   *
   */
  StartScreen();

  /** @brief Deconstructor
   *
   * Freeing all entities.
   *
   */
  virtual ~StartScreen();

  /** @brief Selected mode function
   *
   * Used to return selected mode.
   *
   *  @return float
   */
  float SelectedMode() noexcept;

  /** @brief Change selected mode function
   *
   * Used to check the current mode for menu selection.
   *
   *  @return void
   */
  void ChangeSelectedMode(int change);

  /** @brief Update function
   *
   * Used to update animated textures.
   *
   *  @return void
   */
  void Update();

  /** @brief Render function
   *
   * Renders all textures.
   *
   *  @return void
   */
  void Render();
};

#endif