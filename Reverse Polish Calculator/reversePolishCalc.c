/* ## Overall Description: ##
 *
 * reverse polish calculator is a basic calculator that receives it's
 * operand after it's operators.
 * It's input will be like: (operand) (operand) (operator).
 * For instance, if we want to calculate the formula "3 + 4" we would
 * write it in the form: "3 4 +" to the input of the calculator.
 * Also, "(1 - 2) * (4 + 5)" is entered as "1 2 - 4 5 + *".
 * This calculator needs no parenthesis. When it receives an operator,
 * it perform the operation on the last two operands behind it.
 *
 * This calculator supports double-precision for all operands
 *
 * This project is intended to make a small reverse polish calculator.
 * Please input operators and operands each separated by a space or a tab.
 *
 * ## Trigonometric Functions: ##
 *
 * You can use trigonometric functions like(sin, cos, tan, exp, pow, sqrt)
 * Example: 90 sin↵
 * Result: 1
 *
 * Example 2: 2 exp↵
 * Result 2: 7.3890561
 *
 * Example 3: 5 2 pow↵
 * Result 3: 23
 *
 * ## Orders: ##
 *
 * "print" order will print the top value of the stack.
 * Example: print↵
 * Result: 8.34
 *
 * "dup" order will duplicate it's operand.
 * Example: 5 dup *↵
 * Result: 25
 *
 * "swap" order will swap the previous two operators.
 * Example: 2 5 swap /↵
 * Result: 2.5
 *
 * "clear" order will clear the contents of stack[] and store[].
 * Example: clear↵
 * Result: stack cleared!↵ store cleared!
 *
 * "store" order will store the previous value in the corresponding one-char variable.
 * Example: 5.67 store a↵
 * Result: a = 5.67
 *
 * "view" order will view the contents of the corresponding variable/s.
 * Example: view a↵
 * Result: a = 5.67
 * Example 2: view a-z↵
 * Result 2: a = 5.67↵ b = 0↵ ... z = 0
 */

#include <stdio.h>
#include <stdlib.h>			//atof()
#include <ctype.h>			//isdigit(), isblank(), isalpha()
#include <string.h>			//strcmp()
#include <math.h>			//sin(), sqrt(), ...

#define MAX 100
#define STKMAX 50

#define NUMBER 	'0'
#define PRINT 	'1'
#define DUP 	'2'
#define SWAP 	'3'
#define CLEAR 	'4'

#define	SIN	'5'
#define COS	'6'
#define TAN	'7'
#define EXP	'8'
#define POW	'9'
#define SQRT	'A'

#define STORE	'B'
#define VIEW	'C'

char inStr[MAX];
double stack[STKMAX];
double store[26];
int sp = 0;				//stack pointer
int getInput(void);
void push(double);
double pop(void);
double popVal = 0.0;			//value from pop()
char read(void);
char readVal = 0;			//value from read()
void unread(char);
void clear(char []);

char calcInput[MAX] = "4 3 -\n";
int calcp = 0;

