#include "../Headers/Enemy.h"
#include "../Headers/PhysicsManager.h"

vector<vector<Vector2>> Enemy::paths;
Formation* Enemy::theLineup = NULL;
Player* Enemy::thePlayer = nullptr;

void Enemy::CreatePaths()
{
	int screenMidPoint = Graphics::Instance()->windowWidth * 0.4f;
	int currentPath = 0;
	EnemyPath* path = new EnemyPath();
	path->AddCurve({ Vector2(screenMidPoint + 50.0f, -10.0f), Vector2(screenMidPoint + 50.0f, -20.0f), Vector2(screenMidPoint + 50.0f, 30.0f), Vector2(screenMidPoint + 50.0f, 20.0f) }, 1);
	path->AddCurve({ Vector2(screenMidPoint + 50.0f, 20.0f), Vector2(screenMidPoint + 50.0f, 100.0f), Vector2(75.0f, 325.0f), Vector2(75.0f, 425.0f) }, 25);
	path->AddCurve({ Vector2(75.0f, 425.0f), Vector2(75.0f, 650.0f), Vector2(325.0f, 650.0f), Vector2(350.0f, 425.0f) }, 25);

	paths.push_back(vector<Vector2>());
	path->Sample(&paths[currentPath]);
	delete path;
}

void Enemy::CurrentPlayer(Player* player) 
{
	thePlayer = player;
}

void Enemy::SetFormation(Formation* f) 
{
	theLineup = f;
}

Enemy::Enemy(int index, int path, bool challengeStage) 
{
	gameTimer = GameTimer::Instance();
	currentPath = path;
	currentState = flyIn;

	currentPathPos = 1;
	Pos(paths[currentPath][0]);

	sprites[0] = NULL;
	sprites[1] = NULL;
	speed = 400.0f;
	enemyIndex = index;
	challengeStage = challengeStage;

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);
}

Enemy::~Enemy()
{
	gameTimer = NULL;
	for (int i = 0; i < 2; i++)
	{
		delete sprites[i];
		sprites[i] = NULL;
	}
}

void Enemy::PathComplete()
{
	if (challengeStage)
		currentState = dead;
}

void Enemy::JoinFormation() 
{
	Pos(WorldFormationPosition());
	Parent(theLineup);
	currentState = formation;
}

Vector2 Enemy::WorldFormationPosition()
{
	return theLineup->Pos() + LocalFormationPosition();
}

void Enemy::FlyInComplete()
{
	if (challengeStage)
		currentState = dead;
	else
		JoinFormation();
}

void Enemy::HandleFlyInState() 
{
	if (currentPathPos < paths[currentPath].size())
	{
		Vector2 dist = paths[currentPath][currentPathPos] - Pos();
		Translate(dist.Normalized() * gameTimer->DeltaTime() * speed, world);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if ((paths[currentPath][currentPathPos] - Pos()).MagnitudeSqr() < EPSILON)
			currentPathPos++;
		if (currentPathPos >= paths[currentPath].size())
			PathComplete();
	}
	else
	{
		Vector2 dist = WorldFormationPosition() - Pos();
		Translate(dist.Normalized() * gameTimer->DeltaTime() * speed, world);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);
		if (dist.MagnitudeSqr() < EPSILON)
			FlyInComplete();
	}
}

void Enemy::HandleFormationState()
{
	Pos(LocalFormationPosition());
}

void Enemy::HandleDeadState() 
{
}

void Enemy::HandleStates()
{
	switch (currentState) 
	{
	case flyIn:
		HandleFlyInState();
		break;
	case formation:
		HandleFormationState();
		break;
	case dive:
		HandleDiveState();
		break;
	case dead:
		HandleDeadState();
		break;
	}
}

void Enemy::RenderFlyInState()
{
	sprites[0]->Render();
}

void Enemy::RenderFormationState() 
{
	sprites[theLineup->GetTick() % 2]->Render();
}

void Enemy::Hit(PhysicsEntity* other)
{
	if (currentState == formation)
	{
		Parent(nullptr);
	}
	currentState = dead;
	AudioManager::Instance()->PlayGameEffects("EnemyExplosion.wav");
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[Enemy Deleted, Explosion SOund Played]");
	thePlayer->AddScore(10);
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "[Player Score Increased by 10]");
}

void Enemy::RenderDeadState() 
{
}

void Enemy::RenderStates()
{
	switch (currentState) 
	{
	case flyIn:
		RenderFlyInState();
		break;
	case formation:
		RenderFormationState();
		break;
	case dive:
		RenderDiveState();
		break;
	case dead:
		RenderDeadState();
		break;
	}
	PhysicsEntity::Render();
}

bool Enemy::IgnoreCollisions()
{
	return currentState == dead;
}

Enemy::STATES Enemy::CurrentState() 
{
	return currentState;
}

Enemy::TYPES Enemy::Type() 
{
	return type;
}

void Enemy::Dive()
{
	Parent(NULL);
	currentState = dive;
	fallStartPos = Pos();
	currentPathPos = 1;
}

void Enemy::Update() 
{
	if (Active())
		HandleStates();
}

void Enemy::Render() 
{
	if (Active())
		RenderStates();
}