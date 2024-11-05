/*
Author: Ian McGillivary
Program Name: Buffer Indexing

This program will read up to 2048 bytes from stdin or until the EOF is reached and store the input into a buffer, then
produce a report with all unique words to stdout. For each word in the report, the following information will be
included: begin index, length, end index, and the word itself. The report will also contain the total bytes processed, 
total unique words, and total words found. For this program a word is defined as a any sequence of non-whitespace 
characters and the null byte (\0) is not defined as a whitesace character.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 2048


void getBuffer(char *);
size_t findAllWords(char *, char **);
int countUniqueWords(char **, size_t);
int indexOf(char **, char *, size_t);
void fillUniqueWords(char **, char **, size_t);


int main(void){
    char * buffer = calloc(BUFFER_SIZE + 1, sizeof(char));

    getBuffer(buffer);

    printf("Buffer = %s\n", buffer);
    
    char *** indexArr = malloc(8 * sizeof(char **));
    for(int i = 0; i < 8; i++){
        indexArr[i] = malloc(4 * sizeof(char *));
    }

    char ** wordsArr = malloc(1024 * sizeof(char *));

    size_t wordsSize = findAllWords(buffer, wordsArr);
    printf("words = %lu\n", wordsSize);
    
    for(int i = 0; i < wordsSize; i++){
        printf("%s, ", wordsArr[i]);
    }

    printf("\n");

    int uniqueCount = countUniqueWords(wordsArr, wordsSize);

    printf("Unique words = %d\n", uniqueCount);
    
    char ** uniqueWordsArr = malloc(uniqueCount * sizeof(char *));
    fillUniqueWords(wordsArr, uniqueWordsArr, wordsSize);
    
    for(int i = 0; i < uniqueCount; i++){
        printf("%s, ", uniqueWordsArr[i]);
    }

    printf("\n");
}

/*
This function will fill a given buffer array with characters until it is full or EOF is reached

Arguments:
    char * buffer: Character array to fill from stdin

Returns:
    char *: buffer array filled from stdin
*/
// POINTER ARITHMETIC
void getBuffer(char * buffer){
    printf("Input characters into the buffer:\n");

    int i = 0;
    while (!feof(stdin) && i < BUFFER_SIZE){
        if(!fread(buffer + i, sizeof(char), 1, stdin)){
            break;
        }

        i++;
    }

    printf("\nDone filling\n");
    printf("Buffer Length = %d\n", i);
} 

/*
This function will find all the words in buffer and return them in an array
   */
size_t findAllWords(char * buffer, char ** wordsArr){
    size_t size = 0;
    char * word = malloc(2048 * sizeof(char));
    word[0] = '\0';

    for(int i = 0; i < BUFFER_SIZE; i++){
        if(isspace(buffer[i])){
            if(strlen(word) != 0){
                wordsArr[size] = malloc(strlen(word) * sizeof(char));
                strcpy(wordsArr[size], word);

                size++; 

                word[0] = '\0';
            } 
        }
        else{
            size_t len = strlen(word);
            word[len] = buffer[i];
            word[len + 1] = '\0';
        }
    }

    if(strlen(word) != 0){
        wordsArr[size] = malloc(sizeof(word));
        strcpy(wordsArr[size], word);
        size++;
    }

    return size;
}

/*
Returns the number of unique words in the given words array
   */
int countUniqueWords(char ** wordsArr, size_t size){
    int uniqueCount = 0;

    char ** uniqueArr = malloc(size * sizeof(char *));

    for(int i = 0; i < size; i++){
        if(indexOf(uniqueArr, wordsArr[i], uniqueCount) == -1){
            uniqueArr[uniqueCount] = malloc(strlen(wordsArr[i] + 1) * sizeof(char));
            strcpy(uniqueArr[uniqueCount], wordsArr[i]);
            uniqueCount++;
        }
    }

    return uniqueCount;
}

/*
This function returns the index of a given item in the given array, returns -1 if the item is not found.
   */
int indexOf(char ** arr, char * word, size_t size){
    for(int i = 0; i < size; i++){
        if(strcmp(arr[i], word) == 0){
            return i;
        }
    }

    return -1;
}

/*
This function will fill the uniqueWordsArr with the unique words from wordsArr
   */
void fillUniqueWords(char ** wordsArr, char ** uniqueWordsArr, size_t size){
    int uniqueCount = 0;

    for(int i = 0; i < size; i++){
        if(indexOf(uniqueWordsArr, wordsArr[i], uniqueCount) == -1){
            uniqueWordsArr[uniqueCount] = malloc(strlen(wordsArr[i] + 1) * sizeof(char));
            strcpy(uniqueWordsArr[uniqueCount], wordsArr[i]);
            uniqueCount++;
        }
    }
}
