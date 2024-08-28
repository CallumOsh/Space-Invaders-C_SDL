#include "../Headers/Collider.h"

Collider::Collider(ColliderType type)
	: type(type)
{
}

Collider::~Collider()
{
}

Collider::ColliderType Collider::GetType() 
{
	return type;
}

void Collider::Render()
{
}