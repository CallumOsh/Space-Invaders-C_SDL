#ifndef aProjectileFile
#define aProjectileFile

#include "GameTimer.h"
#include "PhysicsEntity.h"

class Projectile : public PhysicsEntity 
{

private:
	const int offScreen = 10;
	GameTimer* gameTimer;
	float speed;
	Sprite* sprite;
	bool IgnoreCollisions() override;

public:
	Projectile(bool friendly);
	~Projectile();
	void Fire(Vector2 pos);
	void Reload();
	void Hit(PhysicsEntity* other) override;
	void Update();
	void Render();
};
#endif
