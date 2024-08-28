#include "../Headers/Player.h"
#include "../Headers/BoxCollider.h"
#include "../Headers/PhysicsManager.h"

Player::Player()
{
	gameTimer = GameTimer::Instance();
	inputManager = InputManager::Instance();
	audioManager = AudioManager::Instance();

	isVisible = false;
	isAnimating = false;
	isHit = false;
	playerScore = 0;
	playerLives = 3;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[Player Lives Set]");

	player = new AnimatedSprite("ShipSprites.png", 0, 0, 64, 64, 3, 1.0f, AnimatedSprite::vertical);
	player->Parent(this);
	player->Pos(VEC2_ZERO);
	player->Scale(Vector2(2.0f, 2.0f));

	playerSpeed = 350.0f;
	screenBoundaries = (Vector2(45.0f, 990.0f));

	for (int i = 0; i < max_Projectiles; i++)
	{
		projectiles[i] = new Projectile(true);
	}
	AddCollider(new BoxCollider(Vector2(15.0f, 67.0f)));
	AddCollider(new BoxCollider(Vector2(15.0f, 40.0f)), Vector2(15.0f, 10.0f));
	AddCollider(new BoxCollider(Vector2(15.0f, 40.0f)), Vector2(-15.0f, 10.0f));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);
}

Player::~Player()
{
	gameTimer = NULL;
	inputManager = NULL;
	audioManager = NULL;

	delete player;
	player = NULL;

	for (int i = 0; i < max_Projectiles; i++)
	{
		delete projectiles[i];
		projectiles[i] = NULL;
	}
}

bool Player::IgnoreCollisions()
{
	return !isVisible || isAnimating;
}

void Player::HandleMovement()
{
	if (inputManager->KeyDown(SDL_SCANCODE_D))
	{
		Translate(VEC2_RIGHT * playerSpeed * gameTimer->DeltaTime(), world);
		if (inputManager->KeyPressed(SDL_SCANCODE_D))
		{
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[D Key Pressed]");
		}
	}
	else if (inputManager->KeyDown(SDL_SCANCODE_A))
	{
		Translate(-VEC2_RIGHT * playerSpeed * gameTimer->DeltaTime(), world);
		if (inputManager->KeyPressed(SDL_SCANCODE_A))
		{
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[A Key Pressed]");
		}
	}

	Vector2 pos = Pos(local);
	if (pos.x < screenBoundaries.x) {
		pos.x = screenBoundaries.x;
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[Screen Boundaries Reached]");
	}

	else if (pos.x > screenBoundaries.y)
	{
		pos.x = screenBoundaries.y;
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[Screen Boundaries Reached]");
	}
	Pos(pos);
}

void Player::HandleFiring()
{
	if (inputManager->KeyPressed(SDL_SCANCODE_SPACE))
	{
		for (int i = 0; i < max_Projectiles; i++)
		{
			if (!projectiles[i]->Active())
			{
				projectiles[i]->Fire(Pos());
				audioManager->PlayGameEffects("PlayerShoot.wav");
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[Space Key Pressed, Shoot Sound Played]");
				break;
			}
			else 
			{
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[Max Projectiles Reached]");
			}
		}
	}
}

void Player::Visible(bool visible)
{
	isVisible = visible;
}

void Player::Hit(PhysicsEntity* other) 
{
	playerLives--;
	isAnimating = true;
	audioManager->PlayGameEffects("EnemyExplosion.wav");
	isHit = true;
}

bool Player::WasHit()
{
	return isHit;
}

bool Player::IsAnimating()
{
	return isAnimating;
}

int Player::Score()
{
	return playerScore;
}

int Player::Lives()
{
	return playerLives;
}

void Player::AddScore(int change)
{
 	playerScore += change;
}

void Player::Update()
{
	if (isAnimating)
	{
		if (isHit)
			isHit = false;
	}
	else 
	{
		if (Active())
		{
			HandleMovement();
			HandleFiring();
		}
	}
	for (int i = 0; i < max_Projectiles; i++)
	{
		projectiles[i]->Update();
	}
	player->Update();
}

void Player::Render()
{
	player->Render();

	for (int i = 0; i < max_Projectiles; i++)
	{
		projectiles[i]->Render();
	}
	PhysicsEntity::Render();
}