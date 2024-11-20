//TODO: block comment
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#define LINE_COUNT 'l'
#define CHARACTER_COUNT 'c'
#define WORD_COUNT 'w'
#define FREQUENCY 'f'
#define VERBOSE 'v'
#define HELP 'h'
#define DEBUG 'd'
#define AVERAGE_CHARACTER_COUNT 'a'
#define EXCLUDE_PUNCTUATION 'p'

#define DEFAULT_BUFFER_SIZE 40
#define DEFAULT_WORD_LIST_SIZE 5


int parseArgs(int, char **);
void printHelp();
void debugLog(char *, ...);
struct inputBuffer fillBuffer();
struct inputBuffer resize(struct inputBuffer);
void report(struct inputBuffer);
struct wordList fillWordList(struct inputBuffer);
int indexOf(struct wordList, char *);
struct wordList resizeWordList(struct wordList);
struct inputBuffer concatReport(struct inputBuffer, char *, ...);


struct inputBuffer {
    size_t size;
    size_t maxSize;
    char * buffer;
};

struct word {
    size_t length;
    size_t count;
    char * word;
};

struct wordList {
    size_t length;
    size_t maxLength;
    size_t wordCount;
    struct word * list;
};


bool lineCount = false;
bool characterCount = false;
bool wordCount = false;
bool frequency = false;
bool debug = false;
bool averageCharCount = false;
bool excludePunct = false;

char * delim = " \t\n\r";


int main(int argc, char ** argv){
    if(parseArgs(argc, argv)){
        return 0;
    }

    struct inputBuffer buf = fillBuffer();

    report(buf);
}


int parseArgs(int argc, char ** argv){
    if(argc == 1){
        lineCount = true;
        wordCount = true;
        characterCount = true;
    }

    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            char * argument = argv[i] + 1;
            size_t len = strlen(argument);

            for(int j = 0; j < len; j++){
                switch (argument[j]){
                    case LINE_COUNT:
                        lineCount = true;
                        break;
                    case CHARACTER_COUNT: 
                        characterCount = true;
                        break;
                    case WORD_COUNT: 
                        wordCount = true;
                        break;
                    case FREQUENCY:
                        frequency = true;
                        break;
                    case VERBOSE:
                        lineCount = true;
                        characterCount = true;
                        wordCount = true;
                        frequency = true;
                        break;
                    case HELP: 
                        printHelp();
                        return 1;
                        break;
                    case DEBUG:
                        debug = true;
                        break;
                    case AVERAGE_CHARACTER_COUNT: 
                        averageCharCount = true;
                        break;
                    case EXCLUDE_PUNCTUATION: 
                        excludePunct = true;
                        break;
                    default:
                        printf("Unknown option: %c\n", argument[j]);
                } 
            }
        }
    }

    if(lineCount) debugLog("Flag set: Line count");
    if (wordCount) debugLog("Flag set: Word count");
    if (characterCount) debugLog("Flag set: Character count");
    if (frequency) debugLog("Flag set: Word frequency");
    if (debug) debugLog("Flag set: Debug");
    if (averageCharCount) debugLog("Flag set: Average character count");
    if (excludePunct) debugLog("Flag set: Exclude punctuation");

    return 0;
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
}


void debugLog(char * msg, ...){
    va_list args;
    va_start(args, msg);

    if(debug){
        fprintf(stderr, "DEBUG    ");
        vfprintf(stderr, msg, args);
        fprintf(stderr, "\n");
    }
}


struct inputBuffer fillBuffer(){
    debugLog("Starting buffer fill");

    struct inputBuffer buf;
    buf.buffer = (char *) calloc(DEFAULT_BUFFER_SIZE, sizeof(char));
    buf.size = 0;
    buf.maxSize = DEFAULT_BUFFER_SIZE;

    if (!buf.buffer) {
        fprintf(stderr, "Memory allocation failed for buffer.\n");
        exit(EXIT_FAILURE);
    }

    while(!feof(stdin)){
        if(!fread(buf.buffer + buf.size, 1, sizeof(char), stdin)){
            break;
        }

        buf.size++;

        if(buf.size == buf.maxSize){
            buf = resize(buf);
        }
    }

    debugLog("Finished buffer fill, final size: %lu", buf.size);

    return buf;
}


struct inputBuffer resize(struct inputBuffer buf){
    debugLog("Resizing buffer from %lu to %lu", buf.maxSize, buf.maxSize + DEFAULT_BUFFER_SIZE);

    char * newBuffer = realloc(buf.buffer, buf.maxSize + DEFAULT_BUFFER_SIZE);

    if (!newBuffer) {
        fprintf(stderr, "Memory reallocation failed.\n");
        free(buf.buffer);
        exit(EXIT_FAILURE);
    }

    for(int i = buf.size; i < buf.maxSize + DEFAULT_BUFFER_SIZE; i++){
        newBuffer[i] = 0;
    }

    buf.buffer = newBuffer;
    buf.maxSize += DEFAULT_BUFFER_SIZE;

