/* 栈的顺序表实现 */

#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
# define MAXLENGTH 10

typedef struct {
    int data[MAXLENGTH];
    int top;
} SeqStack;

void InitStack(SeqStack* stack) {
    stack->top = -1;
}

bool StackEmpty(SeqStack* stack) {
    if (stack->top == -1) {
        return true;
    } else {
        return false;
    }
}



bool push(SeqStack* stack, int val) {
    if (stack->top == MAXLENGTH - 1) return false;
    stack->data[++stack->top] = val;
    return true;
}

bool pop(SeqStack* stack, int* res) {
    if (StackEmpty(stack)) return false;
    *res = stack->data[stack->top--];
    return true;
}

bool getTop(SeqStack* stack, int* res) {
    if (StackEmpty(stack)) return false;
    *res = stack->data[stack->top];
    return true;
}

bool destroyStack(SeqStack* stack) {
    stack->top = -1;
    return true;
}

int main() {
    SeqStack s;
    InitStack(&s);
    printf("InitStack\n");
    printf("stack.top : %d\n", s.top);

    push(&s, 1);
    printf("push : %d\n", 1);
    push(&s, 2);
    printf("push : %d\n", 2);
    push(&s, 3);
    printf("push : %d\n", 3);
    push(&s, 4);
    printf("push : %d\n", 4);

    printf("current stack: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", s.data[i]);
    }
    printf("\n");

    int pop_res;
    pop(&s, &pop_res);
    printf("pop res: %d\n", pop_res);


}