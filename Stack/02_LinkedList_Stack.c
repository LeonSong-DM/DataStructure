/* 栈的链表实现 - 无头节点 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node{
    struct Node* next;
    int val;
} Node;

typedef struct {
    Node* top;
    int size;
} LinkedListStack;

LinkedListStack* createLinkedListStack() {
    LinkedListStack* stack = (LinkedListStack*) malloc(sizeof(LinkedListStack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

bool stackEmpty(LinkedListStack* stack) {
    if (!stack) return false;
    return stack->size == 0;
}


bool push(LinkedListStack* stack, int val) {
    if (!stack) return false;
    Node* node = (Node*) malloc(sizeof(Node));
    node->val = val;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
    return true;
}

bool pop(LinkedListStack* stack, int* res) {
    if (!stack || stackEmpty(stack) || !res) return false;
    Node* currentTop = stack->top;
    *res = currentTop->val;

    stack->top = currentTop->next;
    free(currentTop);
    stack->size--;
    return true;
}

bool getTop(LinkedListStack* stack, int* res) {
    if (stackEmpty(stack)) return false;
    *res = stack->top->val;
    return true;
}

void destroyStack(LinkedListStack* stack) {
    /* 明确有哪些内存空间是动态申请出来的 : 1.每个节点 2.当前栈*/
    while (stack->top) {
        Node* nextNode = stack->top->next;
        free(stack->top);
        stack->top = nextNode;
    }
    free(stack);
}

int main() {
    LinkedListStack* stack;
    stack = createLinkedListStack();
    
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);

    // 查看当前栈元素
    Node* current = stack->top;
    while (current) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
    
    int pop_res;
    pop(stack, &pop_res);
    printf("pop res: %d\n", pop_res);

    int top_val;
    getTop(stack, &top_val);
    printf("top res: %d\n", top_val);

}