#include "../Headers/PhysicsEntity.h"
#include "../Headers/PhysicsHelper.h"
#include "../Headers/PhysicsManager.h"

PhysicsEntity::PhysicsEntity() 
{
	BPCollider = nullptr;
	mId = 0;
}

PhysicsEntity::~PhysicsEntity() 
{
	for (int i = 0; i < colliders.size(); i++) 
	{
		delete colliders[i];
		colliders[i] = nullptr;
	}
	colliders.clear();

	if (BPCollider) 
	{
		delete BPCollider;
		BPCollider = nullptr;
	}

	if (mId != 0) 
	{
		PhysicsManager::Instance()->UnregisterEntity(mId);
	}		
}

unsigned long PhysicsEntity::GetId()
{
	return mId;
}

bool PhysicsEntity::CheckCollision(PhysicsEntity* other)
{
	if (IgnoreCollisions() || other->IgnoreCollisions())
		return false;
	return ColliderColliderCheck(BPCollider, other->BPCollider);
}

void PhysicsEntity::Hit(PhysicsEntity* other) 
{
}

void PhysicsEntity::AddCollider(Collider* collider, Vector2 localPos) 
{
	collider->Parent(this);
	collider->Pos(localPos);
	colliders.push_back(collider);

	if (colliders.size() > 1 || colliders[0]->GetType() != Collider::ColliderType::Circle) 
	{
		float furthestDist = colliders[0]->GetFurthestPoint().Magnitude();
		float dist = 0.0f;
		for (int i = 1; i < colliders.size(); i++)
		{
			dist = colliders[i]->GetFurthestPoint().Magnitude();
			if (dist > furthestDist) 
			{
				furthestDist = dist;
			}
		}
		delete BPCollider;
		BPCollider = new CircleCollider(furthestDist, true);
		BPCollider->Parent(this);
		BPCollider->Pos(VEC2_ZERO);
	}
}

bool PhysicsEntity::IgnoreCollisions()
{
	return false;
}

void PhysicsEntity::Render() 
{
	for (int i = 0; i < colliders.size(); i++) 
	{
		colliders[i]->Render();
	}
	if (BPCollider)
		BPCollider->Render();
}