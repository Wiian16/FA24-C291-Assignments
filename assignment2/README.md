## Assignmnet 2: FizzBuzz
### Design
This program will begin by taking in a user input. This input should be a positive integer. \
\
Upon revieving this integer, the program will enter a loop with an index starting at 0 and counting up to the given integer. \
\
When the program encounters a number that is divisible by 3, it will outout `Fizz` to `stdout`.
When it encounters a number that is divisible by 5 it will output `Buzz`.
When it encounters a divisible by both 3 and 5, it will output `FizzBuzz`.
Otherwise, it will output the current number. \
\
Each output will be on a new line. 

### Psuedocode
```
input := stdin

loop from 0 to input
    if index is divisible by 3
        print "Fizz"
    if index is divisible by 5 
        print "Buzz"
    if index is not divisible by 3 or 5 
        print index
    print newline
```
