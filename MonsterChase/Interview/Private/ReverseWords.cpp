#include "../ReverseWords.h"

void ReverseWords(char* sentence) {
	int count = 0;
	int wordBeginning = 0;	
	char* startOfWord = nullptr;
	assert(sentence);
	while (sentence[count] != '\0') {
		if (sentence[count] != ' ') {
			count++;
		}
		else {
			int start = wordBeginning;
			int end = count-1;
			while (start < end) {
				char temp = sentence[start];
				sentence[start] = sentence[end];
				sentence[end] = temp;
				start++;
				end--;
			}
			wordBeginning = count + 1;
			count++;
		}
	}
	int start = wordBeginning;
	int end = count-1;
	while (start < end) {
		char temp = sentence[start];
		sentence[start] = sentence[end];
		sentence[end] = temp;
		start++;
		end--;
	}
	wordBeginning = count + 1;
	count++;
}