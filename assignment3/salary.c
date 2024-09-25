#include <regex.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MONTHS_PER_YEAR 12
#define WEEKS_PER_MONTH 4
#define HOURS_PER_WEEK 40

#define ADMIN 0
#define STAFF 1 
#define HOURLY 2
#define ADJUNCT 3
#define REGULAR 4
#define TA 5

const char usage[] = "Usage information: \n\
Valid commands:\n\
\t'q' -- print output and quit\n\
Input must begin with a valid employee character code, followed by one or two decimal numbers\n\
Valid employee types:\n\
\tA -- Administrator: Salary paid in equal portions each month\n\
\t\tInput: Requires only yearly salary\n\
\tS -- Staff: Salary paid monthly with optional overtime\n\
\t\tInput: Requires yearly salary and overtime hours worked in the month\n\
\tH -- Hourly: Paid by the hour with potential overtime\n\
\t\tInput: Requires hourly pay rate and total hours worked in the month\n\
\tJ -- Adjunct Faculty: Paid per 3 credit hours taught over a 5-month period\n\
\t\tInput: Requires number of credit hours being taught\n\
\tR -- Regular Faculty: Paid yearly salary with potential overload credit pay\n\
\t\tInput: Requires yearly salary and number of overload credit hours this semester\n\
\tT -- Teaching Assistant: Paid per course with regular and overtime hours\n\
\t\tInput: Requires number of courses assisted and total hours worked in the month\n";


regex_t regex;

/*
 * This function takes an input string and returns true if the string contains a valid
 * employee type as the first character and one or two decimal numbers, false otherwise
 */
bool validate(char input[]){
    return regexec(&regex, input, 0, NULL, 0) == 0;
}

/*
 * This function returns true if strigns a and b are equal, false otehrwise
 */
bool equals(char a[], char b[]){
    return strcmp(a, b) == 0;
}

/*
 * This function prints usage instructions to stdout
 */
void printUsage(void){
    printf("%s", usage);
}

/*
 * This method takes in the user input after validation, and returns the type of employee based on the
 * character provided. If the character is invalid, -1 is returned. 
 */
int getType(char input[]){
    if (input[0] == 'A'){
        return ADMIN;
    }
    else if (input[0] == 'S'){
        return STAFF;
    }
    else if (input[0] == 'J'){
        return ADJUNCT;
    }
    else if (input[0] == 'R'){
        return REGULAR;
    }
    else if (input[0] == 'T'){
        return TA;
    }
    else{
        return -1;
    }
}

/*
 * This function outputs a formatted string of the admin average salary when given the yearly salary
 */
char * calcualteAdmin(float salary){ //todo: calculate avg salary
    char * str;
    sprintf(str, "%-18s%-17.2f", "Administrator", salary);
    return str;
}

/*
 * This method takes in two strings (char arrays), appends them together, and returns the new array
 */ 
char * append(char * a, char * b){
    int len = strlen(a) + strlen(b);
    char * str = (char * ) malloc(len);
    strcat(str, a);
    strcat(str, b);

    return str;
}

/*
 * This function runs on program start, it first initializes a regular expression for validation of user input.
 * Second, the program will enter a loop until the user quits the program. During this loop, it will wait for user
 * input, if this input is 'q', the loop will exit, if the input is '?', it will print instructions, and otherwise,
 * it will validate the input. If the input is invalid, a warning will be printed, the data will be discarded, 
 * and the loop will continue. If the data is valid, the function enters a switch for the employee type provided.
 * If the input for that employee type is incorrect, a warning will be printed, otherwise, the salary data will be
 * added to the output. When the loop is exited, the output will be printed with all employee types and salary
 * data.
 */
int main(void){
    printf("program started\n");

    //Initialize regular expression and error out if failed
    if(regcomp(&regex, "^[ASRJTH] ([0-9]+[\\.0-9]* ?){1,2}$", REG_EXTENDED) != 0){
        printf("regular expression compilation failed");
        return 1;
    }

    char * output = "EMPLOYEE_TYPE     AVG_SALARY       AVG_PAY\n";

    while(true){
        char input[5];
        printf("Enter employee salary: ");
        scanf(" %[^\n]", input);
        //break loop and print output
        if(equals(input, "q")){
            break;
        }
        //print instructions and continue
        if(equals(input, "?")){
            printUsage();
            memset(input, 0, sizeof(input)); // Clear the input
            continue;
        }
        //ensure input follows correct format, continue loop if it doesn't
        if(!validate(input)){
            printf("Invalid input\n");
            printUsage();
            memset(input, 0, sizeof(input));
            continue;
        }

        int type = getType(input);

        switch(type){
            case ADMIN: //todo: extract values from input string
                output = append(output, calcualteAdmin(1000));
                break;
            case STAFF:
                printf("Not implemented yet\n"); //todo
                break;
            case HOURLY:
                printf("Not implemented yet\n"); //todo
                break;
            case ADJUNCT:
                printf("Not implemented yet\n"); //todo
                break;
            case REGULAR:
                printf("Not implemented yet\n"); //todo
                break;
            case TA:
                printf("Not implemented yet\n"); //todo
                break;
            default:
                printUsage();
        }

        memset(input, 0, sizeof(input));
    }

    printf("%s\n", output);

    printf("program finished\n");
}
