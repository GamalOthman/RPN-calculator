# RPN-calculator
Reverse Polish Notation basic calculator with some functions.

 ## Overall Description

 * Reverse polish calculator is a basic calculator that receives it's
   operand after it's operators.
 * It's input will be like: (operand) (operand) (operator).
 * For instance, if we want to calculate the formula "3 + 4" we would
   write it in the form: "3 4 +" to the input of the calculator.
 * Also, "(1 - 2) * (4 + 5)" is entered as `1 2 - 4 5 + *`.
 * This calculator needs no parenthesis. When it receives an operator,
   it perform the operation on the last two operands behind it.
 * This calculator supports double-precision for all operands
 * This project is intended to make a small reverse polish calculator.
 * Please input operators and operands each separated by a space or a tab.

## Trigonometric Functions

 * Trigonometric functions embedded in this program is: `sin`, `cos`, `tan`, `exp`, `pow` and `sqrt`.
   
 *Example*   
   `90 sin↵`
   
 *Result*  
   `1`
   
 *Example*   
 `2 exp↵`
   
 *Result*   
   `7.3890561`
 
 *Example*   
 `5 2 pow↵`
   
 *Result*   
   `23`
 
## Orders:

### Print

   `print` order will print the top value of the stack.

   *Example*   
   `print↵`

   *Result*   
   `8.34`

### Duplicate

   `dup` order will duplicate it's operand.

   *Example*   
   `5 dup *↵`

   *Result*     
   `25`
 
### Swap
 
   `swap` order will swap the previous two operators.

   *Example*   
   `2 5 swap /↵`

   *Result*   
   `2.5`
 
### Clear
  
  `clear` order will clear the contents of stack[] and store[].

   *Example*   
   `clear↵`

   *Result*   
   ```
   stack cleared!   
   store cleared!
   ```

### Store

   `store` order will store the previous value in the corresponding one-char variable.

   *Example*   
   `5.67 store a↵`

   *Result*   
   `a = 5.67`

### View
  
   `view` order will view the contents of the corresponding variable/s.

   *Example*   
   `view a↵`

   *Result*     
   `a = 5.67`

   *Example*   
   `view a-z↵`

   *Result*   
   ```
   a = 5.67
   b = 0
   c = 0
   ...
   z = 0
   ```
  
### Exit
  
   `exit` order will exit the program.

   *Example*   
   `exit`
 
