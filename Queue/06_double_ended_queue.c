/* 双端队列 - 基于单向链表实现 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} DoubleEndedQueue;

DoubleEndedQueue* initDEQueue() {
    DoubleEndedQueue *queue = (DoubleEndedQueue*) malloc(sizeof(DoubleEndedQueue));
    if (!queue) return NULL;
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    return queue;
}

void destroDEQueue(DoubleEndedQueue *queue) {
    if (!queue) return;
    Node *currrnt = queue->head;
    Node *next;

    while (currrnt != NULL) {
        next = currrnt->next;
        free(currrnt);
        currrnt = next;
    }

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    free(queue);
}

int getSize(DoubleEndedQueue *queue) {
    if (!queue) return -1;
    return queue->size;
}

bool queueEmpty(DoubleEndedQueue *queue) {
    if (!queue) return false;
    return queue->size == 0;
}


bool getFirst(DoubleEndedQueue *queue, int *res) {
    if (!queue || !res) return false;
    *res = queue->head->val;
    return true;
}

bool getLast(DoubleEndedQueue *queue, int *res) {
    if (!queue || !res) return false;
    *res = queue->tail->val;
    return true;
}

bool push(DoubleEndedQueue *queue, int val) {
    if (!queue) return false;

    Node *node = (Node*) malloc(sizeof(Node));
    if (!node) return false;

    node->val = val;
    
    if (getSize(queue) == 0) {
        node->next = NULL;
        queue->head = node;
        queue->tail = node;
        queue->size++;
    } else {
        node->next = queue->head;
        queue->head = node;
        queue->size++;
    }
    
    return true;
}

bool pop(DoubleEndedQueue *queue, int *res) {
    if (!queue || queueEmpty(queue)) return false;

    *res = queue->head->val;

    if (getSize(queue) == 1) {
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
    } else {
        Node *old_head = queue->head;
        queue->head = old_head->next;
        free(old_head);

        queue->size--;
    }
    return true;
}

bool pushFirst(DoubleEndedQueue *queue, int val) {
    if (!queue) return false;

    Node *node = (Node*) malloc(sizeof(Node));
    if (!node) return false;
    node->val = val;

    if (queueEmpty(queue)) {
        node->next = NULL;
        queue->head = node;
        queue->tail = node;
        queue->size++;
    } else {
        Node *old_head = queue->head;
        node->next = old_head;
        queue->head = node;
        queue->size++;
    }

    return true;
}

bool popLast(DoubleEndedQueue *queue, int *res) {
    if (!queue || queueEmpty(queue)) return false;
    *res = queue->tail->val;

    if (getSize(queue) == 1) {
        Node *node = queue->head;
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
        free(node);
    } else {
        // 获取尾节点的前一个节点
        Node *tail_before = queue->head;
        while (tail_before->next != queue->tail) {
            tail_before = tail_before->next;
        }

        // 更新tail
        queue->tail = tail_before;
        queue->tail->next = NULL;   // !!!
        queue->size--;
    }

    return true;
}


static void printQueue(DoubleEndedQueue *q, const char *tag) {
    printf("\n[%s] size=%d  head=%p  tail=%p\n",
           tag,
           q ? q->size : -1,
           q ? (void*)q->head : NULL,
           q ? (void*)q->tail : NULL);

    if (!q) return;

    printf("  data: ");
    Node *cur = q->head;
    while (cur) {
        printf("%d ", cur->val);
        cur = cur->next;
    }
    printf("\n");
}



int main(void) {
    DoubleEndedQueue *q = initDEQueue();
    assert(q != NULL);
    assert(getSize(q) == 0);
    assert(queueEmpty(q) == true);

    printQueue(q, "init");

    /* ---------- 空队列边界 ---------- */
    int x = 0;
    assert(pop(q, &x) == false);
    assert(popLast(q, &x) == false);

    /* 由于你 getFirst/getLast 没判断空，这里只验证“不调用”以免崩溃 */
    if (!queueEmpty(q)) {
        assert(getFirst(q, &x) == true);
        assert(getLast(q, &x) == true);
    } else {
        printf("[empty] skip getFirst/getLast to avoid crash (need empty-check in functions)\n");
    }

    /* ---------- 插入：pushFirst / push（你当前 push 也是头插） ---------- */
    assert(pushFirst(q, 10) == true);  // [10]
    assert(pushFirst(q, 20) == true);  // [20,10]
    assert(push(q, 30) == true);       // [30,20,10]
    assert(getSize(q) == 3);
    assert(queueEmpty(q) == false);

    printQueue(q, "after pushFirst(10), pushFirst(20), push(30)");

    /* ---------- 取首/取尾（前提：非空） ---------- */
    assert(getFirst(q, &x) == true);
    printf("getFirst => %d (expect 30)\n", x);
    assert(x == 30);

    assert(getLast(q, &x) == true);
    printf("getLast  => %d (expect 10)\n", x);
    assert(x == 10);

    /* ---------- pop：删头 ---------- */
    assert(pop(q, &x) == true);
    printf("pop => %d (expect 30)\n", x);
    assert(x == 30);
    assert(getSize(q) == 2);

    printQueue(q, "after pop (remove head)");

    /* ---------- popLast：删尾 ---------- */
    assert(popLast(q, &x) == true);
    printf("popLast => %d (expect 10)\n", x);
    assert(x == 10);
    assert(getSize(q) == 1);

    printQueue(q, "after popLast (remove tail)");

    /* ---------- 单元素边界 ---------- */
    assert(getFirst(q, &x) == true);
    assert(getLast(q, &x) == true);
    printf("single element => %d (expect 20)\n", x);
    assert(x == 20);

    /* popLast 删除最后一个 */
    assert(popLast(q, &x) == true);
    printf("popLast(single) => %d (expect 20)\n", x);
    assert(x == 20);
    assert(getSize(q) == 0);
    assert(queueEmpty(q) == true);

    printQueue(q, "after popLast on single element");

    /* 再次验证空队列 pop */
    assert(pop(q, &x) == false);
    assert(popLast(q, &x) == false);

    /* ---------- 释放队列 ---------- */
    destroDEQueue(q);
    q = NULL;

    printf("\nAll tests passed (logic-wise). Note: current implementation still leaks memory in pop(size==1) and popLast(size>1).\n");
    return 0;
}