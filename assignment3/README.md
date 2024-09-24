## Assignment 3: University Payroll Calculator

### Design
This program will handle payroll calculations for a university system.
Each type of employee will have different rules for how they work and how they are paid,
with correspondingly different inputs. \
\
When the user quits the program, all the types of employees entered will be printed in a formatted
table with the employee type, average salary, and average pay.

### Psuedocode
```
const MONTHS_PER_YEAR := 12
const WEEKS_PER_MONTH := 4
const HOURS_PER_WEEK := 40

loop until user quits program
    input := stdin
    if validate() fails
        print warning
        continue

    output := "EMPLOYEE_TYPE        AVG_SALARY      AVG_PAY\n"
    employee_type := First char of input
    
    switch(employee_type)
        each case handles input and formatting output for each employee type
            output += "$employee_type_long      $avg_salary     $avg_pay\n"
        quit case breaks the loop
        default case prints a warning and continues

print output
exit


function validate(input)
    return true if input has a valid character, then one or two floats, false otherwise
```
