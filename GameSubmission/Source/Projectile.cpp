#include "../Headers/Projectile.h"
#include "../Headers/BoxCollider.h"
#include "../Headers/PhysicsManager.h"

Projectile::Projectile(bool friendly) 
{
	gameTimer = GameTimer::Instance();
	speed = 1000.0f;

	sprite = new Sprite("Bullet.png");
	sprite->Parent(this);
	sprite->Pos(VEC2_ZERO);
	sprite->Scale(Vector2(0.25f, 0.25f));
	Reload();

	AddCollider(new BoxCollider(sprite->ScaledDimensions()));
	if (friendly)
		PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::FriendlyProjectiles);
	else
		PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::HostileProjectiles);
}

Projectile::~Projectile()
{
	gameTimer = NULL;

	delete sprite;
	sprite = NULL;
}

void Projectile::Fire(Vector2 pos) 
{
	Pos(pos);
	Active(true);
}

void Projectile::Reload() 
{
	Active(false);
}

void Projectile::Hit(PhysicsEntity* other)
{
	Reload();
}

bool Projectile::IgnoreCollisions() 
{
	return !Active();
}

void Projectile::Update()
{
	if (Active()) 
	{
		Translate(-VEC2_UP * speed * gameTimer->DeltaTime(), local);
		Vector2 pos = Pos();

		if (pos.y < -offScreen || pos.y > Graphics::Instance()->windowHeight + offScreen) 
		{
			Reload();
		}
	}
}

void Projectile::Render() 
{
	if (Active())
	{
		sprite->Render();
		PhysicsEntity::Render();
	}
}
