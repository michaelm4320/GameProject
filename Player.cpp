/** @file Player.cpp
 *  @brief Source file for player
 *
 * This program is responsible handling the player within a level.
 *
 *  @author Michael Martinez
 *  @bug No known bugs.
 */
#include "Player.h"

// C26455: Fixing the warning 'noexcept' solution is to not include 'noexcept'
// in the first place.
//(https://docs.microsoft.com/en-us/cpp/code-quality/c26447?view=msvc-170)
Player::Player() {
  mTimer = Timer::Instance();
  mInput = InputManager::Instance();
  mAudio = AudioManager::Instance();

  mVisible = false;
  mAnimating = false;

  mScore = 0;
  mLives = 2;

  // Player entity
  // C26409: Fixing warning to replace 'new' requires editing included
  // framework library 'QuickSDL"
  mMan = new Texture("megaman.png");
  mMan->Parent(this);
  mMan->Pos(VEC2_ZERO);

  // Player Settings
  mMoveSpeed = 300.0f;
  mMoveBounds = Vector2(99.0f, 413.0f);
  mMoveBounds2 = Vector2(277.0f, 471.0f);

  // Movement transition entity
  mMoveLeave = new AnimatedTexture("transition.png", 0, 0, 175, 262, 4, 0.2f,
                                   AnimatedTexture::horizontal);
  mMoveLeave->Parent(this);
  mMoveLeave->Pos(VEC2_ZERO);
  mMoveLeave->WrapMode(AnimatedTexture::once);

  // Player death entity
  mDeathAnimation = new AnimatedTexture("mmDeath.png", 0, 0, 237, 217, 1, 2.0f,
                                        AnimatedTexture::horizontal);
  mDeathAnimation->Parent(this);
  mDeathAnimation->Pos(VEC2_ZERO);
  mDeathAnimation->WrapMode(AnimatedTexture::once);

  for (int i = 0; i < MAX_BULLETS; i++) {
    gsl::at(mBullets, i) = new Bullet();
  }
}

// C26432: deleting all would cause compiling error
Player::~Player() {
  mTimer = nullptr;
  mInput = nullptr;
  mAudio = nullptr;

  delete mMan;
  mMan = nullptr;

  delete mMoveLeave;
  mMoveLeave = nullptr;

  delete mDeathAnimation;
  mDeathAnimation = nullptr;

  for (int i = 0; i < MAX_BULLETS; i++) {
    delete gsl::at(mBullets, i);
    gsl::at(mBullets, i) = nullptr;
  }
}

void Player::HandleMovement() {
  // Player Movement
  if (mInput->KeyPressed(SDL_SCANCODE_RIGHT)) {
    mMoveLeave->ResetAnimation();
    mLeaveMoving = true;

    Translate(VEC2_RIGHT * 157, world);

  } else if (mInput->KeyPressed(SDL_SCANCODE_LEFT)) {
    mMoveLeave->ResetAnimation();
    mLeaveMoving = true;
    Translate(-VEC2_RIGHT * 157, world);
  }

  if (mInput->KeyPressed(SDL_SCANCODE_UP)) {
    mMoveLeave->ResetAnimation();
    mLeaveMoving = true;
    Translate(-VEC2_UP * 100, world);

  } else if (mInput->KeyPressed(SDL_SCANCODE_DOWN)) {
    mMoveLeave->ResetAnimation();
    mLeaveMoving = true;
    Translate(VEC2_UP * 100, world);
  }

  // Player movement bound area
  Vector2 pos = Pos(local);
  if (pos.x < mMoveBounds.x)
    pos.x = mMoveBounds.x;
  else if (pos.x > mMoveBounds.y)
    pos.x = mMoveBounds.y;

  if (pos.y < mMoveBounds2.x)
    pos.y = mMoveBounds2.x;
  else if (pos.y > mMoveBounds2.y)
    pos.y = mMoveBounds2.y;

  Pos(pos);
}

void Player::HandleFiring() {
  // Player firing
  if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
    for (int i = 0; i < MAX_BULLETS; i++) {
      if (!gsl::at(mBullets, i)->Active()) {
        gsl::at(mBullets, i)->Fire(Pos());
        mAudio->PlaySFX("fire.wav");
        break;
      }
    }
  }
}

void Player::Visible(bool visible) noexcept { mVisible = visible; }

bool Player::IsAnimating() noexcept { return mAnimating; }

int Player::Score() noexcept { return mScore; }

int Player::Lives() noexcept { return mLives; }

void Player::AddScore(int change) noexcept { mScore += change; }

void Player::WasHit() {
  // Player hit
  mLives--;
  mDeathAnimation->ResetAnimation();
  mAnimating = true;
  mAudio->PlaySFX("death.wav");
}

// C26433: Method is not a virtual function to use override.
void Player::Update() {
  if (mLeaveMoving) {
    mMoveLeave->Update();
    mLeaveMoving = mMoveLeave->IsAnimating();
  }

  if (mAnimating) {
    mDeathAnimation->Update();
    mAnimating = mDeathAnimation->IsAnimating();

  } else {
    if (Active()) {
      HandleMovement();
      HandleFiring();
    }
  }

  for (int i = 0; i < MAX_BULLETS; i++) gsl::at(mBullets, i)->Update();
}

// C26433: Method is not a virtual function to use override.
void Player::Render() {
  if (mVisible) {
    if (mAnimating) {
      mDeathAnimation->Render();
    } else if (mLeaveMoving) {
      mMoveLeave->Render();
    } else {
      mMan->Render();
    }
  }
  for (int i = 0; i < MAX_BULLETS; i++) gsl::at(mBullets, i)->Render();
}