#include "../Headers/PhysicsManager.h"

PhysicsManager* PhysicsManager::instance = nullptr;

PhysicsManager* PhysicsManager::Instance()
{
	if (instance == nullptr)
		instance = new PhysicsManager();
	return instance;
}

void PhysicsManager::Clean() 
{
	delete instance;
	instance = nullptr;
}

void PhysicsManager::SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags)
{
	mLayerMasks[static_cast<unsigned int>(layer)] = bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(flags));
}

unsigned long PhysicsManager::RegisterEntity(PhysicsEntity* entity, CollisionLayers layer)
{
	colliderLayer[static_cast<unsigned int>(layer)].push_back(entity);
	idLast++;
	return idLast;
}

void PhysicsManager::UnregisterEntity(unsigned long id) 
{
	bool found = false;
	for (int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers) && !found; i++)
	{		
		for (int j = 0; j < colliderLayer[i].size() && !found; j++)
		{			
			if (colliderLayer[i][j]->GetId() == id)
			{
				colliderLayer[i].erase(colliderLayer[i].begin() + j);
				found = true;
			}
		}
	}
}

PhysicsManager::PhysicsManager() 
{
	idLast = 0;
	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++) 
	{
		mLayerMasks[i] = bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(CollisionFlags::None));
	}
}

PhysicsManager::~PhysicsManager()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++) 
	{
		colliderLayer[i].clear();
	}
}

void PhysicsManager::Update() 
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++)
	{
		for (unsigned int j = 0; j < static_cast<unsigned int>(CollisionLayers::MaxLayers); j++)
		{
			if (mLayerMasks[i].test(j) && i <= j)
			{
				for (unsigned int k = 0; k < colliderLayer[i].size(); k++) 
				{
					for (unsigned int l = 0; l < colliderLayer[j].size(); l++) 
					{
						if (colliderLayer[i][k]->CheckCollision(colliderLayer[j][l]))
						{
							colliderLayer[i][k]->Hit(colliderLayer[j][l]);
							colliderLayer[j][l]->Hit(colliderLayer[i][k]);
						}
					}
				}
			}
		}
	}
}