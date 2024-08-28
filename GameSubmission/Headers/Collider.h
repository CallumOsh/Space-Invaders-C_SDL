#ifndef aColliderFile
#define aColliderFile

#include "Sprite.h"

class Collider : public GameEntity 
{

public:
	enum class ColliderType 
	{
		Box,
		Circle
	};

protected:
	ColliderType type;

public:
	Collider(ColliderType type);
	virtual ~Collider();
	virtual Vector2 GetFurthestPoint() = 0;
	ColliderType GetType();
	virtual void Render();
};
#endif