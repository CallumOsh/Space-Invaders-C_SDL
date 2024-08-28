#include "../Headers/EnemyPath.h"

EnemyPath::EnemyPath()
{
}

EnemyPath::~EnemyPath() 
{
}

void EnemyPath::AddCurve(AlienCurve curve, int samples) 
{
	curves.push_back(curve);
	sample.push_back(samples);
}

void EnemyPath::Sample(vector<Vector2>* sampledPath) 
{
	for (int i = 0; i < curves.size(); i++)
	{
		for (float t = 0; t <= 1.0f; t += (1.0f / sample[i])) 
		{
			sampledPath->push_back(curves[i].CalculateCurvePoint(t));
		}
	}
}