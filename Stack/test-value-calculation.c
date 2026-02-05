/*
 * @Author: LeonSong 
 * @Date: 2026-02-01 17:38:47 
 * @Last Modified by: LeonSong
 * @Last Modified time: 2026-02-03 19:08:33
 */

/**
 *  栈在值计算的应用,包括:
 *      - 利用栈结构计算表达式
 *          - 准备数字栈和运算符栈, 扫描表达式, 数字压栈 
 *      - 中缀表达式转前缀表达式
 *      - 中缀表达式转后缀表达式
 *      - 利用栈结构计算前缀表达式
 *      - 利用栈结构计算后缀表达式
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

/* 数字栈 */
typedef struct {
    int top;
    int data[MAX];
} NumStack;

NumStack* initNumStack() {
    NumStack *stack = malloc(sizeof(NumStack));
    stack->top = -1; 
    return stack;
}

int isNumEmpty(NumStack *stack) { return stack->top == -1; }

void pushNum(NumStack *stack, int val) {stack->data[++stack->top] = val; }

int popNum(NumStack *stack) { return stack->data[stack->top--]; }




/* 运算符栈 */
typedef struct {
    int top;
    char data[MAX];
} OpStack;

OpStack* initOpStack() {
    OpStack* stack = malloc(sizeof(OpStack));
    stack->top = -1; 
    return stack;
}

int isOpEmpty(OpStack *stack) { return stack->top == -1; }

void pushOp(OpStack *stack, char c) {stack->data[++stack->top] = c; }

char popOp(OpStack *stack) { return stack->data[stack->top--]; }

char peekOp(OpStack *stack) { return stack->data[stack->top]; }


/* 判断优先级 */
int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

/* 两数计算 */
int apply(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a-b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}


int evaluate(const char *expr) {
    // 声明栈 && 初始化
    NumStack *num_stack = initNumStack(); 
    OpStack *op_stack = initOpStack();

    // 遍历表达式
    int i = 0;
    while (expr[i]) {
        // 跳过空格
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        // 读多位整数
        if (isdigit(expr[i])) {
            int val = 0;
            while (isdigit(expr[i])) {
                val = val * 10 + (expr[i] - '0');
                i++;
            }
            
            // 入栈
            pushNum(num_stack, val);
            continue;
        }

        // 左括号
        if (expr[i] == '(') {
            pushOp(op_stack, expr[i]);
        } else if(expr[i] == ')') {
            // 右括号 (数字栈不为空)
            while (isNumEmpty(num_stack) && peekOp(op_stack) != '(') {
                int b = popNum(num_stack);
                int a = popNum(num_stack);
                char op = popOp(op_stack);
                pushNum(num_stack, apply(a, b, op));
            }

            if (!isOpEmpty(op_stack) && peekOp(op_stack) == '(') {
                popOp(op_stack);
            }

        } else {
            // 运算符
            while (!isOpEmpty(op_stack) 
            && precedence(peekOp(op_stack)) >= precedence(expr[i]) ) {
                int b = popNum(num_stack);
                int a = popNum(num_stack);
                char op = popOp(op_stack);
                pushNum(num_stack, apply(a, b, op));

            }
            pushOp(op_stack, expr[i]);
        }
        i++;

    }
    // 清算剩余
    while (!isOpEmpty(op_stack)) {
        int b = popNum(num_stack);
        int a = popNum(num_stack);
        char op = popOp(op_stack);
        pushNum(num_stack, apply(a, b, op));
    }
    
    return popNum(num_stack);
}


int main() {
    const char *expr = "3 + 4 * 2 / ( 1 - 5 )";
    int result = evaluate(expr);
    printf("Expression: %s\n", expr);
    printf("Result: %d\n", result);
    return 0;
}