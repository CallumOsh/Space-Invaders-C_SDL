#ifndef aCircleColliderFile
#define aCircleColliderFile

#include "Collider.h"

class CircleCollider :public Collider 
{

private:
	float mRadius;

public:
	CircleCollider(float radius, bool breadPhase = false);
	~CircleCollider();
	Vector2 GetFurthestPoint() override;
	float GetRadius();
};
#endif
