#include "PlayScreen.h"

// C26455: Fixing the warning 'noexcept' solution is to not include 'noexcept'
// in the first place.
//(https://docs.microsoft.com/en-us/cpp/code-quality/c26447?view=msvc-170)
PlayScreen::PlayScreen() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

    // C26409: Fixing warning to replace 'new' requires editing included
    // framework library 'QuickSDL"
	mPlayBG = new PlayBG();

	//Ready player texture
	mStartLabel = new Texture("ARE YOU READY?", "BN6FontBold.ttf", 60, {0, 0, 0});
	mStartLabel->Parent(this);
    mStartLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f,Graphics::Instance()->SCREEN_HEIGHT * 0.3f));

	mLevel = nullptr;
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;

	mPlayer = nullptr;
}

// C26432: deleting all would cause compiling error
PlayScreen::~PlayScreen() {

	mTimer = nullptr;
	mInput = nullptr;

	delete mPlayBG;
	mPlayBG = nullptr;

	delete mStartLabel;
	mStartLabel = nullptr;

	delete mLevel;
	mLevel = nullptr;

	delete mPlayer;
	mPlayer = nullptr;
}

void PlayScreen::StartNextLevel() {

	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;
	
	delete mLevel;
	mLevel = new Level(mCurrentStage, mPlayBG, mPlayer);
}

void PlayScreen::StartNewGame() {

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
    mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.267f,Graphics::Instance()->SCREEN_HEIGHT * 0.58f));
	mPlayer->Active(false);

	mPlayBG->SetLives(mPlayer->Lives());
	mPlayBG->SetLevel(0);

	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;

    mCurrentStage = 0;

	mAudio->PlayMusic("start.wav", 0);
	
}

bool PlayScreen::GameOver() noexcept {

	//Game over state
	if(!mLevelStarted)
		return false;

    // C26812: Changing 'enum' to 'enum class' would cause compilation
    // error, making all types into undeclared identifiers
	return (mLevel->State() == Level::gameover);
}

// C26433: Method is not a virtual function to use override.
void PlayScreen::Update() {

	if(mGameStarted) {
		
		if(!mLevelStarted) {
		
			mLevelStartTimer += mTimer->DeltaTime();
			if(mLevelStartTimer >= mLevelStartDelay)
				StartNextLevel();
		}
		
	} else {
	
		if(!Mix_PlayingMusic()) {
		
			mGameStarted = true;
		}
	}

	if(mGameStarted) {
	
		if(mCurrentStage > 0)
			mPlayBG->Update();

		if (mLevelStarted) {
                 
			mLevel->Update();

			if(mLevel->State() == Level::finished) {
			
				mLevelStarted = false;
			}
        }

		mPlayer->Update();		
	}       
}

// C26433: Method is not a virtual function to use override.
void PlayScreen::Render() {

  mPlayBG->Render();

  if (!mGameStarted) 
	  mStartLabel->Render();

  if (mGameStarted) {

    if (mLevelStarted) 
      mLevel->Render();

    mPlayer->Render();
    
  }
}