//TODO: block comment
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LINE_COUNT 'l'
#define CHARACTER_COUNT 'c'
#define WORD_COUNT 'w'
#define FREQUENCY 'f'
#define VERBOSE 'v'
#define HELP 'h'
#define DEBUG 'd'
#define AVERAGE_CHARACTER_COUNT 'a'
#define EXCLUDE_PUNCTUATION 'p'


void parseArgs(int, char **);
void printHelp();


bool lineCount = false;
bool characterCount = false;
bool wordCount = false;
bool frequency = false;
bool debug = false;
bool averageCharCount = false;
bool excludePunct = false;


int main(int argc, char ** argv){
    parseArgs(argc, argv);

    printf("lineCount: %d\n", lineCount);
    printf("characterCount: %d\n", characterCount);
    printf("wordCount: %d\n", wordCount);
    printf("frequency: %d\n", frequency);
    printf("debug: %d\n", debug);
    printf("averageCharCount: %d\n", averageCharCount);
    printf("excludePunct: %d\n", excludePunct);
}


void parseArgs(int argc, char ** argv){
    if(argc == 1){
        lineCount = true;
        wordCount = true;
        characterCount = true;
        return;
    }

    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            char * argument = argv[i] + 1;
            size_t len = strlen(argument);

            for(int j = 0; j < len; j++){
                switch (argument[j]){
                    case LINE_COUNT:
                        printf("Line Count\n");
                        lineCount = true;
                        break;
                    case CHARACTER_COUNT: 
                        printf("Character Count\n");
                        characterCount = true;
                        break;
                    case WORD_COUNT: 
                        printf("Word Count\n");
                        wordCount = true;
                        break;
                    case FREQUENCY:
                        printf("Word Frequency\n");
                        frequency = true;
                        break;
                    case VERBOSE:
                        printf("Verbose\n");
                        lineCount = true;
                        characterCount = true;
                        wordCount = true;
                        frequency = true;
                        break;
                    case HELP: 
                        printf("Help\n");
                        printHelp();
                        break;
                    case DEBUG:
                        printf("Debug\n");
                        debug = true;
                        break;
                    case AVERAGE_CHARACTER_COUNT: 
                        printf("Average Character Count\n");
                        averageCharCount = true;
                        break;
                    case EXCLUDE_PUNCTUATION: 
                        printf("Exclude Punctuation\n");
                        excludePunct = true;
                        break;
                    default:
                        printf("Unknown option: %c\n", argument[j]);
                } 
            }
        }
    }
}


void printHelp(){
    printf("Usage: my_wc [-h] [-l] [-c] [-w] [-f] [-d] [-v] [-a] [-p]\n");
    printf("\n");
    printf("Options:\n");
    printf("  -h    Display this help message and exit.\n");
    printf("  -d    Enable debugging output to stderr, showing internal operations.\n");
    printf("  -l    Report the number of lines in the input.\n");
    printf("  -c    Report the total number of characters in the input.\n");
    printf("  -w    Report the total number of words in the input (default with no options).\n");
    printf("  -f    Report the frequency of each unique word in the input.\n");
    printf("  -v    Output all counts: line count, word count, character count, and word frequency.\n");
    printf("  -a    Report average word length and average line length.\n");
    printf("  -p    Exclude punctuation from words, but include punctuation in character count.\n");
    printf("\n");
    printf("If no options are provided, the program will report the line count, word count,\n");
    printf("and character count in that order.\n");
    printf("\n");
    printf("Example usage:\n");
    printf("  my_wc -l < sample.txt     # Report line count from stdin\n");
    printf("  my_wc -v < sample.txt     # Report line, word, character count, and word frequency\n");
    printf("  my_wc -f -d < sample.txt  # Report word frequency with debugging output\n");
    exit(0);
}
