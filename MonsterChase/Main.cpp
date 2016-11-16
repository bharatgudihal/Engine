#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "Player\Player.h"
#include "Math\Vector2D.h"
#include "Monster\Monster.h"
#include "MonsterChase.h"
#include "Logger\Logger.h"
#include "Monster\MonsterController.h"
#include "Tests\HeapManagerTest.h"
#include "Tests\ConstChecker.h"
#include "Tests\AllocatorTest.h"
#include "Memory\Allocators.h"
#define _CRTDBG_MAP_ALLOC
//#define HEAPMANAGERTEST
//#define CONSTTEST
#define ALLOCATORTEST
//#define MONSTERCHASE
using namespace std;
using namespace Engine;

bool CheckInput(const char c) {
	if (c != 'A' && c != 'a' && c != 'W' && c != 'w' && c != 'S' && c != 's' && c != 'D' && c != 'd' && c == 'Q' && c == 'q') {
		DEBUG_LOG("input entered %c ", c);		
		printf("\\(O_O)/\n");
		printf("Wrong Input! Read the instructions and try again dummy!\n");
		return false;
	}
	return true;
}

int main() {
	void* heapManagerMemory = _aligned_malloc(sizeof(HeapManager),4);
	HeapManager* heapManager = HeapManager::create(heapManagerMemory, 1024, 16);
	getDefaultHeapManager(heapManager);
	Engine::Actor* actor = new Engine::Actor("Test", Vector2D::ZERO);
	assert(actor);
	delete actor;
	#ifdef _DEBUG
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif // _DEBUG
#ifdef HEAPMANAGERTEST
	HeapManager_UnitTest();		
#endif
#ifdef CONSTTEST
	ConstChecker();
#endif
#ifdef ALLOCATORTEST
	startAllocatorTest();
#endif
#ifdef MONSTERCHASE
	MonsterChase monsterChase;
	printf("Please enter the number of monsters you want to start with: ");
	int monsterCount;
	scanf_s("%d", &monsterCount);
	assert(monsterCount >= 1);
	while (monsterCount > 50) {
		DEBUG_LOG("monsterCount entered %d ", monsterCount);
		printf("Do you really think you can escape so many monsters?\nTry something smaller: ");
		scanf_s("%d", &monsterCount);
		assert(monsterCount >= 1);
	}
	Engine::Actor monsterArray[50];
	for (int i = 0; i < monsterCount; i++) {
		printf("Enter the name of monster %d: ", i);
		char monsterName[20];
		scanf_s("%s", monsterName, 20);
		monsterArray[i] = Monster(monsterName, Vector2D((float)(rand() % monsterChase.GRIDSIZE), (float)(rand() % monsterChase.GRIDSIZE)));
	}
	printf("Enter the player's name: ");
	char playerName[20];
	scanf_s("%s", playerName, 20);
	Engine::Actor player = Engine::Actor(playerName,Vector2D(0,0));
	PlayerController playerController;
	playerController.SetActor(&player);
	bool quitGame = false;
	while (true) {
		for (int i = 0; i < monsterCount; i++) {
			printf("Monster %s at [%f,%f]\n", monsterArray[i].getName(), monsterArray[i].getPosition().X(), monsterArray[i].getPosition().Y());
		}
		printf("Player %s at [%f,%f]\n", player.getName(), player.getPosition().X(), player.getPosition().Y());
		printf("Use the W,A,S,D keys to move. Press Q to quit.\n");
		char c;
		c = _getch();
		while (!CheckInput(c)) {
			c = _getch();
		}
		if (c == 'Q' || c == 'q') {
			break;
		}
		playerController.Update(c);
		monsterChase.UpdateMonsterLocation(monsterArray, monsterCount, &player);
		monsterChase.CheckMonsterToMonsterCollision(monsterArray, monsterCount);
		if (monsterChase.CheckPlayerToMonsterCollision(&player, monsterArray, monsterCount)) {
			printf("Press any button to exit.");
			_getch();
			break;
		}
	}
#endif
	delete heapManager;
	_CrtDumpMemoryLeaks();
	return 0;
}