    return buf;
}


void report(struct inputBuffer buf) {
    struct inputBuffer report;
    report.maxSize = DEFAULT_BUFFER_SIZE;
    report.size = 0;
    report.buffer = calloc(DEFAULT_BUFFER_SIZE, sizeof(char));

    if(lineCount){
        debugLog("Generating line count report");

        int lines = 0;

        for(int i = 0; i < buf.size; i++){
            if(buf.buffer[i] == '\n'){
                lines++;
            }
        }

        char * format = "lines : %d\n";
        int length = snprintf(NULL, 0, format, lines) + 1;
        char * lineReport = malloc(length);
        sprintf(lineReport, format, lines);

        for(int i = 0; i < strlen(lineReport); i++){
            report.buffer[report.size] = lineReport[i];

            report.size++;

            if(report.size == report.maxSize){
                report = resize(report);
            }
        }

        free(lineReport);
    } 

    struct wordList list = fillWordList(buf);

    if(wordCount){ // todo: add total word count to wordList
        debugLog("Generating word count report");

        char * format = "word count : %lu\n";
        int length = snprintf(NULL, 0, format, list.wordCount) + 1;
        char * wordCountReport = malloc(length);
        sprintf(wordCountReport, format, list.wordCount);

        for(int i = 0; i < strlen(wordCountReport); i++){
            report.buffer[report.size] = wordCountReport[i];

            report.size++;

            if(report.size == report.maxSize){
                report = resize(report);
            }
        }

        free(wordCountReport);
    }

    if(characterCount){
        debugLog("Generating character count report");

        char * format = "character count : %lu\n";
        int length = snprintf(NULL, 0, format, buf.size) + 1;
        char * charCountReport = malloc(length);
        sprintf(charCountReport, format, buf.size);

        for(int i = 0; i < strlen(charCountReport); i++){
            report.buffer[report.size] = charCountReport[i];

            report.size++;

            if(report.size == report.maxSize){
                report = resize(report);
            }
        }

        free(charCountReport);
    }

    if(frequency){
        debugLog("Generating word frequency count");
        report = concatReport(report, "word frequency : \n");
        for(int i = 0; i < list.length; i++){
            report = concatReport(report, "\t%s : %lu\n", list.list[i].word, list.list[i].count);
        }
    }

    if(averageCharCount){
        debugLog("Buffer: %s", buf.buffer);
    }

    free(buf.buffer);
    free(list.list);

    printf("%s", report.buffer);

    free(report.buffer);
}


struct inputBuffer concatReport(struct inputBuffer report, char * fmt, ...){
    va_list args;
    va_start(args, fmt);

    va_list argsCopy;
    va_copy(argsCopy, args);
    int length = vsnprintf(NULL, 0, fmt, argsCopy) + 1;
    char * newStr = malloc(length);
    va_copy(argsCopy, args);
    vsprintf(newStr, fmt, args);

    for(int i = 0; i < strlen(newStr); i++){
        report.buffer[report.size] = newStr[i];

        report.size++;

        if(report.size == report.maxSize){
            report = resize(report);
        }
    }

    return report;
}


struct wordList fillWordList(struct inputBuffer buf){
    debugLog("Starting word list fill");

    struct wordList list;
    list.length = 0;
    list.maxLength = DEFAULT_WORD_LIST_SIZE;
    list.wordCount = 0;
    list.list = (struct word *) calloc(DEFAULT_WORD_LIST_SIZE, sizeof(struct word));

    if (!list.list) {
        fprintf(stderr, "Memory allocation failed for word list.\n");
        exit(EXIT_FAILURE);
    }

    char * token = strtok(buf.buffer, delim);

    while(token != NULL) {
        int index = indexOf(list, token);

        if(index != -1){
            list.list[index].count++;
        }
        else {
            struct word newWord;
            newWord.count = 1;
            newWord.length = strlen(token);
            newWord.word = token;

            if (!newWord.word) {
                fprintf(stderr, "Memory allocation failed for word.\n");
                free(list.list);
                exit(EXIT_FAILURE);
            }

            list.list[list.length] = newWord;
            list.length++;

            if(list.length == list.maxLength){
                list = resizeWordList(list);
            }
        }

        list.wordCount++;

        token = strtok(NULL, delim);
    }

    debugLog("Finished word list fill, final size: %lu", list.length);

    return list;
} 


int indexOf(struct wordList list, char * str){
    int index = -1;

    for(int i = 0; i < list.length; i++){
        if(strcmp(list.list[i].word, str) == 0){
            index = i;
            break;
        }
    }

    return index;
}


struct wordList resizeWordList(struct wordList list){
    debugLog("Resizing wordList from size %lu to %lu", list.length, list.length + DEFAULT_WORD_LIST_SIZE);

    struct word * newList = realloc(list.list, (list.length + DEFAULT_WORD_LIST_SIZE) * sizeof(struct word));

    list.list = newList;
    list.maxLength += DEFAULT_WORD_LIST_SIZE;

    return list;
}
