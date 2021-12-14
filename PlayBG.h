#ifndef _PLAYHEALTH_H
#define _PLAYHEALTH_H
#include "Timer.h"
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "StartScreen.h"
#include <vector>
#include <gsl/util>


class PlayBG : public GameEntity {

	private:
		Timer* mTimer;
		AudioManager* mAudio;

		Texture* mBackground;
        AnimatedTexture* mAnimatedBackground;

		Texture* mStage;
        Texture* mStatus;

		//float mBlinkTimer;
		//float mBlinkInterval;
		
		static const int MAX_MM_TEXTURES = 2;
		GameEntity* mLives;
		Texture* mLivesTextures[MAX_MM_TEXTURES];
		int mTotalLives = 0;

		GameEntity* mFlags;
		std::vector<Texture*> mFlagTextures;
		int mRemainingLevels = 0;
		float mFlagXOffset = 0.0;
		float mFlagTimer;
		float mFlagInterval;

		private:

			void ClearFlags() noexcept;
			void AddNextFlag();
			void AddFlag(std::string filename, float widgth, int value);

	public:

		PlayBG();
	    virtual ~PlayBG();

		void SetLives(int lives) noexcept;
		void SetLevel(int level) noexcept;

		void Update();

		void Render();

};

#endif