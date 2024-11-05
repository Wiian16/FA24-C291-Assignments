/*
Author: Ian McGillivary
Program Name: Buffer Indexing

This program will read up to 2048 bytes from stdin or until the EOF is reached and store the input into a buffer, then
produce a report with all unique words to stdout. For each word in the report, the following information will be
included: begin index, length, end index, and the word itself. The report will also contain the total bytes processed, 
total unique words, and total words found. For this program a word is defined as a any sequence of non-whitespace 
characters and the null byte (\0) is not defined as a whitesace character.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define BUFFER_SIZE 2048


struct UniqueWord{
    char * word;
    int begin;
    int count;
};

struct Word{
    char * word;
    int begin;
};


int getBuffer(char *);
size_t findAllWords(char *, struct Word *);
size_t findAllUniqueWords(struct Word *, struct UniqueWord *, size_t);
int indexOfUniqueWord(struct UniqueWord *, char * word, size_t);
void printReport(struct UniqueWord *, size_t, char *, size_t, size_t);
void printString(char *);


int main(void){
    char * buffer = calloc(BUFFER_SIZE + 1, sizeof(char));

    size_t bufferSize = getBuffer(buffer);

    struct Word * wordList = malloc(1024 * sizeof(struct Word));

    size_t wordListSize = findAllWords(buffer, wordList);

    struct UniqueWord * uniqueWordList = malloc(1024 * sizeof(struct UniqueWord));
    
    size_t uniqueWordListSize = findAllUniqueWords(wordList, uniqueWordList, wordListSize);

    printReport(uniqueWordList, uniqueWordListSize, buffer, wordListSize, bufferSize);;
}

/*
This function will fill a given buffer array with characters until it is full or EOF is reached

Arguments:
    char * buffer: Character array to fill from stdin

Returns:
    char *: buffer array filled from stdin
*/
// POINTER ARITHMETIC
int getBuffer(char * buffer){
    int i = 0;
    while (!feof(stdin) && i < BUFFER_SIZE){
        if(!fread(buffer + i, sizeof(char), 1, stdin)){
            break;
        }

        if(buffer[i] == '\0'){
           buffer[i] = 27;
        }

        i++;
    }

    return i;
} 

//Fills wordList with all words found in buffer and returns the filled size of wordList
size_t findAllWords(char * buffer, struct Word * wordList){
    size_t size = 0;
    char * word = malloc(BUFFER_SIZE * sizeof(char));
    word[0] = '\0';
    int begin = -1;

    int i;
    for(i = 0; i < BUFFER_SIZE; i++){
        if(isspace(buffer[i])){
            if(strlen(word) != 0){
                wordList[size].word = malloc(strlen(word) * sizeof(char));
                strcpy(wordList[size].word, word);
                wordList[size].begin = begin;

                size++;

                word[0] = '\0';
                begin = -1;
            }
        }
        else{
            size_t len = strlen(word);
            word[len] = buffer[i];
            word[len + 1] = '\0';

            if(begin == -1){
                begin = i;
            }
        }
    }

    if(strlen(word) != 0){
        wordList[size].word = malloc(strlen(word) * sizeof(char));
        strcpy(wordList[size].word, word);
        wordList[size].begin = begin;
        size++;
    }

    return size;
}

//Fills uniqueWordList with all unique words from wordList and returns the filled size of uniqueWordList
size_t findAllUniqueWords(struct Word * wordList, struct UniqueWord * uniqueWordList, size_t size){
    int uniqueSize = 0;

    for(int i = 0; i < size; i++){
        int index = indexOfUniqueWord(uniqueWordList, wordList[i].word, uniqueSize);
        if(index == -1){
            uniqueWordList[uniqueSize].word = malloc(strlen(wordList[i].word) * sizeof(char *));
            strcpy(uniqueWordList[uniqueSize].word, wordList[i].word);
            uniqueWordList[uniqueSize].begin = wordList[i].begin;
            uniqueWordList[uniqueSize].count = 1;
            uniqueSize++;
        }
        else{
            uniqueWordList[index].count++;
        }
    }

    return uniqueSize;
}

//Returns the index of the given word
int indexOfUniqueWord(struct UniqueWord * uniqueWordList, char * word, size_t size){
    for(int i = 0; i < size; i++){
        if(strcmp(uniqueWordList[i].word, word) == 0){
            return i;
        }
    }
    return -1;
}


void printReport(struct UniqueWord * uniqueWordList, size_t size, char * buffer, size_t wordListSize,
        size_t bufferSize){
    printf("%-10s%-10s%-10s%-s\n", "BEGIN", "LENGTH", "COUNT", "WORD");

    for(int i = 0; i < size; i++){
        printf("%-10d%-10d%-10d", uniqueWordList[i].begin, (int) strlen(uniqueWordList[i].word),
                uniqueWordList[i].count);
        printString(uniqueWordList[i].word);
        printf("\n");
    }

    printf("Total bytes processed: %lu\n", bufferSize);
    printf("Total Unique Words: %lu\n", size);
    printf("Total words found: %lu\n", wordListSize);
}

//Prints a given string to stdout, but replaces the esc character (27) with the null byte
void printString(char * word){
    int i = 0;
    while(word[i] != 0){
        if(word[i] != 27){
            printf("%c", word[i]);
        }
        else{
            printf("%c", '\0');
        }

        i++;
    }
}