int main()
{
	int i, input = 0;
	double operand2 = 0.0;
	double temp = 0.0;
	double temp2 = 0.0;
	char view1 = 0;
	char view2 = 0;

	//while(MAX == MAX){
	while( (input = getInput()) != EOF ){
		switch(input){
		//number:
		case NUMBER:
			push(atof(inStr));
			break;
		case PRINT:
			//if stack is empty, pop() will print "stack empty!";
			if( sp==0 ) {pop(); break;}
			temp = pop();
			printf("%.8g\n", temp);
			push(temp);
			break;
		case DUP:
			temp = pop();
			push(temp);
			push(temp);
			//printf("%.8g %.8g ", stack[sp-2], stack[sp-1]);
			break;
		case SWAP:
			temp = pop();
			temp2 = pop();
			push(temp);
			push(temp2);
			//printf("%.8g %.8g ", stack[sp-2], stack[sp-1]);
			break;
		case CLEAR:
			for(sp=STKMAX-1; sp>0; sp--)
				stack[sp] = '\0';
			stack[sp] = '\0';
			for(i=26-1; i>0; i--)
				store[i] = '\0';
			store[i] = '\0';

			printf("stack cleared!\nstore cleared!\n");
			break;
		case SIN:
			push(sin(M_PI/180*pop()));
			break;
		case COS:
			push(cos(M_PI/180*pop()));
			break;
		case TAN:
			push(tan(M_PI/180*pop()));
			break;
		case EXP:
			push(exp(pop()));
			break;
		case POW:
			operand2 = pop();
			push(pow(pop(), operand2));
			break;
		case SQRT:
			push(sqrt(pop()));
			break;
		case STORE:
			//skip whitespaces to detect variable
			while( read() == ' ' )
				;
			//store the value it's proper position in store[]
			store[readVal-'a'] = pop();
			printf("%c = %.8g\n",readVal ,store[readVal-'a']);
			read();
			break;
		case VIEW:
			while( read() == ' ' )
				;
			view1 = readVal;
			if( read() == '\n' ){
				printf("%c = %.8g\n",view1 ,store[view1-'a']);
				break;
			}
			if( readVal == '-'){
				for( view2=read(), i=view1; i<=view2; i++ )
					printf("%c = %.8g\n", i, store[i-'a']);
			}
			read();
			break;

		//math operations:
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			operand2 = pop();
			push(pop() - operand2);
			break;
		case '/':
			if( (operand2 = pop()) == 0 ){
				printf("Division by zero!\n");
				return 0;
			}
			push(pop() / operand2);
			break;
		case '%':
			if( (operand2 = pop()) == 0 ){
				printf("Division by zero!\n");
				return 0;
			}
			push( (int) pop() % (int) operand2 );
			break;

		//result request:
		case '\n':
			printf("%.8g\n", pop());
			break;
		default:
			printf("Undefined input!\n");
			break;
		}
	}
	return 0;
}

int getInput()
{
	int i=0;
	clear(inStr);

	char oneCharReturn[MAX] = "\n+*/%";

	//if input is blank or tap, skip it
	while( isblank(read()) )
		;
	inStr[i++] = readVal;
	inStr[i] = '\0';

	if( strchr(oneCharReturn, readVal) != '\0' )
		return readVal;
	if( readVal == '-' ) {
		if( !isdigit(read()) ){
			unread(readVal);
			return '-';
		}
		else
			unread(readVal);
	}
	if( isalpha(readVal) )
		while( read() != '\n' && i < 10 ){
			inStr[i++] = readVal;

			if( !strcmp(inStr, "print") ){ getchar(); return PRINT; }
			if( !strcmp(inStr, "dup") ){ return DUP; }
			if( !strcmp(inStr, "swap") ){ return SWAP; }
			if( !strcmp(inStr, "clear") ){ getchar(); return CLEAR; }

			if( !strcmp(inStr, "sin") ){ return SIN;}
			if( !strcmp(inStr, "cos") ){ return COS;}
			if( !strcmp(inStr, "tan") ){ return TAN;}
			if( !strcmp(inStr, "exp") ){ return EXP;}
			if( !strcmp(inStr, "pow") ){ return POW;}
			if( !strcmp(inStr, "sqrt") ){ return SQRT;}

			if( !strcmp(inStr, "store") ){ return STORE;}
			if( !strcmp(inStr, "view") ){ return VIEW;}
	}
	if( isdigit(readVal) || readVal == '-' ){
		while( isdigit(read()) )
			inStr[i++] = readVal;
		if(readVal == '.'){
			inStr[i++] = '.';
			while( isdigit(read()) )
				inStr[i++] = readVal;
		}

		if( readVal != EOF )
			unread(readVal);
		inStr[i] = '\0';
		return NUMBER;
	}
	return 0;
}

void push(double value){
	if( sp<100 )
		stack[sp++]=value;
	else
		printf("stack full!\n");
}

double pop(void) {
	if( sp>0 ){
		popVal = stack[--sp];
		return popVal;
	}
	else
		printf("stack empty!\n");
	return 0.0;
}

#define BUFMAX 1

char buffer[BUFMAX];
int bufp=0;

char read(void)
//reads the next char.
{
	readVal = bufp > 0? buffer[--bufp]: getchar();
	return readVal;
}

void unread(char c)
//store the previous char.
{
	if( bufp  < BUFMAX )
		buffer[bufp++] = c;
	else
		printf("Buffer array is full!");
}

void clear(char s[]){
	int i;
	for(i=0; i<MAX; i++)
		s[i]='\0';
}
