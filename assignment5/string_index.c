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


void getBuffer(char *);


int main(void){
    char * buffer = calloc(2048, sizeof(char));

    getBuffer(buffer);

    printf("Buffer = %s\n", buffer);
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

    int maxLength = *(&buffer + 1) - buffer;

    int i = 0;
    while (!feof(stdin)){
        if(i == maxLength){
            break;
        }

        fread(buffer + index, sizeof(char), 1);
    }

    printf("Done filling\n");
} 
