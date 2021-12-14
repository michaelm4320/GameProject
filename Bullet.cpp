#include "Bullet.h"
#include <memory>

//C26455: Fixing the warning 'noexcept' solution is to not include 'noexcept' in the first place. 
//(https://docs.microsoft.com/en-us/cpp/code-quality/c26447?view=msvc-170)
Bullet::Bullet() {

	mTimer = Timer::Instance();

	mSpeed = 1500.0f;

	//Bullet Entity
	//C26409: Fixing warning to replace 'new' requires editing included framework library 'QuickSDL"
	mTexture = new Texture("bullet.png");
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);

	Rotate(90);
	Reload();
}

// C26432: deleting all would cause compiling error
Bullet::~Bullet() {

	
	mTimer = nullptr;

	delete mTexture;
    mTexture = nullptr;
}

void Bullet::Fire(Vector2 pos) {

	Pos(pos);
	Active(true);
}


void Bullet::Reload() {

	Active(false);
}

//C26433: Method is not a virtual function to use override.
void Bullet::Update() {

	//Bullet direction
	if(Active()) {
	
		Translate(-VEC2_UP * mSpeed * mTimer-> DeltaTime(), local);

		Vector2 const pos = Pos();

		if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFFSCREEN_BUFFER || pos.x < -OFFSCREEN_BUFFER || pos.x > Graphics::Instance()->SCREEN_WIDTH + OFFSCREEN_BUFFER) {
		
			Reload();
		}
	}
}

//C26433: Method is not a virtual function to use override.
void Bullet::Render() {

	if(Active()) {
	
		mTexture->Render();
	}
}