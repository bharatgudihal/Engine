#include "../TestReverseWords.h"

bool TestReverseWords() {
	char test1[] = { 'H','e','l','l','o',' ','w','o','r','l','d','\0' };
	printf("Normal string: %s\n",test1);
	ReverseWords(test1);
	printf("Reversed string: %s\n", test1);
	char test2[] = { 'H','i',' ','t','h','e','r','e','\0' };
	printf("Normal string: %s\n", test2);
	ReverseWords(test2);
	printf("Reversed string: %s\n", test2);
	char test3[] = { 'H','e','l','l','o','\0' };
	printf("Normal string: %s\n", test3);
	ReverseWords(test3);
	printf("Reversed string: %s\n", test3);
	char test4[] = { 'H','\0' };
	printf("Normal string: %s\n", test4);
	ReverseWords(test4);
	printf("Reversed string: %s\n", test4);
	_getch();
	return true;
}