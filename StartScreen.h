#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace QuickSDL;

class StartScreen : public GameEntity {
 private:
  // Texture used to create text/images, vector2 with regards to movemement
  Timer* mTimer;
  InputManager* mInput;

  // Top Bar Entities
  //GameEntity* mTopBar;
  //Texture* mPlayerOne;
  //Texture* mHiScore;
  //Texture* mPlayerTwo;

  // Logo Entities
  Texture* mLogo;
  AnimatedTexture* mAnimatedLogo;

  // Play Mode Entities
  GameEntity* mPlayModes;
  Texture* mNewGame;
  Texture* mControls;
  //Texture* mCursor;
  AnimatedTexture* mAnimatedCursor;
  Vector2 mCursorStartPos;
  Vector2 mCursorOffset;
  float mSelectedMode;

  // Bottom Bar Entities
  GameEntity* mBotBar;
  //Texture* mNamco;
  //Texture* mDates;
  Texture* mRights;

  // Screen Animation Variables
  Vector2 mAnimationStartPos;
  Vector2 mAnimationEndPos;
  float mAnimationTotalTime = 0.0;
  float mAnimationTimer = 0.0;
  bool mAnimationDone = true;

 public:
  StartScreen();
  virtual ~StartScreen();

  float SelectedMode() noexcept;
  void ChangeSelectedMode(int change);

  void Update();

  void Render();
};

#endif