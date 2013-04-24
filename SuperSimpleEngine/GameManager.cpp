#include "GameManager.h"
#include "FileIO.h"

GameManager::GameManager(void)
{
}


GameManager::~GameManager(void)
{
}

void GameManager::Initialize()
{
	CurrentLevel = FileIO::getInstance().LoadLevel("hole.00.db");
}
