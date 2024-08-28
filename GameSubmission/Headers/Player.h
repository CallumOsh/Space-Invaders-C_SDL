#ifndef aPlayerFile
#define aPlayerFile

#include "AnimatedSprite.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Projectile.h"

class Player : public PhysicsEntity 
{

private:
	GameTimer* gameTimer;
	InputManager* inputManager;
	AudioManager* audioManager;

	bool isVisible;
	bool isAnimating;
	bool isHit;
	int playerScore;
	int playerLives;

	AnimatedSprite* player;
	float playerSpeed;
	Vector2 screenBoundaries;
	static const int max_Projectiles = 3;
	Projectile* projectiles[max_Projectiles];

private:
	bool IgnoreCollisions() override;
	void HandleMovement();
	void HandleFiring();

public:
	Player();
	~Player();
	void Visible(bool visible);
	bool IsAnimating();
	int Score();
	int Lives();
	void Hit(PhysicsEntity* other) override;
	bool WasHit();
	void AddScore(int change);
	void Update();
	void Render();
};
#endif
