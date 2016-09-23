#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <crtdbg.h>
#else
#include <stdlib.h>
#endif // _DEBUG

char* MakeSentence(const char * strings[]) {	
	char * val;	
	int memorySize=0;
	int sourceIndex = 0;
	int secondarySourceIndex = 0;
	while (strings[sourceIndex] != NULL) {
		secondarySourceIndex = 0;
		while (strings[sourceIndex][secondarySourceIndex] != NULL) {
			secondarySourceIndex++;
			memorySize++;
		}
		sourceIndex++;
		memorySize++;
	}
	val = (char*)malloc(memorySize+1);
	sourceIndex = 0;
	secondarySourceIndex = 0;
	int destinationIndex = 0;
	while (strings[sourceIndex] != NULL) {
		secondarySourceIndex = 0;
		while (strings[sourceIndex][secondarySourceIndex] != NULL) {
			val[destinationIndex] = strings[sourceIndex][secondarySourceIndex];
			destinationIndex++;
			secondarySourceIndex++;
		}
		val[destinationIndex] = ' ';
		destinationIndex++;
		sourceIndex++;
	}
	val[memorySize - 1] = '.';
	val[memorySize] = '\0';
	return val;
}
void main( int i_argc, char ** i_argl )
{
	const char * strings[] = {
		"This",
		"is",
		"a",
		"test",
		NULL
	} ;	
	char * pSentence = MakeSentence( strings );

	printf( "The Sentence is: %s", pSentence );
	_getch();
	free( pSentence );
#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}