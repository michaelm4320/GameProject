/** @file Controls.cpp
 *  @brief Source file for 'Controls' menu
 *
 *  This program is used to create the menu 'Controls' at the start screen.
 * The screen displays player controls for the game.
 *
 *  @author Michael Martinez
 *  @bug No known bugs.
 */
#include "Controls.h"

// C26455: Fixing the warning 'noexcept' solution is to not include 'noexcept'
// in the first place.
//(https://docs.microsoft.com/en-us/cpp/code-quality/c26447?view=msvc-170)
Controls::Controls() {
  // Control screen text entities
  // C26409: Fixing warning to replace 'new' requires editing included framework
  // library 'QuickSDL" C26432: Already deleted underneath deconstructor
  mControlsMove = new Texture("Arrow Keys - Move Up, Down, Left, Right",
                              "BN6FontBold.ttf", 45, {255, 255, 255});
  mControlsMove->Parent(this);
  mControlsMove->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f,
                             Graphics::Instance()->SCREEN_HEIGHT * 0.1f));

  mControlShoot = new Texture("Spacebar Key - Shoot", "BN6FontBold.ttf", 45,
                              {255, 255, 255});
  mControlShoot->Parent(this);
  mControlShoot->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f,
                             Graphics::Instance()->SCREEN_HEIGHT * 0.2f));

  mControlHit = new Texture("X Key - Lose a life", "BN6FontBold.ttf", 45,
                            {255, 255, 255});
  mControlHit->Parent(this);
  mControlHit->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f,
                           Graphics::Instance()->SCREEN_HEIGHT * 0.3f));

  mControlLevel = new Texture("N Key - Skip a level", "BN6FontBold.ttf", 45,
                              {255, 255, 255});
  mControlLevel->Parent(this);
  mControlLevel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f,
                             Graphics::Instance()->SCREEN_HEIGHT * 0.4f));

  mControlReturn = new Texture("Press Enter to return to title",
                               "BN6FontBold.ttf", 45, {255, 255, 255});
  mControlReturn->Parent(this);
  mControlReturn->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f,
                              Graphics::Instance()->SCREEN_HEIGHT * 0.6f));
}

// C26432: deleting all would cause compiling error
Controls::~Controls() {
  // C26433: Method is not a virtual function to use override.
  delete mControlsMove;
  mControlsMove = nullptr;

  delete mControlShoot;
  mControlShoot = nullptr;

  delete mControlHit;
  mControlHit = nullptr;

  delete mControlLevel;
  mControlLevel = nullptr;

  delete mControlReturn;
  mControlReturn = nullptr;
}

// C26433: Method is not a virtual function to use override.
void Controls::Render() {
  mControlsMove->Render();
  mControlShoot->Render();
  mControlHit->Render();
  mControlLevel->Render();
  mControlReturn->Render();
}