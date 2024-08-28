#ifndef aAlienFile
#define aAlienFile

#include "Enemy.h"

class Alien : public Enemy 
{

private:
	Vector2 LocalFormationPosition();
	void HandleDiveState();
	void HandleDeadState();
	void RenderDiveState();
	void RenderDeadState();

public:
	Alien(int index, int path, bool challengeStage);
};
#endif
