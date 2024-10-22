/*
Author: Ian McGillivary
Program name: Bloomington Skating Company

This program calculates and formats a monthly report for the Bloomington Skating Company and it's
five employees. Output will include, monthly sales, monthly profit, commission, bonus, federal
tax withholding, staate tax withholding, social security contributions, net pay, and net profit.
The user will input data for each employee with a pair of numbers representing sales and tenure, 
respectively. If the user inputs "0 0" or equivalent before all five employees are entered, all
unentered employees will be filled with 0 sales and 0 tenure. The program will output the formatted
report when either all five employees have been entered, or when an early exit has been input.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_EMPLOYEES 5
#define FED_W 0.15
#define STATE_W 0.05
#define FICA 0.075
#define COMPANY_PROFIT_MARGIN 0.45
#define EMPLOYEE_COMISSION_RATE 0.125
#define BONUS_RATE 0.1
#define TENURE_BONUS_RATE 0.05


double round_to_2(double);
char * validateMonth(int);
void parseInput(double *, double *);
double calculateTotalSales(double *);
double calculateTotalProfit(double);
void calculateCommission(double *, double *);
void calculateBonus(double, double *, double *);
double calculateNetProfit(double, double);
void calculateFedW(double *, double *, double *);
void calculateStateW(double *, double *, double *);
double total(double *);
void calculateFICAW(double *, double *, double *);
void calculateNetPay(double *, double *, double *, double *, double *, double *);


int main(void){
    int month, year;
    char * monthStr;

    printf("Enter the payroll month and year(format mm/yyyy): ");
    scanf("%d/%d", &month, &year);

    monthStr = validateMonth(month);

    double * salesArr = malloc(NUM_EMPLOYEES * sizeof(double));
    double * tenureArr = malloc(NUM_EMPLOYEES * sizeof(double));

    for(int i = 0; i < NUM_EMPLOYEES; i++){
        salesArr[i] = 0;
        tenureArr[i] = 0;
    }

    parseInput(salesArr, tenureArr);

    double totalSales = calculateTotalSales(salesArr);
    double totalProfit = calculateTotalProfit(totalSales);

    double * commissionArr = malloc(NUM_EMPLOYEES * sizeof(double));
    double * bonusArr = malloc(NUM_EMPLOYEES * sizeof(double));
    double * fedWArr = malloc(NUM_EMPLOYEES * sizeof(double));
    double * stateWArr = malloc(NUM_EMPLOYEES * sizeof(double));
    double * FICAArr = malloc(NUM_EMPLOYEES * sizeof(double));
    double * netPayArr = malloc(NUM_EMPLOYEES * sizeof(double));

    calculateCommission(salesArr, commissionArr);
    double totalCommission = total(commissionArr);
    calculateBonus(totalProfit, tenureArr, bonusArr);
    double totalBonus = total(bonusArr);
    calculateFedW(commissionArr, bonusArr, fedWArr);
    double totalFedW = total(fedWArr);
    calculateStateW(commissionArr, bonusArr, stateWArr);
    double totalStateW = total(stateWArr);
    calculateFICAW(commissionArr, bonusArr, FICAArr);
    double totalFICA = total(FICAArr);
    calculateNetPay(commissionArr, bonusArr, fedWArr, stateWArr, FICAArr, netPayArr);
    double totalNetPay = total(netPayArr);
    
    double netProfit = calculateNetProfit(totalProfit, totalBonus);


    //Formatted output
    printf("\nMONTHLY STATEMENT (%s %d)\n", monthStr, year);
    printf("                                                    Bloomington Skating Company\n");
    printf("                                                                Bloomington, IN\n");
    printf("                                                          Phone: (812)-855-0000\n");
    printf("MONTHLY SALES: $%.2lf\n", round_to_2(totalSales));
    printf("MONTHLY PROFIT: $%.2lf\n", round_to_2(totalProfit));
    printf("===============================================================================\n");
    printf("Name       Commission   Bonus       Fed W.       ST W.       FICA      Net Pay\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("Empl A:    %-13.2lf%-12.2lf%-13.2lf%-12.2lf%-10.2lf%-.2lf\n", round_to_2(commissionArr[0]), round_to_2(bonusArr[0]), 
            round_to_2(fedWArr[0]), round_to_2(stateWArr[0]), round_to_2(FICAArr[0]), round_to_2(netPayArr[0]));
    printf("Empl B:    %-13.2lf%-12.2lf%-13.2lf%-12.2lf%-10.2lf%-.2lf\n", round_to_2(commissionArr[1]), round_to_2(bonusArr[1]), 
            round_to_2(fedWArr[1]), round_to_2(stateWArr[1]), round_to_2(FICAArr[1]), round_to_2(netPayArr[1]));
    printf("Empl C:    %-13.2lf%-12.2lf%-13.2lf%-12.2lf%-10.2lf%-.2lf\n", round_to_2(commissionArr[2]), round_to_2(bonusArr[2]), 
            round_to_2(fedWArr[2]), round_to_2(stateWArr[2]), round_to_2(FICAArr[2]), round_to_2(netPayArr[2]));
    printf("Empl D:    %-13.2lf%-12.2lf%-13.2lf%-12.2lf%-10.2lf%-.2lf\n", round_to_2(commissionArr[3]), round_to_2(bonusArr[3]), 
            round_to_2(fedWArr[3]), round_to_2(stateWArr[3]), round_to_2(FICAArr[3]), round_to_2(netPayArr[3]));
    printf("Empl E:    %-13.2lf%-12.2lf%-13.2lf%-12.2lf%-10.2lf%-.2lf\n", round_to_2(commissionArr[4]), round_to_2(bonusArr[4]), 
            round_to_2(fedWArr[4]), round_to_2(stateWArr[4]), round_to_2(FICAArr[4]), round_to_2(netPayArr[4]));
    printf("-------------------------------------------------------------------------------\n");
    printf("Total      %-13.2lf%-12.2lf%-13.2lf%-12.2lf%-10.2lf%-.2lf\n", round_to_2(totalCommission), round_to_2(totalBonus), 
            round_to_2(totalFedW), round_to_2(totalStateW), round_to_2(totalFICA), round_to_2(totalNetPay));
    printf("-------------------------------------------------------------------------------\n");
    printf("Net Profit (Profit - Bonus): %.2lf\n", round_to_2(netProfit));
    printf("John Doe, Branch Manager\n");
}

/*
   This function rounds a given number to two decimal places rounding half up
    Arguments:
        double x: number to round

    Returns:
        double: given number rounded half up to two decimal places
   */
