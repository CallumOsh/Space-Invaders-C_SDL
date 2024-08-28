#include "../Headers/Alien.h"
#include "../Headers/BoxCollider.h"


Alien::Alien(int index, int path, bool challengeStage)
	: Enemy(index, path, challengeStage)
{
	sprites[0] = new Sprite("UFO.png");
	sprites[0]->Parent(this);
	sprites[0]->Rotation(0);
	sprites[0]->Pos(VEC2_ZERO);

	sprites[1] = new Sprite("UFO.png");
	sprites[1]->Parent(this);
	sprites[1]->Rotation(0);
	sprites[1]->Pos(VEC2_ZERO);

	type = alien;
	AddCollider(new BoxCollider(sprites[1]->ScaledDimensions()));
	AddCollider(new BoxCollider(sprites[0]->ScaledDimensions()));
}

Vector2 Alien::LocalFormationPosition()
{
	Vector2 retVal;
	retVal.x = (theLineup->GridSize().x + theLineup->GridSize().x * 2 * (enemyIndex / 4)) * pow(-1, enemyIndex % 2 + 1);
	retVal.y = theLineup->GridSize().y * ((enemyIndex % 4) / 2);
	return retVal;
}

void Alien::HandleDiveState() 
{
}

void Alien::HandleDeadState() 
{
}

void Alien::RenderDiveState() 
{
}

void Alien::RenderDeadState() 
{
}