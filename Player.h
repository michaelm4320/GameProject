#ifndef _PLAYER_H
#define _PLAYER_H
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Bullet.h"
#include <gsl/util>

using namespace QuickSDL;

class Player : public GameEntity {

	private:

		Timer* mTimer;
		InputManager* mInput;
		AudioManager* mAudio;

		bool mVisible;
		bool mAnimating;

		int mScore;
		int mLives;

		Texture* mMan;
        AnimatedTexture* mMoveLeave;
		bool mLeaveMoving = true;

		AnimatedTexture* mDeathAnimation;

		float mMoveSpeed;
		Vector2 mMoveBounds;
        Vector2 mMoveBounds2;

		static const int MAX_BULLETS = 2;
		Bullet* mBullets[MAX_BULLETS];

	private:

		void HandleMovement();
		void HandleFiring();

	public:

		Player();
		virtual ~Player();

		void Visible(bool visible) noexcept;
		bool IsAnimating() noexcept;

		int Score() noexcept;
		int Lives() noexcept;

		void AddScore(int change) noexcept;

		void WasHit();

		void Update();

		void Render();
};


#endif