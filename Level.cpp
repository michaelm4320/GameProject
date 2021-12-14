#include "Level.h"

Level::Level(int stage, PlayBG* playBG, Player* player) {

	mTimer = Timer::Instance();
	mPlayBG = playBG;
	mPlayBG->SetLevel(stage);

	mStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.5f;

	//Battle start message entity
    // C26409: Fixing warning to replace 'new' requires editing included
    // framework library 'QuickSDL"
	mReadyLabel = new Texture("battleStart.png");
	mReadyLabel->Parent(this);
    mReadyLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT *0.3f));

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 3.0f;

	//Player settings
	mPlayer = player;
	mPlayerHit = false;
    mPlayerRespawnDelay = 3.0f;
    mPlayerRespawnTimer = 0.0f;
	mPlayerRespawnLabelOnScreen = 2.0f;

	//Game over entities
    // C26409: Fixing warning to replace 'new' requires editing included
    // framework library 'QuickSDL"
	mGameOverLabel = new Texture("GAME OVER", "BN6FontBold.ttf", 75, {150, 0, 0});
	mGameOverLabel->Parent(this);
    mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.3f));

	mGameOver = false;
	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	// C26812: Changing 'enum' to 'enum class' would cause compilation error, making all types into undeclared identifiers
	mCurrentState = running;
}

// C26432: deleting all would cause compiling error
Level::~Level() {

	mTimer = nullptr;
    mPlayBG = nullptr;

	delete mReadyLabel;
    mReadyLabel = nullptr;

	mPlayer = nullptr;

	delete mGameOverLabel;
    mGameOverLabel = nullptr;
}

void Level::StartStage() noexcept {

	mStageStarted = true;
}

void Level::HandleStartLabels() {

	mLabelTimer += mTimer->DeltaTime();
  if (mLabelTimer >= mStageLabelOffScreen) {
    if (mStage > 1) {
      StartStage();
    } else {
      if (mLabelTimer >= mReadyLabelOffScreen) {
        StartStage();
        mPlayer->Active(true);
        mPlayer->Visible(true);
      }
    }
  }
}

void Level::HandleCollisions() {
	
	//Player hit
  if (!mPlayerHit) {
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_X)) {
      mPlayer->WasHit();
      mPlayBG->SetLives(mPlayer->Lives());

      mPlayerHit = true;
      mPlayerRespawnTimer = 0.0f;
      mPlayer->Active(false);
    }
  }
}

void Level::HandlePlayerDeath() {

	//Player losing lives
	if(!mPlayer->IsAnimating()) {
	
		if(mPlayer->Lives() > 0) {
		
			if(mPlayerRespawnTimer == 0.0f)
				mPlayer->Visible(false);

			mPlayerRespawnTimer += mTimer->DeltaTime();
			if(mPlayerRespawnTimer >= mPlayerRespawnDelay) {
			
				mPlayer->Active(true);
				mPlayer->Visible(true);
				mPlayerHit = false;
			}

		} else {
		
			if(mGameOverTimer == 0.0f)
				mPlayer->Visible(false);

			mGameOverTimer += mTimer->DeltaTime();
			if(mGameOverTimer >= mGameOverDelay) {
			
				mCurrentState = gameover;
			}
		}
	}
}

Level::LEVEL_STATES Level::State() noexcept {

	return mCurrentState;
}

// C26433: Method is not a virtual function to use override.
void Level::Update() {

  if (!mStageStarted) {

    HandleStartLabels();

  } else {
    HandleCollisions();

    if (mPlayerHit) {
		
		HandlePlayerDeath();

  } else {	

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N)) {

        mCurrentState = finished;
      }
	}
  }
}
// C26433: Method is not a virtual function to use override.
void Level::Render() {

	if(!mStageStarted) {
	
		if(mLabelTimer > mStageLabelOnScreen && mLabelTimer < mStageLabelOffScreen) {
			
		} else if(mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen) {
		
			mReadyLabel->Render();
		}
	} else {
	
		if(mPlayerHit) {
		
			if(mPlayerRespawnTimer >= mPlayerRespawnLabelOnScreen)
				mReadyLabel->Render();

			if(mGameOverTimer >=mGameOverLabelOnScreen)
				mGameOverLabel->Render();
		}
	}
}