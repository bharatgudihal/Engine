#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <vector>
#include <Windows.h>
#include "Player\Player.h"
#include "Math\Vector2D.h"
#include "Monster\Monster.h"
#include "MonsterChase.h"
#include "Logger\Logger.h"
#include "Monster\MonsterController.h"
#include "Memory\Allocators.h"
#include "Memory\MasterMemoryManager.h"
#include "Tests\HeapManagerTest.h"
#include "Tests\ConstChecker.h"
#include "Tests\AllocatorTest.h"
#include "Tests\IsNANTest.h"
#include "Tests\MoveCopyTest.h"
#include "Interview\TestReverseWords.h"
#include "Tests\BitArrayUnitTest.h"
#include "Tests\FSATest.h"
#include "GLibTest\GLibTest.h"
#include "Timer\CoreTimer.h"

#define _CRTDBG_MAP_ALLOC
//#define HEAPMANAGERTEST
//#define CONSTTEST
//#define ALLOCATORTEST
//#define FLOATCHECKTEST
//#define MOVECOPYTEST
//#define TESTREVERSEWORDS
//#define BITARRAYTEST
//#define FSATEST
//#define MONSTERCHASE
//#define GLIBTEST

using namespace std;
using namespace Engine;

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow) {
	if (MasterMemoryManager::Startup()) {
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
#ifdef FLOATCHECKTEST
		TestNAN();
#endif // FLOATCHECKTEST
#ifdef MOVECOPYTEST
		MoveCopyTest();
#endif // MOVECOPYTEST
#ifdef TESTREVERSEWORDS
		TestReverseWords();
#endif // TESTREVERSEWORDS
#ifdef BITARRAYTEST
		BitArray_UnitTest();
#endif
#ifdef FSATEST
		FSAUnitTest();
#endif
#ifdef MONSTERCHASE
		playMonsterChase();
#endif
#ifdef GLIBTEST
		GLibTest(i_hInstance, i_nCmdShow);
#endif
		while (1) {
			float time = CoreTimer::GetDeltaTime();
			DEBUG_LOG("%f \n", time);
		}
		MasterMemoryManager::ShutDown();
	}
	return 0;
}