double round_to_2(double x){
    return round(x * 100.0) / 100.0;
}

/*
   This function validates that the given month is valid and returns a string of the month's name
   in all caps
   Arguments:
        int month: month number to validate

   Returns: 
        char *: string of month name
   */
char * validateMonth(int month){
    if(month > 12 || month < 1){
        printf("month %d is invalid, must be 1-12\n", month);
        exit(1);
    }

    char * monthStr = malloc(9);

    switch(month){
        case 1:
            monthStr = "JANUARY";
            break;
        case 2:
            monthStr = "FEBRUARY";
            break;
        case 3:
            monthStr = "MARCH";
            break;
        case 4:
            monthStr = "APRIL";
            break;
        case 5:
            monthStr = "MAY";
            break;
        case 6:
            monthStr = "JUNE";
            break;
        case 7:
            monthStr = "JULY";
            break;
        case 8:
            monthStr = "AUGUST";
            break;
        case 9:
            monthStr = "SEPTEMBER";
            break;
        case 10:
            monthStr = "OCTOBER";
            break;
        case 11:
            monthStr = "NOVEMBER";
            break;
        case 12:
            monthStr = "DECEMBER";
            break;
    }
    
    return monthStr;
}

/*
This function takes in sales and tenure arrays and asks the user for sales and tenure data for
each employee. If the user inputs 0 0, the remaining items are left as is. Arrays must be 
initialized to 0.
Arguments:
   int * salesArr: list of sales values for all employees, modified in place
   int * tenureArr: list of tenure values for all employees, modified in place
*/
void parseInput(double * salesArr, double * tenureArr){
    for(int i = 0; i < NUM_EMPLOYEES; i++){
        int sales, tenure;

        printf("Enter the sales and tenure for next employee: ");
        scanf("%d %d", &sales, &tenure);

        if(sales == 0 && tenure == 0){
            return;
        }

        salesArr[i] = sales;
        tenureArr[i] = tenure;
    }
}

