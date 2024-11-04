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
int indexBuffer(char *, char ***, int);
int indexOf(char ***, char *, int);


int main(void){
    char * buffer = calloc(BUFFER_SIZE, sizeof(char));

    getBuffer(buffer);

    printf("Buffer = %s\n", buffer);
    
    char *** indexArr = malloc(8 * sizeof(char **));
    
    for(int i = 0; i < 8; i++){
        indexArr[i] = malloc(4 * sizeof(char *));
    }

    indexBuffer(buffer, indexArr, 8);
}

/*
This function will fill a given buffer array with characters until it is full or EOF is reached

Arguments:
    char * buffer: Character array to fill from stdin

Returns:
    char *: buffer array filled from stdin
*/
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
This function, when given a buffer array, index array, and in index array size, will find all words in the bufer and
add it to the index array. If the index array is full, it will allocate more size. The function will return the actual
size of the index array.
Arguments:
    char * buffer: filled character buffer from stdin
    char ** indexArr: initialized index array for buffer
    int indexArrSize: Index array starting size
Returns:
    int: Final size of index array
*/
int indexBuffer(char * buffer, char *** indexArr, int indexArrSize){
    int size = 0;
    char * word = "";

    for(int i = 0; i < BUFFER_SIZE; i++){
        if(isspace(buffer[i])){
            if(strlen(word) == 0){
                continue;
            }

            int index = indexOf(indexArr, word, size);
            if(index != -1){

            }

            //add element, check size
        }
    }

    return size;
}


int indexOf(char *** indexArr, char * word, int size){
    for(int i = 0; i < size; i++){
        if(strcmp(indexArr[i][3], word) == 0){
            return i;
        }
    }

    return -1;
}
