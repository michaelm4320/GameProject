/** @file Bullet.h
 *  @brief Header file for player projectiles
 *
 *  This program is used to create bullets for the player to shoot with towards
 * enemy encounters.
 *
 *  @author Michael Martinez
 *  @bug No known bugs.
 */

#ifndef _BULLET_H
#define _BULLET_H
#include "Texture.h"
#include "Timer.h"

using namespace QuickSDL;

/**
 * @brief The Bullet class
 * @author Michael Martinez
 *
 * Bullet class inheriting from GameEntity which is used to program player
 * bullets.
 */
// LO1 LO1a LO2
class Bullet : public GameEntity {
  /** @brief Offscreen buffer variable
   *
   * Used for reloading bullets when bullets are offscreen from player.
   *
   */
  const int OFFSCREEN_BUFFER = 10;

  /** @brief Timer variable
   *
   * Used to keep track of time between resets.
   *
   */
  Timer* mTimer;

  /** @brief Projectile speed
   *
   * 'mSpeed' is used to control projectile speed.
   *
   */
  float mSpeed;

  /** @brief Bullet image
   *
   * 'mTexture' is used create the look of the player's bullet.
   *
   */
  Texture* mTexture;

 public:
  /** @brief Constructor
   *
   * Creates texture for speed as well as setting speed for the bullet after
   * shot and angle being shot.
   *
   */
  Bullet();

  /** @brief Deconstructor
   *
   * Freeing all entities
   *
   */
  virtual ~Bullet();

  /** @brief Firing function
   *
   * Position for when the bullets are fired.
   *
   *  @param pos Bullet vector position
   *  @return void
   */
  void Fire(Vector2 pos);

  /** @brief Reload function
   *
   * Reloads bullets for the player
   *
   *  @returnvoid
   */
  void Reload();

  /** @brief Update function
   *
   * Updating bullet travel direction.
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