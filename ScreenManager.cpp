/** @file ScreenManager.cpp
 *  @brief Source file for ScreenManager
 *
 * This program is responsible handling all screen types for the game.
 *
 *  @author Michael Martinez
 *  @bug Title selection screen movement is being triggered throughout all the
 * screen types when it should only be affected within the start screen. This
 * causes the menu selection to be incorrect sometimes.
 */
#include "ScreenManager.h"

// Responsible for handling all screens for game (Title screen, Control Screen,
// Play Screen)
ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance() {
  // C26409: Fixing warning to replace 'new' requires editing included
  // framework library 'QuickSDL"
  if (sInstance == nullptr) sInstance = new ScreenManager();

  return sInstance;
}

void ScreenManager::Release() noexcept {
  delete sInstance;
  sInstance = nullptr;
}

// C26455: Fixing the warning 'noexcept' solution is to not include 'noexcept'
// in the first place.
//(https://docs.microsoft.com/en-us/cpp/code-quality/c26447?view=msvc-170)
ScreenManager::ScreenManager() {
  mInput = InputManager::Instance();

  mStartScreen = new StartScreen();
  mPlayScreen = new PlayScreen();
  mControls = new Controls();

  // C26812: Changing 'enum' to 'enum class' would cause compilation
  // error, making all types into undeclared identifiers
  mCurrentScreen = start;
}

// C26432: deleting all would cause compiling error
ScreenManager::~ScreenManager() {
  mInput = nullptr;

  delete mStartScreen;
  mStartScreen = nullptr;

  delete mPlayScreen;
  mPlayScreen = nullptr;
}

void ScreenManager::Update() {
  if (mInput->KeyPressed(SDL_SCANCODE_DOWN) ||
      mInput->KeyPressed(SDL_SCANCODE_UP))
    mode *= -1;

  switch (mCurrentScreen) {
    case start:

      mStartScreen->Update();

      // Switch screens by hitting enter
      if (mInput->KeyPressed(SDL_SCANCODE_RETURN) && mode == -1) {
        mCurrentScreen = controls;
      } else if (mInput->KeyPressed(SDL_SCANCODE_RETURN) && mode == 1) {
        mCurrentScreen = play;
        mPlayScreen->StartNewGame();
      }
      break;

    case play:

      mPlayScreen->Update();
      if (mPlayScreen->GameOver()) {
        mCurrentScreen = start;
      }
      break;

    case controls:

      mControls->Update();
      if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) mCurrentScreen = start;
      break;
  }
}

void ScreenManager::Render() {
  switch (mCurrentScreen) {
    case start:

      mStartScreen->Render();

      break;

    case play:

      mPlayScreen->Render();
      break;

    case controls:

      mControls->Render();
      break;
  }
}