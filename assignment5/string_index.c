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
char *** indexBuffer(char *, char ***, int);
int indexOf(char ***, char *, int);


int main(void){
    char * buffer = calloc(BUFFER_SIZE, sizeof(char));

    getBuffer(buffer);

    printf("Buffer = %s\n", buffer);
    
    char *** indexArr = malloc(8 * sizeof(char **));
    for(int i = 0; i < 8; i++){
        indexArr[i] = malloc(4 * sizeof(char *));
    }
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
    while (!feof(stdin) && i <= BUFFER_SIZE){
        if(!fread(buffer + i, sizeof(char), 1, stdin)){
            break;
        }

        i++;
    }

    printf("\nDone filling\n");
    printf("Buffer Length = %d\n", i);
} 

/*
This function, when given a buffer array, index array, and an index size will parse the buffer for words seperated by
whitespace. Unique words found will be stored in the index array along with their being index, length, and count. The 
new array will be returned, as it may be at a different address. 
Arguments:
    char * buffer: filled buffer to index
    char *** indexArr: Initialized index of buffer
    int indexSize: starting size of indexArr
*/
char *** indexBuffer(char * buffer, char *** indexArr, int indexSize){
    int filledSize = 0;
    char * word = malloc(2048 * sizeof(char));
    word[0] = '\0';

    for(int i = 0; i < BUFFER_SIZE; i++){
        if(isspace(buffer[i])){
            if(strlen(word) == 0){
                continue;
            }

            int index = indexOf(indexArr, word, filledSize);
            if(index != -1){
                //word already found, update count
                int count = atoi(indexArr[i][2]) + 1;
                sprintf(indexArr[i][2], "%d", count);
            }
            else{

            }
        }
    }

    return indexArr;
}

/*
When given an array of strings, a string to search for, and a size, this function will return the index of the given
string if it is in the array and -1 if the string is not found.
*/
int indexOf(char *** wordsArr, char * word, int size){
    for(int i = 0; i < size; i++){
        if(strcmp(wordsArr[i][3], word) == 0){
            return i;
        }
    }

    return -1;
}

