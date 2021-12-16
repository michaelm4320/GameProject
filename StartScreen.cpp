/** @file StartScreen.cpp
 *  @brief Source file for StartScreen
 *
 * This program is responsible handling the title screen after first playing the
 * game.
 *
 *  @author Michael Martinez
 *  @bug No known bugs.
 */
#include "StartScreen.h"

// C26455: Fixing the warning 'noexcept' solution is to not include 'noexcept'
// in the first place.
//(https://docs.microsoft.com/en-us/cpp/code-quality/c26447?view=msvc-170)
StartScreen::StartScreen() {
  mTimer = Timer::Instance();
  mInput = InputManager::Instance();

  // Logo Entities
  // C26409: Fixing warning to replace 'new' requires editing included
  // framework library 'QuickSDL"
  mLogo = new Texture("TitleScreen.png", 0, 0, 960, 640);
  //(PNG file, x, y, width, height, frames, speed, direction for spritesheet)
  mAnimatedLogo = new AnimatedTexture("TitleScreen.png", 0, 0, 960, 640, 10,
                                      1.25f, AnimatedTexture::vertical);

  // Used to adjust position of entities
  mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f,
                     Graphics::Instance()->SCREEN_HEIGHT * 0.32f));
  mAnimatedLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f,
                             Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

  mLogo->Parent(this);
  mAnimatedLogo->Parent(this);

  // Play Mode Entities
  mPlayModes =
      new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f,
                             Graphics::Instance()->SCREEN_HEIGHT * 0.55f));
  mNewGame = new Texture("NEW GAME", "BN6FontBold.ttf", 60, {230, 230, 230});
  mControls = new Texture("CONTROLS", "BN6FontBig.ttf", 60, {230, 230, 230});

  mAnimatedCursor = new AnimatedTexture("arrow.png", 0, 0, 52, 64, 3, 0.25f,
                                        AnimatedTexture::vertical);

  mNewGame->Parent(mPlayModes);
  mControls->Parent(mPlayModes);
  mAnimatedCursor->Parent(mPlayModes);

  mNewGame->Pos(Vector2(0.0f, 150.0f));
  mControls->Pos(Vector2(0.0f, 210.0f));

  mAnimatedCursor->Pos(Vector2(-150.0f, 148.0f));

  mPlayModes->Parent(this);

  mCursorStartPos = mAnimatedCursor->Pos(local);

  mCursorOffset = Vector2(0.0f, 60.0f);
  mSelectedMode = 0;

  // Bottom Bar Entities
  mBotBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f,
                                   Graphics::Instance()->SCREEN_HEIGHT * 0.7f));

  mRights = new Texture("© CAPCOM CO.,LTD.2005 ALL RIGHTS RESERVED",
                        "BN6FontBold.ttf", 45, {230, 230, 230});
  mRights->Parent(mBotBar);
  mRights->Pos(Vector2(0.0f, 170.0f));

  mBotBar->Parent(this);

  Pos(mAnimationStartPos);
}

// C26432: deleting all would cause compiling error
StartScreen::~StartScreen() {
  // Freeing Logo Entities
  delete mLogo;
  mLogo = nullptr;
  delete mAnimatedLogo;
  mAnimatedLogo = nullptr;

  // Freeing Play Mode Entities
  delete mPlayModes;
  mPlayModes = nullptr;
  delete mNewGame;
  mNewGame = nullptr;
  delete mControls;
  mControls = nullptr;

  delete mAnimatedCursor;
  mAnimatedCursor = nullptr;

  // Freeing Bottom Bar Entities
  delete mBotBar;
  mBotBar = nullptr;
  delete mRights;
  mRights = nullptr;
}

float StartScreen::SelectedMode() noexcept { return mSelectedMode; }

void StartScreen::ChangeSelectedMode(int change) {
  mSelectedMode += change;

  if (mSelectedMode < 0)
    mSelectedMode = 1;
  else if (mSelectedMode > 1)
    mSelectedMode = 0;

  // Allows the cursor to move positions
  mAnimatedCursor->Pos(mCursorStartPos + mCursorOffset * mSelectedMode);
}

// C26433: Method is not a virtual function to use override.
void StartScreen::Update() {
  if (!mAnimationDone) {
    mAnimationTimer += mTimer->DeltaTime();
    Pos(Lerp(mAnimationStartPos, mAnimationEndPos,
             mAnimationTimer / mAnimationTotalTime));

    if (mAnimationTimer >= mAnimationTotalTime) mAnimationDone = true;

    if (mInput->KeyPressed(SDL_SCANCODE_DOWN) ||
        mInput->KeyPressed(SDL_SCANCODE_UP))
      mAnimationTimer = mAnimationTotalTime;
  } else {
    mAnimatedLogo->Update();
    mAnimatedCursor->Update();

    if (mInput->KeyPressed(SDL_SCANCODE_DOWN))
      ChangeSelectedMode(1);
    else if (mInput->KeyPressed(SDL_SCANCODE_UP))
      ChangeSelectedMode(-1);
  }
}

// C26433: Method is not a virtual function to use override.
void StartScreen::Render() {
  if (!mAnimationDone)
    mLogo->Render();
  else
    mAnimatedLogo->Render();

  mNewGame->Render();
  mControls->Render();

  mAnimatedCursor->Render();

  mRights->Render();
}