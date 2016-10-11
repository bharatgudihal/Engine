#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

const int ARRAY_SIZE = 500;
const int WORD_SIZE = 25;

char* MakeSentence(char * strings[]) {	
	char * sentence;	
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
	sentence = (char*)malloc(memorySize+1);
	sourceIndex = 0;
	secondarySourceIndex = 0;
	int destinationIndex = 0;
	while (strings[sourceIndex] != NULL) {
		secondarySourceIndex = 0;
		while (strings[sourceIndex][secondarySourceIndex] != NULL) {
			sentence[destinationIndex] = strings[sourceIndex][secondarySourceIndex];
			destinationIndex++;
			secondarySourceIndex++;
		}
		sentence[destinationIndex] = ' ';
		destinationIndex++;
		sourceIndex++;
	}
	sentence[memorySize - 1] = '.';
	sentence[memorySize] = '\0';
	return sentence;
}

char * RemoveNewLine(char* input) {
	char* output = input;
	int index = 0;
	while(output[index] != '\n'){
		index++;
	}
	output[index] = '\0';
	return output;
}

void main( int i_argc, char ** i_argl )
{
	char * strings[ARRAY_SIZE];
	int index = 0;
	int size;
	printf("Enter a words for your one by one sentence. If you want to end it, just press ENTER\n");
	char* input;
	while (true) {
		input = (char*)malloc(WORD_SIZE);
		fgets(input, WORD_SIZE,stdin);
		if (input[0] != '\n') {
			strings[index] = RemoveNewLine(input);
			index++;
		}
		else {
			strings[index] = NULL;
			break;
		}
	}
	size = index;
	char * pSentence = MakeSentence( strings );
	printf( "The Sentence is: %s", pSentence );
	_getch();
	free( pSentence );
	free(input);
	for (index = 0; index < size; index++) {
		free(strings[index]);
	}
#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}