/*
This function will take in the filled array of monthly sales and returns the total
Arguments:
    double * salesArr: list of monthly sales values

Returns:
    double: total of sales array
*/
double calculateTotalSales(double * salesArr){
    double totalSales = 0;

    for(int i = 0; i < NUM_EMPLOYEES; i++){
        totalSales += salesArr[i];
    }

    return totalSales;
}

/*
This function calculates the total profit for the month using the total sales and profit margin
Arguments:
    double totalSales: total monthly sales

Returns:
    double: total monthly profit
*/
double calculateTotalProfit(double totalSales){
    return totalSales * COMPANY_PROFIT_MARGIN;
}

/*
This function calculates commissions for all employees based on individual sales
Arguments:
    double * salesArr: Monthly sales values
    double * commissionArr: Commission values, modified in place
*/
void calculateCommission(double * salesArr, double * commissionArr){
    for(int i = 0; i < NUM_EMPLOYEES; i++){
        commissionArr[i] = salesArr[i] * EMPLOYEE_COMISSION_RATE;
    }
}

/*
Calculates the bonuses for all employees based on total profit and individual tenure
Arguments:
    double totalProfit: Total company profit
    double * tenureArr: Employee tenure valules
    double * bonusArr: Employee bonus values, modified in place
*/
void calculateBonus(double totalProfit, double * tenureArr, double * bonusArr){
    for(int i = 0; i < NUM_EMPLOYEES; i++){
       double bonus = totalProfit * BONUS_RATE;
       int tenureDecades = (int) (tenureArr[i] / 10);
       bonus += totalProfit * tenureDecades * TENURE_BONUS_RATE;

       bonusArr[i] = bonus;
    } 
}

/*
Calculates net profit from total profit and total bonuses paid out
Arguments:
    double totalProfit: total company profit
    double totalBonus: total bonuses paid out
Returns:
    double: company net profit
*/
double calculateNetProfit(double totalProfit, double totalBonus){
    return totalProfit - totalBonus;
}

/*
Calculates federal withholding for all employees using commissions and bonuses
Arguments:
    double * commissionArr: Employee commission data
    double * bonusArr: Employee bonus data
    double * fedWArr: Employee federal withholding data, modified in place
*/
void calculateFedW(double * commissionArr, double * bonusArr, double * fedWArr){
    for(int i = 0; i < NUM_EMPLOYEES; i++){
        fedWArr[i] = (commissionArr[i] + bonusArr[i]) * FED_W;
    }
}

/*
Calculates the total of a given array
*/
double total(double * arr){
    double total = 0;

    for(int i = 0; i < NUM_EMPLOYEES; i++){
        total += round_to_2(arr[i]);
    }

    return total;
}

/*
Calculates state withholding for all employees using commissions and bonuses
*/
void calculateStateW(double * commissionArr, double * bonusArr, double * stateWArr){
    for(int i = 0; i < NUM_EMPLOYEES; i++){
        stateWArr[i] = (commissionArr[i] + bonusArr[i]) * STATE_W;
    }
}

/*
Calculates fica withholding for all employees using commissions and bonuses
*/
void calculateFICAW(double * commissionArr, double * bonusArr, double * FICAWArr){
    for(int i = 0; i < NUM_EMPLOYEES; i++){
        FICAWArr[i] = (commissionArr[i] + bonusArr[i]) * FICA;
    }
}

/*
Calculates net pay based on all compensation and withholding
*/
void calculateNetPay(double * commission, double * bonus, double * fed, double * state, double * fica,
        double * netPay){
    for(int i = 0; i < NUM_EMPLOYEES; i++){
        netPay[i] = commission[i] + bonus[i] - fed[i] - state[i] - fica[i];
    }
}
