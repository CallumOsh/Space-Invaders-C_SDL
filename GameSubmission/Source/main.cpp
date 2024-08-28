#include "../Headers/GameManager.h"

int main(int argc, char* argv[]) {

	GameManager* gm = GameManager::Instance();
	gm->Run();
	GameManager::Clean();
	gm = NULL;

	return 0;
}