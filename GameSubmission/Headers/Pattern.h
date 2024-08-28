#ifndef aPatternFile
#define aPatternFile

#include "GameEntity.h"
#include "GameTimer.h"

class Formation : public GameEntity
{

private:
	GameTimer* gameTimer;

	float offsetNum;
	float offsetTime;
	float offsetDelay;
	int offsetCount;
	int offsetDir;

	float spreadTime;
	float spreadDelay;
	int spreadCount;
	int spreadDir;
	Vector2 gridDimensions;
	bool isLocked;

public:
	Formation();
	~Formation();
	Vector2 GridSize();
	int GetTick();
	void Lock();
	bool Locked();
	void Update();
};
#endif
