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
\tq -- print output and quit\n\
\t? -- print this help message\n\
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
int getType(char typeChar){
    if (typeChar == 'A'){
        return ADMIN;
    }
    else if (typeChar == 'S'){
        return STAFF;
    }
    else if (typeChar == 'J'){
        return ADJUNCT;
    }
    else if (typeChar == 'R'){
        return REGULAR;
    }
    else if (typeChar == 'T'){
        return TA;
    }
    else if (typeChar == 'H'){
        return HOURLY;
    }
    else{
        return -1;
    }
}

/*
 * This method takes in two strings (char arrays), appends them together, and returns the new array
 */ 
char * append(char * a, char * b){
    int len = strlen(a) + strlen(b) + 1;

    char * str = (char *) malloc(len);

    strcpy(str, a);
    strcat(str, b);

    return str;
}

/*
 * This function outputs a formatted string of the admin average salary when given the yearly salary
 */
char * calculateAdmin(float salary){ 
    char * str = (char *) malloc(60);
    sprintf(str, "%-18s%-17.2f%-.2f\n", "Administrator", salary / MONTHS_PER_YEAR, salary / MONTHS_PER_YEAR);
    return str;
}

/*
 * This function outputs a formatted string of the staff average salary and pay when given yearly salary and
 * overtime hours
 */
char * calculateStaff(float salary, float overtimeHours){
    char * str = (char *) malloc(60);

    float avgSalary = salary / MONTHS_PER_YEAR;
    float hourly = avgSalary / WEEKS_PER_MONTH / HOURS_PER_WEEK;
    float overtimeHourly = hourly * 1.5;

    sprintf(str, "%-18s%-17.2f%-.2f\n", "Staff", avgSalary, avgSalary + overtimeHourly * overtimeHours);
    return str;
}

/*
 * This function outputs a formatted string of the hourly average salary and pay when given an hourly pay rate
 * and hours worked. Hourly workers are paid at their base rate for the first 20 hours, then 1.25 times their 
 * rate for the next 20.
 */
char * calculateHourly(float payRate, float hoursWorked){
    const int HOURS_PER_MONTH = HOURS_PER_WEEK / 2 * WEEKS_PER_MONTH; //20 hours per week for one month
    const float OVERTIME_RATE = 1.25;

    float regularHours, overtimeHours;

    if(hoursWorked > HOURS_PER_MONTH){
        regularHours = HOURS_PER_MONTH;
        hoursWorked -= HOURS_PER_MONTH;
    }
    else{
        regularHours = hoursWorked;
        hoursWorked = 0;
    }

    if(hoursWorked > HOURS_PER_MONTH){
        overtimeHours = HOURS_PER_MONTH;
    }
    else{
        overtimeHours = hoursWorked;
    }

    char * str = (char *) malloc(60);
    
    float avgSalary = payRate * HOURS_PER_MONTH; 
    sprintf(str, "%-18s%-17.2f%-.2f\n", "Hourly", avgSalary, avgSalary + payRate * OVERTIME_RATE * overtimeHours);
    return str;
}

/*
 * This function outputs a formatted string of the adjunct average salary and pay when given their credit houts taught.
 */
char * calculateAdjunct(float creditHours){
    const float ADJUNCT_RATE = 8500.0 / 3;
    const int ADJUNCT_MONTHS = 5;

    int hours = (int) creditHours;

    float avg_salary = hours * ADJUNCT_RATE / ADJUNCT_MONTHS;

    char * str = (char *) malloc(60);
    sprintf(str, "%-18s%-17.2f%-.2f\n", "Adjunct", (float) avg_salary, avg_salary);
    return str;
}

/*
 * This function outputs a formatted string of regular faculty average salary and pay when given their annual salary
 * and credit hour overload
 */
