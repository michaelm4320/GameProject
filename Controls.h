/** @file Controls.h
 *  @brief Header file for 'Controls' menu
 *
 *  This program is used to create the menu 'Controls' at the start screen.
 * The screen displays player controls for the game.
 *
 *  @author Michael Martinez
 *  @bug No known bugs.
 */
#ifndef _CONTROLS_H
#define _CONTROLS_H
#include "InputManager.h"
#include "Level.h"
#include "PlayBG.h"
#include "Player.h"
#include "StartScreen.h"

/**
 * @brief The Controls class
 * @author Michael Martinez
 *
 * Controls class inheriting from GameEntity which is used to program 'Controls'
 * menu.
 */
class Controls : public GameEntity {
  // LO6
 private:
  /** @brief Movement controls texture
   *
   * 'mControlsMove' displays controls for movement.
   *
   */
  Texture* mControlsMove;

  /** @brief Shooting controls texture
   *
   * 'mControlShoot' displays controls for player shooting.
   *
   */
  Texture* mControlShoot;

  /** @brief Damage hit controls texture
   *
   * 'mControlHit' displays controls for taking player damage.
   *
   */
  Texture* mControlHit;

  /** @brief Level controls texture
   *
   * 'mControlLevel' displays controls for player level advancement.
   *
   */
  Texture* mControlLevel;

  /** @brief Return controls texture
   *
   * 'mControlReturn' displays controls for returning player back to title
   * screen.
   *
   */
  Texture* mControlReturn;

 public:
  /** @brief Constructor
   *
   * Creates all textures for the controls menu.
   *
   */
  Controls();

  /** @brief Deconstructor
   *
   * Freeing all entities.
   *
   */
  virtual ~Controls();

  /** @brief Render function
   *
   * Renders all textures.
   *
   *  @return void
   */
  void Render();
};

#endif
