#ifndef aPhysicsFile
#define aPhysicsFile

#include <vector>
#include "Collider.h"

using namespace std;

class PhysicsEntity :public GameEntity 
{

protected:
	unsigned long mId;
	vector<Collider*> colliders;
	Collider* BPCollider;

public:
	PhysicsEntity();
	virtual ~PhysicsEntity();
	unsigned long GetId();
	bool CheckCollision(PhysicsEntity* other);
	virtual void Hit(PhysicsEntity* other);
	virtual void Render();

protected:
	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);
	virtual bool IgnoreCollisions();
};
#endif