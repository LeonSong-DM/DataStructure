#include<stdio.h>
#include<stdlib.h>

// 使用typedef必须要起别名
typedef struct ListNode{
    // 结构体内部引用自身类型需要加struct关键字
    // 内部使用了struct ListNode,结构体标签不能匿名
    struct ListNode *next;
    int value;
} ListNode;

ListNode *newListNode(int val) {
    ListNode *node;
    node = (ListNode*)malloc(sizeof(ListNode));
    node->value = val;
    node->next = NULL;
    return node;
}


void print_ListNode(ListNode *head) {
    ListNode *n = head;
    while(n != NULL) {
        printf("%d ", n->value);
        n = n->next;
    }
    printf("\n");
    free(n);
}

void insert(ListNode *n0, ListNode *p) {
    ListNode *n1= n0->next;
    n0->next = p;
    p->next = n1;
}

void removeNode(ListNode *n0) {
    if (!n0->next || !n0) return;
    // 删除n0之后的首个节点
    ListNode *p;
    p = n0->next;
    n0->next = p->next;
    free(p);
}

ListNode *access(ListNode *head, int index) {
    /*访问链表中索引为index的节点*/
    if (index < 0) return NULL;
    for (int i = 0; i < index; i++) {
        if (!head) return NULL;
        head = head->next;
    }
    return head;
}

int find(ListNode *head, int value) {
    /*查找值为value的首个节点,返回索引*/
    if (!head || value < 0) return -1;
    int count = 0;
    while (head) {
        if (head->value == value) return count;
        head = head->next;
        count++;
    }
    return -1;
}

int main() {
    // 创建节点
    ListNode* n1 = newListNode(1);
    ListNode* n2 = newListNode(2);
    ListNode* n3 = newListNode(3);
    ListNode* n4 = newListNode(4);

    // 链接引用
    n1->next = n2;
    n2->next = n3;
    n3->next = n4; 

    print_ListNode(n1);

    ListNode *access_node = access(n1, 2);
    printf("The value of index of 2 is : %d\n", access_node->value);
    
    int target = 3;
    int target_index = find(n1, target);
    printf("The index of target is : %d\n", target_index);

    
}