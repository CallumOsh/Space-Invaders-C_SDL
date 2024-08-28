#ifndef aEnemyPathFile
#define aEnemyPathFile

#include "MathHelper.h"
#include <vector>

using namespace std;

class EnemyPath 
{

private:
	vector<AlienCurve> curves;
	vector<int> sample;

public:
	EnemyPath();
	~EnemyPath();
	void AddCurve(AlienCurve curve, int samples);
	void Sample(vector<Vector2>* sampledPath);
};
#endif