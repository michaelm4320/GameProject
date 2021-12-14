#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H
#include "InputManager.h"
#include "StartScreen.h"
#include "PlayBG.h"
#include "Level.h"
#include "Player.h"

class PlayScreen : public GameEntity {

	private:

		Timer* mTimer;
		InputManager* mInput;
		AudioManager* mAudio;
		
		PlayBG* mPlayBG;
		
		Texture* mStartLabel;

		float mLevelStartTimer = 0.0;
		float mLevelStartDelay;

		bool mGameStarted = false;

		Level* mLevel;
		bool mLevelStarted;
		int mCurrentStage = 0;

		Player* mPlayer;

	private:

		void StartNextLevel();

	public:

		PlayScreen();
		virtual ~PlayScreen();
		
		void StartNewGame();

		bool GameOver() noexcept;

		void Update();

		void Render();
};

#endif
