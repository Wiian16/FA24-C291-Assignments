#include <stdbool.h>
#include <stdio.h>

#define MONTHS_PER_YEAR 12
#define WEEKS_PER_MONTH 4
#define HOURS_PER_WEEK 40

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


void printUsage(void){
    printf("%s", usage);
}


/*
 * Author -- Ian McGillivary
 * Program -- University Payroll Calculator
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
    //admin values
    double admin_total_salary = 0, admin_total_pay = 0, admin_count = 0;
    //staff values
    double staff_total_salary = 0, staff_total_pay = 0, staff_count = 0;
    //adjunct values
    double adjunct_total_salary = 0, adjunct_total_pay = 0, adjunct_count = 0;
    //regular values
    double regular_total_salary = 0, regular_total_pay = 0, regular_count = 0;
    //ta values
    double ta_total_salary = 0, ta_total_pay = 0, ta_count = 0;
    //hourly values
    double hourly_total_salary = 0, hourly_total_pay = 0, hourly_count = 0;

    while(true){
        char type = 0;

        printf("Enter employee salary: ");
        scanf(" %c", &type);
        
        if(type == 'q' || type == 'Q'){
            break;
        }

        if(type == '?'){
            printUsage();
            continue;
        }

        double param1 = 0, param2 = 0;

        switch(type){
            case 'A': { //Administrator
                          scanf("%lf", &param1);

                          double salary = param1 / MONTHS_PER_YEAR;

                          admin_total_salary += salary;
                          admin_total_pay += salary;
                          admin_count++;

                          break;
                      }
            case 'S': { //Staff
                          scanf("%lf %lf", &param1, &param2);

                          if(param2 > 10){
                              printf("Warning: Staff member over allowed overtime hours, extra time discarded\n");
                              param2 = 10;
                          }

                          const float OVERTIME_RATE = 1.5;

                          double salary = param1 / MONTHS_PER_YEAR;
                          double hourlyRate = salary / WEEKS_PER_MONTH / HOURS_PER_WEEK;
                          double overtimeHourly = hourlyRate * OVERTIME_RATE;

                          double pay = salary;
                          double overtimePay = overtimeHourly * param2;

                          pay += overtimePay;

                          staff_total_salary += salary;
                          staff_total_pay += pay;
                          staff_count++;

                          break;
                      }
            case 'H': { //Hourly
                          scanf("%lf %lf", &param1, &param2);

                          if(param2 > 20 * WEEKS_PER_MONTH + 20){
                              printf("Warning: Hourly employee over allowed overtime hours, extra time discarded\n");
                              param2 = 20 * WEEKS_PER_MONTH + 20;
                          }

                          const int HOURS_PER_MONTH = 80;
                          const float OVERTIME_RATE = 1.25;

                          int hours = 0, overtimeHours = 0;

                          if(param2 > HOURS_PER_MONTH){
                              hours = HOURS_PER_MONTH;
                              overtimeHours = param2 - hours;
                          }
                          else{
                              hours = param2;
                          }

                          double salary = hours * param1;
                          double overtimePay = overtimeHours * param1 * OVERTIME_RATE;
                          double pay = salary + overtimePay;

                          hourly_total_salary += salary;
                          hourly_total_pay += pay;
                          hourly_count++;

                          break;
                      }
            case 'J': { //Adjunct
                          scanf("%lf", &param1);

                          if(param1 > 9){
                              printf("Warning: Adjunct instructor over allowed credit hours, extra credits discarded\n");
                              param1 = 9;
                          }

                          const float ADJUNCT_RATE = 8500.0 / 3;
                          const int MONTHS = 5;

                          int hours = (int) param1;

                          float salary = hours * ADJUNCT_RATE / MONTHS;

                          adjunct_total_salary += salary;
                          adjunct_total_pay += salary;
                          adjunct_count++;

                          break;
                      }
            case 'R': { //Regular Faculty
                          scanf(" %lf %lf", &param1, &param2);
                          const int MONTHS = 10;
                          const int OVERLOAD_MONTHS = 5;
                          const float OVERLOAD_RATE = 8500.0 / 3;

                          float salary = param1 / MONTHS;
                          float overloadPay = param2 * OVERLOAD_RATE / OVERLOAD_MONTHS;
                          float pay = salary + overloadPay;
                          
                          regular_total_salary += salary;
                          regular_total_pay += pay;
                          regular_count++;

                          break;
                      }
            case 'T': { //TA
                          scanf("%lf %lf", &param1, &param2);
                          
                          const float COURSE_RATE = 2500.0;
                          const int TA_HOURS_PER_WEEK = 10;
                          const int EXPECTED_HOURS = WEEKS_PER_MONTH * TA_HOURS_PER_WEEK * param1;
                          const int MAX_HOURS = EXPECTED_HOURS + 2 * WEEKS_PER_MONTH;
                          const float HOURLY_RATE = COURSE_RATE / 5 / EXPECTED_HOURS * param1;

                          if(param2 > MAX_HOURS){
                              printf("Warning: TA over maximum overtime hours, extra time discarded.\n");
                              param2 = MAX_HOURS;
                          }

                          float hours = 0, overtimeHours = 0;

                          if(param2 > EXPECTED_HOURS){
                              hours = EXPECTED_HOURS;
                              overtimeHours = param2 - EXPECTED_HOURS;
                          }
                          else{
                              hours = param2;
                          }
                          
                          float salary = HOURLY_RATE * hours;
                          float overtimePay = overtimeHours * HOURLY_RATE;
                          float pay = salary + overtimePay;

                          ta_total_salary += salary;
                          ta_total_pay += pay;
                          ta_count++;

                          break;
                      }
            default:
                printf("Invalid input, enter '?' to see usage\n");
                continue;
        }
    }

    //Admin
    double admin_avg_salary = (admin_count == 0) ? 0 : admin_total_salary / admin_count;
    double admin_avg_pay = (admin_count == 0) ? 0 : admin_total_pay / admin_count;
    //Staff
    double staff_avg_salary = (staff_count == 0) ? 0 : staff_total_salary / staff_count;
    double staff_avg_pay = (staff_count == 0) ? 0 : staff_total_pay / staff_count;
    //Adjunct
    double adjunct_avg_salary = (adjunct_count == 0) ? 0 : adjunct_total_salary / adjunct_count;
    double adjunct_avg_pay = (adjunct_count == 0) ? 0 : adjunct_total_pay / adjunct_count;
    //Regular
    double regular_avg_salary = (regular_count == 0) ? 0 : regular_total_salary / regular_count;
    double regular_avg_pay = (regular_count == 0) ? 0 : regular_total_pay / regular_count;
    //Hourly
    double hourly_avg_salary = (hourly_count == 0) ? 0 : hourly_total_salary / hourly_count;
    double hourly_avg_pay = (hourly_count == 0) ? 0 : hourly_total_pay / hourly_count;
    //TA
    double ta_avg_salary = (ta_count == 0) ? 0 : ta_total_salary / ta_count;
    double ta_avg_pay = (ta_count == 0) ? 0 : ta_total_pay / ta_count;

    printf("EMPLOYEE_TYPE     AVG_SALARY       AVG_PAY\n");
    printf("%-18s%-17.2f%-.2f\n", "Administrator", admin_avg_salary, admin_avg_pay);
    printf("%-18s%-17.2f%-.2f\n", "Staff", staff_avg_salary, staff_avg_pay);
    printf("%-18s%-17.2f%-.2f\n", "Faculty", regular_avg_salary, regular_avg_pay);
    printf("%-18s%-17.2f%-.2f\n", "Adjunct", adjunct_avg_salary, adjunct_avg_pay);
    printf("%-18s%-17.2f%-.2f\n", "TA", ta_avg_salary, ta_avg_pay);
    printf("%-18s%-17.2f%-.2f\n", "Hourly", hourly_avg_salary, hourly_avg_pay);
}
