#ifndef aEnemyFile
#define aEnemyFile

#include "AnimatedSprite.h"
#include "EnemyPath.h"
#include "Pattern.h"
#include "PhysicsEntity.h"
#include "Player.h"

using namespace std;

class Enemy : public PhysicsEntity
{

public:
	enum STATES { flyIn, formation, dive, dead };
	enum TYPES { alien };

protected:
	static vector<vector<Vector2>> paths;
	static Formation* theLineup;
	static Player* thePlayer;


	GameTimer* gameTimer;
	Sprite* sprites[2];
	STATES currentState;

	int currentPath;
	int currentPathPos;
	const float EPSILON = 15.0f;
	float speed;

	TYPES type;
	int enemyIndex;
	bool challengeStage;
	Vector2 fallStartPos;

protected:
	virtual void PathComplete();
	virtual void FlyInComplete();
	void JoinFormation();
	virtual Vector2 WorldFormationPosition();
	virtual Vector2 LocalFormationPosition() = 0;

	virtual void HandleFlyInState();
	virtual void HandleFormationState();
	virtual void HandleDiveState() = 0;
	virtual void HandleDeadState();
	void HandleStates();

	virtual void RenderFlyInState();
	virtual void RenderFormationState();
	virtual void RenderDiveState() = 0;
	virtual void RenderDeadState();
	void RenderStates();
	bool IgnoreCollisions() override; 


public:
	static void SetFormation(Formation* f);
	static void CurrentPlayer(Player* player);
	static void CreatePaths();
	Enemy(int index, int path, bool challengeStage);
	virtual ~Enemy();
	virtual void Hit(PhysicsEntity* other) override;
	STATES CurrentState();
	TYPES Type();
	void Dive();
	void Update();
	void Render();
};
#endif