/* 单向循环链表 - 只有尾指针 */

/*
    * 明确: malloc() 和 free() 的本质
    * 掌握: do-while 循环的逻辑
    * 循环链表用"回到起点"表示循环结束
    * free()之后不再解引用
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

/* 只维护尾指针 */
typedef struct {
    struct Node *tail;
} CSLL;

Node* initNode(int val) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;
    return node;
}

CSLL* initlist() {
    CSLL *list = (CSLL*) malloc(sizeof(CSLL));
    list->tail = NULL;
    return list;
}

void destroy_list(CSLL *list) {
    if (!list || !list->tail) {
        free(list);
        return;
    }
    Node *head = list->tail->next;
    Node *current = list->tail->next;   // 头结点
    Node *next;

    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != head);  // list->tail->next 始终指向同一个地址,没有更新
    
    free(list);
}

/* 判空 */
bool csll_empty(CSLL *list) {
    return (!list || list->tail == NULL);
}


/* 头插法 */
bool csll_push_front(CSLL *list, int val) {
    if (!list) return false;
    Node *node = initNode(val);
    
    
    if (csll_empty(list)) {
        // 空表
        list->tail = node;
        node->next = node;
        return true;
    } else {
        // 非空
        node->next = list->tail->next;
        list->tail->next = node;
    }

    return true;
}


/* 尾插法 */
bool csll_push_back(CSLL *list, int val) {
    if (!list) return false;
    Node *node = initNode(val);
    
    if (list->tail == NULL) {
        node->next = node;
        list->tail = node;
        return true;
    } else {
        node->next = list->tail->next;
        list->tail->next = node;
        list->tail = node;
    }
    return true;
}


/* 删除头部节点 */
bool csll_pop_front(CSLL *list, int *res) {
    if (!list || csll_empty(list)) return false;

    Node *head = list->tail->next;
    if (res) *res = head->val;

    if (list->tail == head) {
        // 只有一个元素
        list->tail = NULL;
        free(head);
        return true;
    } else {
        list->tail->next = head->next;
    }
    
    free(head);
    return true;
}

void csll_print(CSLL *list) {
    if (!list || csll_empty(list)) return;

    Node *current = list->tail->next;   // head

    do {
       printf("%d ", current->val);
       current = current->next;
    } while (current != list->tail->next);

    printf("\n");
    
}

int main() {
    /*
        1.	修 initNode：node->val = val
        2.	修 csll_empty：必须返回 bool
        3.	修 csll_pop_front：单节点判断用 head == tail
        4.	修 destroy_list：保存 head，释放完 free(list)
    */
}