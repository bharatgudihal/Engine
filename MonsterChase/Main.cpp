#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <vector>
#include <Windows.h>
#include "Memory\Allocators.h"
#include "Core\Engine.h"
#include "Tests\HeapManagerTest.h"
#include "Tests\ConstChecker.h"
#include "Tests\AllocatorTest.h"
#include "Tests\IsNANTest.h"
#include "Tests\MoveCopyTest.h"
#include "Interview\TestReverseWords.h"
#include "Tests\BitArrayUnitTest.h"
#include "Tests\FSATest.h"
#include "Tests\PointerTest.h"
#include "Tests\StringPoolTest.h"
#include "GLibTest\GLibTest.h"
#include "Tests\FileProcessorTest.h"
#include "Tests\MatrixTest.h"
#include "Game.h"

#define _CRTDBG_MAP_ALLOC
//#define TEST
#define GAME
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
//#define POINTERTEST
//#define STRINGPOOLTEST
//#define FILEPROCESSORTEST
//#define MATRIXTEST

using namespace std;

void RunTests(HINSTANCE i_hInstance, int i_nCmdShow);

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow) {
	if (Engine::Core::Startup()) {
#ifdef _DEBUG
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG
#ifdef TEST
		RunTests(i_hInstance, i_nCmdShow);
#endif // TEST
#ifdef GAME
		{
			Game::Game game;
			game.StartGame(i_hInstance, i_nCmdShow);
		}
#endif // GAME
		Engine::Core::ShutDown();
	}
	return 0;
}

void RunTests(HINSTANCE i_hInstance, int i_nCmdShow) {
#ifdef HEAPMANAGERTEST
	Engine::Test::HeapManager_UnitTest();
#endif
#ifdef CONSTTEST
	Engine::Test::ConstChecker();
#endif
#ifdef ALLOCATORTEST
	Engine::Test::startAllocatorTest();
#endif
#ifdef FLOATCHECKTEST
	Engine::Test::TestNAN();
#endif // FLOATCHECKTEST
#ifdef MOVECOPYTEST
	Engine::Test::MoveCopyTest();
#endif // MOVECOPYTEST
#ifdef TESTREVERSEWORDS
	TestReverseWords();
#endif // TESTREVERSEWORDS
#ifdef BITARRAYTEST
	Engine::Test::BitArray_UnitTest();
#endif
#ifdef FSATEST
	Engine::Test::FSAUnitTest();
#endif
#ifdef GLIBTEST
	GLibTest(i_hInstance, i_nCmdShow);
#endif
#ifdef POINTERTEST
	Engine::Test::TestPointers();
#endif // POINTERTEST
#ifdef STRINGPOOLTEST
	Engine::Test::TestStringPool();
#endif // STRINGPOOLTEST
#ifdef FILEPROCESSORTEST
	Engine::Test::FileProcessorTest fileProcessorTest;
	fileProcessorTest.TestFileProcessor();
#endif // FILEPROCESSORTEST
#ifdef  MATRIXTEST
	Engine::Test::TestMatrix();
#endif //  MATRIXTEST

}