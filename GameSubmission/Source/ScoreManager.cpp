#include "../Headers/ScoreManager.h"

ScoreManager::ScoreManager()
	: ScoreManager({ 230, 230, 230 })
{
}

ScoreManager::ScoreManager(SDL_Color color) 
{
	colour = color;
	Score(0);
}

ScoreManager::~ScoreManager() 
{
	ClearPlayerScore();
}

void ScoreManager::ClearPlayerScore()
{
	for (int i = 0; i < thePlayerScore.size(); i++)
	{
		delete thePlayerScore[i];
		thePlayerScore[i] = NULL;
	}
	thePlayerScore.clear();
}

void ScoreManager::Score(int score)
{
	ClearPlayerScore();
	if (score == 0) 
	{
		for (int i = 0; i < 1; i++) 
		{
			thePlayerScore.push_back(new Sprite("0", "VT323-Regular.ttf", 32, colour));
			thePlayerScore[i]->Parent(this);
			thePlayerScore[i]->Pos(Vector2(-32.0f * i, 0.0f));
		}
	}
	else 
	{
		string str = to_string(score);
		int lastIndex = (int)str.length() - 1;

		for (int i = 0; i <= lastIndex; i++) 
		{
			thePlayerScore.push_back(new Sprite(str.substr(i, 1), "VT323-Regular.ttf", 32, colour));
			thePlayerScore[i]->Parent(this);
			thePlayerScore[i]->Pos(Vector2(-32.0f * (lastIndex - i), 0.0f));
		}
	}
}

void ScoreManager::Render()
{
	for (int i = 0; i < thePlayerScore.size(); i++)
		thePlayerScore[i]->Render();
}