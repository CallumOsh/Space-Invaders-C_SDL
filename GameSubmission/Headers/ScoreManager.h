#ifndef aScoreManagerFile
#define aScoreManagerFile

#include "Sprite.h"
#include <vector>

using namespace std;

class ScoreManager : public GameEntity 
{

private:
	vector<Sprite*> thePlayerScore;
	SDL_Color colour;

public:
	ScoreManager();
	ScoreManager(SDL_Color colour);
	~ScoreManager();
	void Score(int score);
	void Render();

private:
	void ClearPlayerScore();
};
#endif
