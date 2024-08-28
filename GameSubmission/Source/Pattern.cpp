#include "../Headers/Pattern.h"

Formation::Formation() 
{
	gameTimer = GameTimer::Instance();

	offsetNum = 10.0f;
	offsetDelay = 0.4f;
	offsetTime = 0.0f;
	offsetCount = 4;
	offsetDir = 1;
	spreadTime = 0.0f;
	spreadDelay = 0.6f;
	spreadCount = 0;
	spreadDir = 1;

	isLocked = false;
	gridDimensions = Vector2(32.0f, 64.0f);
}

Formation::~Formation() 
{
	gameTimer = NULL;
}


Vector2 Formation::GridSize()
{
	return gridDimensions;
}

int Formation::GetTick()
{
	if (!isLocked || offsetCount != 4)
		return offsetCount;
	else
		return spreadCount;
}

void Formation::Lock() 
{
	isLocked = true;
}

bool Formation::Locked()
{
	return isLocked && offsetCount == 4;
}

void Formation::Update() 
{
	if (!isLocked || offsetCount != 4) 
	{
		offsetTime += gameTimer->DeltaTime();
		if (offsetTime >= offsetDelay)
		{
			offsetCount++;
			Translate(VEC2_RIGHT * offsetDir * offsetNum, world);

			if (offsetCount == 8) 
			{
				offsetCount = 0;
				offsetDir *= -1;
			}
			offsetTime = 0.0f;
		}
	}
	else 
	{
		spreadTime += gameTimer->DeltaTime();
		if (spreadTime >= spreadDelay) 
		{
			spreadCount += spreadDir;
			gridDimensions.x += (spreadDir * ((spreadCount % 2 == 0) ? 1 : 2));
			if (spreadCount == 4 || spreadCount == 0) 
			{
				spreadDir *= -1;
			}
			spreadTime = 0.0f;
		}
	}
}