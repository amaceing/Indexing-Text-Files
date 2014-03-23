#include <iostream>
#include <fstream>
using namespace std;

struct IndexPair {
	char *word;
	int lineNumber;
};

char *getFileName();
void strCopy(char string[], char *pointer);
int strLength(char * word);
int fillStringArray(char *linesInFile[]);
int fillIndexArray(int numberOfLines, char *linesInFile[],
							IndexPair* pairArray[]);
int countLettersInWord(char *originalString);
char *parseString(char *originalString, int count);
bool isWhiteSpace(char *originalString);
IndexPair *createPair(char *word, int lineNumber);
void copyIndexPairArray(IndexPair *source[], IndexPair *destination[],
						int numPairs);
char getFirstLetter(char *word);
void swapIndexPairs(IndexPair *first, IndexPair *second);
int strCompare(char *word, char *possibleMatch);
void sortIndexPairArray(IndexPair *sort[], int numPairs);

int main() {
	char *fileLines[100];
	IndexPair *pairArray[1000];
	IndexPair *sortedPairArray[1000];
	int lines = fillStringArray(fileLines);
	int numberOfPairs = fillIndexArray(lines, fileLines, pairArray);
	copyIndexPairArray(pairArray, sortedPairArray, numberOfPairs);
	for (int i = 0; i < numberOfPairs; i++) {
		cout << sortedPairArray[i]->word << ", " << sortedPairArray[i]->lineNumber << endl;
	}
	cout << endl;
	char *testA = "HiBro";
	char *testB = "HeyBro";
	char *testC = "HiBro";
	sortIndexPairArray(sortedPairArray, numberOfPairs);
	for (int h = 0; h < numberOfPairs; h++) {
		cout << sortedPairArray[h]->word << ", " << sortedPairArray[h]->lineNumber << endl;
	}
	return 0;
}

int fillStringArray(char *linesInFile[]) {
	fstream infile;
	int lines = 0;
	int lineLength = 0;
	char *fileName = getFileName();
	char lineCString[100];
	char *lineStringPointer; 
	infile.open(fileName, ios::in);
	if (infile.fail()) {
		cout << "File open failure on file " << fileName << " ..." << endl << endl;
	} else {
		while (!infile.eof()) {
			lines++;
			infile.getline(lineCString, 100);
			lineLength = strLength(lineCString);
			lineStringPointer = new char[lineLength + 1];
			strCopy(lineCString, lineStringPointer);
			*linesInFile = lineStringPointer;
			linesInFile++;
		}
	}
	return lines;
}

int fillIndexArray(int numberOfLines, char *linesInFile[],
							IndexPair *pairArray[]) {	
	int numberOfPairs = 0;
	int pairArrayIndex = 0;
	for (int i = 0; i < numberOfLines; i++) {
		char *lineFromFile = linesInFile[i];
		while (*lineFromFile) {
			if (isWhiteSpace(lineFromFile)) {
				lineFromFile++;
			} else {				
				int count = countLettersInWord(lineFromFile);
				char *wordForPair = parseString(lineFromFile, count);
				IndexPair *pair = createPair(wordForPair, i);
				pairArray[pairArrayIndex] = pair;
				lineFromFile += count;
				numberOfPairs++;
				pairArrayIndex++;
			}
		}
	}
	return numberOfPairs;
}

void sortIndexPairArray(IndexPair *sort[], int numPairs) {
	for (int j = 0; j < numPairs; j++) {
		int index, last, sorted;
		last = numPairs - 1;
		do {
			sorted = 1;
			for (index = 0; index < last; index++) {
				char *firstWord = sort[index]->word;
				char *secondWord = sort[index + 1]->word;
				int compare = strCompare(firstWord, secondWord);
				if (compare == 1) {
					swapIndexPairs(sort[index], sort[index+1]);
					sorted = 0;
				}
			}
			last--;
		} while (!sorted);
	}
}

char *getFileName() {
	char file[81];
	cout << "Please enter the name of the file" << endl << endl;
	cin >> file;
	int fileNameLength = strLength(file);
	char *fileName = new char[fileNameLength + 1];
	char *fileNameBase = fileName;
	strCopy(file, fileName);
	return fileNameBase;
}

void strCopy(char cString[], char *stringPointer) {
	int index;
	for (index = 0; cString[index]; index++) {
		*stringPointer = cString[index];
		stringPointer++;
	}
	*stringPointer = '\0';
}

void copyIndexPairArray(IndexPair *source[], IndexPair *destination[], 
						int numPairs) {
	for (int i = 0; i < numPairs; i++) {
		destination[i] = source[i];
	}
}

char getFirstLetter(char *word) {
	return *word;
}

void swapIndexPairs(IndexPair *first, IndexPair *second) {
	IndexPair temp = *first;
	*first = *second;
	*second = temp;
}

IndexPair *createPair(char *word, int lineNumber) {
	IndexPair *pair = new IndexPair();
	pair->word = word;
	pair->lineNumber = lineNumber + 1;
	return pair;
}

int countLettersInWord(char *originalString) {
	int letterCount = 0;
	while (*originalString != ' ' && *originalString != '\t' 
		   && *originalString != '\n' && *originalString) {
		letterCount++;
		originalString++;
	}
	return letterCount;
}

bool isWhiteSpace(char *originalString) {
	return (*originalString == ' ' || *originalString == '\t'
			|| *originalString == '\n');
}

char *parseString(char *originalString, int count) {
	char *wordForPair = new char[count + 1];
	char *baseWordForPair = wordForPair;
	for (int i = 0; i < count; i++) {
		if (*originalString >= 'A' && *originalString <= 'Z') {
			*wordForPair = *originalString + ('a' - 'A');
		} else {
			*wordForPair = *originalString;
		}
		wordForPair++;
		originalString++;
	}
	*wordForPair = '\0';
	return baseWordForPair;
}

int strCompare(char *firstWord, char *secondWord) {
	while (*firstWord && *secondWord && (*firstWord == *secondWord)) {
		firstWord++;
		secondWord++;
	}
	if (*firstWord < *secondWord) {
		return -1;
	} else if (*firstWord > *secondWord) {
		return 1;
	}
	return 0;
}

int strLength(char * word) {
	char *base = word;
	while (*word) {
		word++;
	}
	return (word - base);
}