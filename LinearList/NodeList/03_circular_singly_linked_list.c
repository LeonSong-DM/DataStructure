/* 单向循环链表 只有头指针*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int val;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} CSLL;


CSLL* initCSLL() {
    CSLL *csll = (CSLL*) malloc(sizeof(CSLL));
    if (!csll) return NULL;
    csll->head = NULL;
    return csll;
}

bool destroyCSLL(CSLL *csll) {
    if (!csll) return false;

    if (csll->head == NULL) {
        free(csll);
        return true;
    } else {
        Node *head = csll->head;
        Node *current = csll->head;
        Node *next;

        do {
            next = current->next;
            free(current);
            current = next;
        } while (current != head);

        free(csll);
    }
    return true;
}

bool csll_empty(CSLL *csll) {
    if (!csll) return false;
    return csll->head == NULL;
}

bool add_front(CSLL *csll, int val) {
    if (!csll) return false;

    Node *node = (Node*) malloc(sizeof(Node));
    if (!node) return false;
    node->val = val;

    if (csll_empty(csll)) {
        node->next = node;
        csll->head = node; 
    } else {
        node->next = csll->head;
        csll->head = node;
    }
    return false;
}

bool remove_front(CSLL *csll, int *res) {
    if (!csll || csll_empty(csll)) return false;

    Node *old_head = csll->head;

    *res = csll->head->val;

    if (csll->head->next == csll->head) {   
        free(old_head);
        csll->head = NULL;
        return true;
    } else {
        // 修改尾节点指向
        Node *tail = old_head;
        while (tail->next != old_head) {
            tail = tail->next;
        }
        tail->next = old_head->next;
        csll->head = old_head->next;
        free(old_head);
    }
    return true;
}


int main() {

}