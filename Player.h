/** @file Player.h
 *  @brief Header file for player
 *
 * This program is responsible handling the player within a level.
 *
 *  @author Michael Martinez
 *  @bug No known bugs.
 */
#ifndef _PLAYER_H
#define _PLAYER_H
#include <gsl/util>

#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "Bullet.h"
#include "InputManager.h"

using namespace QuickSDL;

/**
 * @brief The Player class
 * @author Michael Martinez
 *
 * Player class inheriting from GameEntity which is used to program player
 * interaction with the level itself.
 *
 */
class Player : public GameEntity {
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

  /** @brief Visible variable
   *
   * Used to check for player visibility.
   *
   */
  bool mVisible;

  /** @brief Animating variable
   *
   * Used to check if entity is animating.
   *
   */
  bool mAnimating;

  /** @brief Score variable
   *
   * Used to keep track of player score.
   *
   */
  int mScore;

  /** @brief Lives variable
   *
   * Used to keep track of current number of player lives.
   *
   */
  int mLives;

  /** @brief Megaman texture
   *
   * Creates texture of megaman for player.
   *
   */
  Texture* mMan;

  /** @brief Movement leaving animation texture
   *
   * An animated texture used for whenever megaman leaves a tile.
   *
   */
  AnimatedTexture* mMoveLeave;

  /** @brief Leave movement variable
   *
   * Used to see if megaman is currently leaving to a different tile.
   *
   */
  bool mLeaveMoving = true;

  /** @brief Death animation variable
   *
   * Animates player dying animation when damaged.
   *
   */
  AnimatedTexture* mDeathAnimation;

  /** @brief Movement speed variable
   *
   * The speed for how fast the player travels.
   *
   */
  float mMoveSpeed;

  /** @brief Movement bound position variable
   *
   * Program that bounds megaman to a specific space for movement.
   *
   */
  Vector2 mMoveBounds;

  /** @brief Movement bound position variable
   *
   * Program that bounds megaman to a specific space for movement.
   *
   */
  Vector2 mMoveBounds2;

  /** @brief Max bullets variable
   *
   * Used for the maximum number of bullets the player can have.
   *
   */
  static const int MAX_BULLETS = 2;

  /** @brief mBullets array
   *
   * Used to loop through the array to create bullets.
   *
   */
  Bullet* mBullets[MAX_BULLETS];

 private:
  /** @brief Movement function
   *
   * Handles players input for movement.
   *
   *  @return void
   */
  void HandleMovement();

  /** @brief Handle firing function
   *
   * Handles players input for firing bullets.
   *
   *  @return void
   */
  void HandleFiring();

 public:
  /** @brief Constructor
   *
   * Creating textures for the player as well as handling lives and player
   * bullets.
   *
   */
  Player();

  /** @brief Deconstructor
   *
   * Freeing all entities
   *
   */
  virtual ~Player();

  /** @brief Visible function
   *
   * Used to check if visible for rendering textures.
   *
   *  @param visible
   *  @return void
   */
  void Visible(bool visible) noexcept;

  /** @brief Animating function
   *
   * Used to check if current animation is in progress
   *
   *  @return bool
   */
  bool IsAnimating() noexcept;

  /** @brief Score function
   *
   * Used to keep track of player score.
   *
   *  @return int
   */
  int Score() noexcept;

  /** @brief Lives function
   *
   * Used to keep track of players current lives
   *
   *  @return int
   */
  int Lives() noexcept;

  /** @brief AddScore
   *
   * Handles changes to player score.
   *
   *  @param change
   *  @return void
   */
  void AddScore(int change) noexcept;

  /** @brief Hit function
   *
   * Plays the hit animation for when the player gets damaged.
   *
   *  @return void
   */
  void WasHit();

  /** @brief Update function
   *
   * Updates player firing and movement textures.
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