char * calculateRegular(float annualSalary, float creditOverload){
    const float OVERLOAD_RATE = 8500.0 / 3;
    const int OVERLOAD_MONTHS = 5;
    const int SALARY_MONTHS = 10;

    float avgSalary = annualSalary / SALARY_MONTHS;
    float avgOverloadPay = creditOverload * OVERLOAD_RATE / OVERLOAD_MONTHS;

    char * str = (char *) malloc(60);
    sprintf(str, "%-18s%-17.2f%-.2f\n", "Faculty", avgSalary, avgSalary + avgOverloadPay);
    return str;
}


char * calculateTA(float courses, float hours){ //todo
    const int REGULAR_HOURS = 10;
    const int OVERTIME_HOURS = 2;
    const int MONTHS = 5;
    const float MONTHLY_RATE = 2500.0 / MONTHS;
    const float HOURLY_RATE = MONTHLY_RATE / WEEKS_PER_MONTH / 10;
    
    int maxHours = REGULAR_HOURS * WEEKS_PER_MONTH * courses + OVERTIME_HOURS * WEEKS_PER_MONTH * courses;
    
    if(hours > maxHours){
        hours = maxHours;
    }

    float pay = hours * HOURLY_RATE;

    char * str = (char *) malloc(60);
    sprintf(str, "%-18s%-17.2f%-.2f\n", "TA", pay, pay);
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
    char * output = "EMPLOYEE_TYPE     AVG_SALARY       AVG_PAY\n";

    while(true){
        char type;

        printf("Enter employee salary:\n");
        scanf(" %c ", &type);
        printf("type=%c\n", type);
        //break loop and print output
        if(type == 'q' || type == 'Q'){
            break;
        }
        //print instructions and continue
        if(type == '?'){
            printUsage();
            continue;
        }

        int typeCode = getType(type);

        double param1 = 0;
        double param2 = 0;
        int params = 0;

        switch(typeCode){
            case ADMIN: 
                params = scanf(" %lf ", &param1);
                printf("param1=%f\n", param1);
    
                if(params != 1){
                    printf("Invalid input, enter '?' to see usage\n");
                    continue;
                }

                output = append(output, calculateAdmin(param1));

                break;
            case STAFF:
                params = scanf(" %lf %lf ", &param1, &param2);

                if(params != 2){
                    printf("Invalid input, enter '?' to see usage\n");
                    continue;
                }

                if(param2 > 10){
                    printf("Warning: staff member above allowed overtime hours, data discarded\n");
                    continue;
                }

                output = append(output, calculateStaff(param1, param2));

                break;
            case HOURLY:
                params = scanf(" %lf %lf", &param1, &param2);

                if(params != 2){
                    printf("Invalid input, enter '?' to see usage\n");
                    continue;
                }

                if(param2 > 20){
                    printf("Warning: hourly employee over allowed time, data discarded\n");
                    continue;
                }

                output = append(output, calculateHourly(param1, param2));

                break;
            case ADJUNCT:
                params = scanf(" %lf ", &param1);

                if(params != 1){
                    printf("Invalid input, enter '?' to see usage\n");
                    continue;
                }

                if(param1 > 9){
                    printf("Warning: adjuncty faculty member over allowed credit hours, data discarded\n");
                    continue;
                }

                output = append(output, calculateAdjunct(param1));

                break;
            case REGULAR:
                params = scanf(" %lf %lf ", &param1, &param2);

                if(params != 2){
                    printf("Invalid input, enter '?' to see usage\n");
                    continue;
                }

                output = append(output, calculateRegular(param1, param2));                

                break;
            case TA:
                params = scanf(" %lf %lf ", &param1, &param2);

                if(params != 2){
                    printf("Invalid input, enter '?' to see usage\n");
                    continue;
                }

                int maxHours = param1 * 12 * WEEKS_PER_MONTH * 5;

                if(param2 > maxHours){
                    printf("Warning: teaching assistant over allowed hours, data discarded\n");
                    continue;
                }

                output = append(output, calculateTA(param1, param2));

                break;
            default:
                printf("Invalid input, enter '?' to see usage\n");
        }
    }

    printf("%s\n", output);
}
