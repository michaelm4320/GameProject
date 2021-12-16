/** @file PlayBG.cpp
 *  @brief Source file for player level background
 *
 * This program is responsible handling level backgrounds. These include
 * displaying the level's animated background, status HUD, and player lives.
 *
 *  @author Michael Martinez
 *  @bug No known bugs.
 */

#include "PlayBG.h"

// C26455: Fixing the warning 'noexcept' solution is to not include 'noexcept'
// in the first place.
//(https://docs.microsoft.com/en-us/cpp/code-quality/c26447?view=msvc-170)
PlayBG::PlayBG() {
  mTimer = Timer::Instance();
  mAudio = AudioManager::Instance();

  // Background stage entities
  // C26409: Fixing warning to replace 'new' requires editing included framework
  // library 'QuickSDL"
  mBackground = new Texture("bgAnimated.png");
  mAnimatedBackground = new AnimatedTexture(
      "bgAnimated.png", 0, 0, 960, 640, 10, 1.25f, AnimatedTexture::vertical);

  mStage = new Texture("Stage.png");
  mStage->Pos(Vector2(480.0f, 450.0f));

  mStatus = new Texture("Status.png");
  mStatus->Pos(Vector2(250.0f, 75.0f));

  mBackground->Parent(this);
  mBackground->Pos(VEC2_ZERO);

  mBackground->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f,
                           Graphics::Instance()->SCREEN_HEIGHT * 0.32f));
  mAnimatedBackground->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f,
                                   Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

  mLives = new GameEntity();
  mLives->Parent(this);
  mLives->Pos(Vector2(110.0f, 90.0f));

  // Player lives
  for (int i = 0; i < MAX_MM_TEXTURES; i++) {
    gsl::at(mLivesTextures, i) = new Texture("Life.png");
    gsl::at(mLivesTextures, i)->Parent(mLives);
    gsl::at(mLivesTextures, i)->Pos(Vector2(130.0f * (i % 3), 70.f * (i / 3)));
  }

  mFlags = new GameEntity();
  mFlags->Parent(this);
  mFlags->Pos(Vector2(350.0f, 100.0f));

  mFlagTimer = 0.0f;
  mFlagInterval = 0.5;
}

// C26432: deleting all would cause compiling error
PlayBG::~PlayBG() {
  mTimer = nullptr;
  mAudio = nullptr;

  delete mBackground;
  mBackground = nullptr;

  delete mAnimatedBackground;
  mAnimatedBackground = nullptr;

  delete mStage;
  mStage = nullptr;

  delete mStatus;
  mStatus = nullptr;

  delete mLives;
  mLives = nullptr;

  for (int i = 0; i < MAX_MM_TEXTURES; i++) {
    delete gsl::at(mLivesTextures, i);
    gsl::at(mLivesTextures, i) = nullptr;
  }
  delete mFlags;
  mFlags = nullptr;

  ClearFlags();
}

void PlayBG::ClearFlags() noexcept {
  for (unsigned int i = 0; i < mFlagTextures.size(); i++) {
    delete gsl::at(mFlagTextures, i);
    gsl::at(mFlagTextures, i) = nullptr;
  }

  mFlagTextures.clear();
}

void PlayBG::AddNextFlag() {
  // Stage level flags
  if (mRemainingLevels == 3)
    AddFlag("3.png", 72.0f, 3);
  else if (mRemainingLevels == 2)
    AddFlag("2.png", 72.0f, 2);
  else if (mRemainingLevels == 1)
    AddFlag("1.png", 72.0f, 2);
}

void PlayBG::AddFlag(std::string filename, float width, int value) {
  const int index = mFlagTextures.size();

  if (index > 0) mFlagXOffset += width * 0.5f;

  // Location of stage flag
  mRemainingLevels -= value;
  mFlagTextures.push_back(new Texture(filename));
  gsl::at(mFlagTextures, index)->Parent(mFlags);
  gsl::at(mFlagTextures, index)->Pos(VEC2_RIGHT * mFlagXOffset);
  mFlagXOffset += width * 0.5f;

  mAudio->PlaySFX("StageSE.wav");
}
void PlayBG::SetLives(int lives) noexcept { mTotalLives = lives; }

void PlayBG::SetLevel(int level) noexcept {
  ClearFlags();

  mRemainingLevels = level;
  mFlagXOffset = 0.0f;
}

// C26433: Method is not a virtual function to use override.
void PlayBG::Update() {
  mAnimatedBackground->Update();

  if (mRemainingLevels > 0) {
    mFlagTimer += mTimer->DeltaTime();
    if (mFlagTimer >= mFlagInterval) {
      AddNextFlag();
      mFlagTimer = 0.0f;
    }
  }
}

// C26433: Method is not a virtual function to use override.
void PlayBG::Render() {
  mBackground->Render();
  mAnimatedBackground->Render();

  mStage->Render();
  mStatus->Render();

  for (int i = 0; i < MAX_MM_TEXTURES && i < mTotalLives; i++) {
    gsl::at(mLivesTextures, i)->Render();
  }

  for (unsigned int i = 0; i < mFlagTextures.size(); i++) {
    gsl::at(mFlagTextures, i)->Render();
  }
}