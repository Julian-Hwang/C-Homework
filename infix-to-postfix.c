#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_STACK_SIZE 100

typedef int element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item) {
	if (is_full(s)){
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType* s) {
	if (is_empty(s)){
		fprintf(stderr, "스택 포화 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s)	{
	if (is_empty(s)){
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

int check_matching(const char* in){
	StackType s;
	char ch, open_ch;
	int i, n = strlen(in);
	init_stack(&s);
	
    for (i = 0; i < n; i++) {
		ch = in[i];
		switch (ch) {
			case '(': case '[': case '{':
				push(&s, ch);
				break;
			
            case ')': case']': case '}':
				if (is_empty(&s)) return 0;
				else {
					open_ch = pop(&s);
					if ((open_ch == '(' && ch != ')') ||
						(open_ch == '[' && ch != ']') ||
						(open_ch == '{' && ch != '}')) {
						
                        return 0;
				}
				break;
		}
	}

	}
	if (!is_empty(&s)) return 0;
	
    return 1;
}

int eval(char exp[]){
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;
	init_stack(&s);

	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%' && ch != '^') {
			value = ch - '0';
			push(&s, value);
		}
		
        else {
			op2 = pop(&s);
			op1 = pop(&s);

			switch (ch) {
				case '+': push(&s, op1 + op2); break;
				case '-': push(&s, op1 - op2); break;
				case '*': push(&s, op1 * op2); break;
				case '/': push(&s, op1 / op2); break;
				case '%': push(&s, op1 % op2); break;
				case '^': push(&s, pow(op1, op2)); break;
			}

		}
	}

	return pop(&s);
}

int prec(char op){
	switch (op) {
		case '(': case ')': return 0;
		case '+': case '-': return 1;
		case '%': case '*': case '/': return 2;
		case '^': return 3;
	}
	return -1;
}

void infix_to_postfix(char exp[], char post[]) // 입력(infix): exp[], 결과(postfix): post[]
{
	int i = 0, j = 0;
	char ch;
	char top_op;
	int len = strlen(exp);
	StackType s;
	init_stack(&s);
	
    for (i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
			case '+': case '-': case '*': case '/': case '%': case '^':
		
        	while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
			post[j++] = pop(&s);
			push(&s, ch);
			break;

			case '(':
			push(&s, ch);
			break;

			case ')':
			top_op = pop(&s);
			while (top_op != '('){
				post[j++] = top_op;
				top_op = pop(&s);
			}
			break;

			default:
			post[j++] = ch;
			break;
		}
	}

	while (!is_empty(&s))
		post[j++] = pop(&s);
		post[j] = '\0';
}

int main(){
	char* s;
	char* p;
	s = (char*)malloc(sizeof(char));
	p = (char*)malloc(sizeof(char));
	scanf("%s",s);

	if (check_matching(s) == 1) {
		infix_to_postfix(s,p);
		printf("POSTFIX: %s",p);
		printf("\n");
		printf("RESULT=%d\n", eval(p));
	}

	else {
		printf("Error: 괄호가 올바르지 않음.\n");
	}
	
    return 0;
}
