#include "../Headers/GameEntity.h"
#include <stdio.h>

GameEntity::GameEntity(Vector2 pos)
{
	objectPosition = pos;
	objectRotation = 0.0f;
	isActive = true;
	objectParent = NULL;
	objectScale = VEC2_ONE;
}

GameEntity::~GameEntity()
{
	objectParent = NULL;
}

void GameEntity::Pos(Vector2 pos) 
{
	objectPosition = pos;
}

Vector2 GameEntity::Pos(SPACE space)
{
	if (space == local || objectParent == NULL) 
	{
		return objectPosition;
	}
	Vector2 parentScale = objectParent->Scale(world);
	Vector2 roto2 = Vector2(objectPosition.x * parentScale.x, objectPosition.y * parentScale.y);
	float roto2_2 = objectParent->Rotation(local);
	Vector2 rotPos = RotateVector(roto2, roto2_2);
	return objectParent->Pos(world) + rotPos;
}

void GameEntity::Rotation(float r) 
{
	objectRotation = r;

	if (objectRotation > 360.0f)
	{
		int mul = objectRotation / 360;
		objectRotation -= 360.0f * mul;
	}
	else if (objectRotation < 0.0f)
	{
		int mul = (objectRotation / 360) - 1;
		objectRotation -= 360.0f * mul;
	}
}

float GameEntity::Rotation(SPACE space) 
{
	if (space == local || objectParent == NULL)
	{
		return objectRotation;
	}
	return objectParent->Rotation(world) + objectRotation;
}

void GameEntity::Scale(Vector2 scale)
{
	objectScale = scale;
}

Vector2 GameEntity::Scale(SPACE space) 
{
	if (space == local || objectParent == NULL) 
	{
		return objectScale;
	}
	Vector2 scale = objectParent->Scale(world);
	scale.x *= objectScale.x;
	scale.y *= objectScale.y;
	return scale;
}

void GameEntity::Active(bool active)
{
	isActive = active;
}

bool GameEntity::Active() 
{
	return isActive;
}

void GameEntity::Parent(GameEntity* parent) 
{
	if (parent == NULL) 
	{
		objectPosition = Pos(world);
		objectScale = Scale(world);
		objectRotation = Rotation(world);
	}
	else 
	{
		if (objectParent != NULL) 
		{
			Parent(NULL);
		}
		Vector2 parentScale = parent->Scale(world);
		Vector2 rot1 = Pos(world) - parent->Pos(world);
		float rot2 = -parent->Rotation(world);
		objectPosition = RotateVector(rot1, rot2);
		objectPosition.x /= parentScale.x;
		objectPosition.y /= parentScale.y;
		objectRotation = objectRotation - parent->Rotation(world);
		objectScale = Vector2(objectScale.x / parentScale.x, objectScale.y / parentScale.y);
	}
	objectParent = parent;
}

GameEntity* GameEntity::Parent()
{
	return objectParent;
}

void GameEntity::Translate(Vector2 vec, SPACE space) 
{
	if (space == world) {
		objectPosition += vec;
	}
	else
	{
		objectPosition += RotateVector(vec, Rotation());
	}
}

void GameEntity::Rotate(float amount)
{
	objectRotation += amount;
}

void GameEntity::Update()
{
}

void GameEntity::Render()
{
}
