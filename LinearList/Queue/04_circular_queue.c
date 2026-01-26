/* 循环队列 链表实现*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node{
    int val;
    struct Node* next;
} Node;

typedef struct {
    Node *front, *rear;
    int size;
} LinkedListQueue;

LinkedListQueue* initQueue() {
    LinkedListQueue* queue = (LinkedListQueue*) malloc(sizeof(LinkedListQueue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void destroyQueue(LinkedListQueue *queue) {
    // 释放节点
    while (queue->front != NULL)
    {
        Node *current = queue->front;
        queue->front = current->next;
        free(current);
    }
    // 释放结构体
    free(queue);
}

int getSize(LinkedListQueue *queue) {
    return queue->size;
}

bool queueEmpty(LinkedListQueue *queue) {
    return queue->size == 0;
}

bool push(LinkedListQueue* queue, int val) {
    // 创建节点
    Node *node = (Node*) malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;
    // 插入
    if (queueEmpty(queue)) {
        // 空队列, 同时设置front, rear
        queue->rear = node;
        queue->front = node;
        queue->size++;
        return true;
    }
    // 非空队列
    queue->rear->next = node;
    queue->rear = node;
    queue->size++;
    return true;
}

bool pop(LinkedListQueue* queue, int *res) {
    if (queueEmpty(queue)) return false;
    Node *tmp = queue->front;
    *res = tmp->val;
    queue->front = tmp->next;
    // size == 1时rear置空
    if (queue->size == 1) {
        queue->rear = NULL;
    }
    queue->size--;
    free(tmp);
    return true;
}

bool getTop(LinkedListQueue *queue, int *res) {
    if (queueEmpty(queue)) return false;
    *res = queue->front->val;
    return true;
}

void printQueue(LinkedListQueue *queue) {
    Node *current = queue->front;
    while (current != NULL)
    {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

int main() {
    /*
        注意点:
            出队时, 如果size == 1, 需要同时置空front和rear两个指针
            遗忘rear, 导致下一次入队时, rear还是上一次已经释放的节点

            入队时,注意队列是否为空,如果为空,需要同时更新front和rear两个指针
    */
    printf("==== Test0: init ====\n");
    LinkedListQueue* q = initQueue();
    if (!q) {
        printf("initQueue failed\n");
        return 0;
    }
    printf("size=%d empty=%d\n", getSize(q), queueEmpty(q));

    printf("\n==== Test1: empty pop/getTop ====\n");
    int x = -1;
    printf("getTop(empty)=%d\n", getTop(q, &x));
    printf("pop(empty)=%d\n", pop(q, &x));

    printf("\n==== Test2: push several ====\n");
    for (int i = 1; i <= 5; i++) {
        bool ok = push(q, i * 10);
        printf("push(%d) => %d | size=%d\n", i * 10, ok, getSize(q));
        printQueue(q);
    }

    printf("\n==== Test3: getTop after pushes ====\n");
    if (getTop(q, &x)) {
        printf("top=%d\n", x);
    } else {
        printf("getTop failed\n");
    }

    printf("\n==== Test4: pop two ====\n");
    for (int i = 0; i < 2; i++) {
        bool ok = pop(q, &x);
        printf("pop => %d, val=%d | size=%d empty=%d\n", ok, x, getSize(q), queueEmpty(q));
        printQueue(q);
    }

    printf("\n==== Test5: push more (interleave) ====\n");
    int vals[] = {111, 222, 333};
    for (int i = 0; i < 3; i++) {
        bool ok = push(q, vals[i]);
        printf("push(%d) => %d | size=%d\n", vals[i], ok, getSize(q));
        printQueue(q);
    }

    printf("\n==== Test6: pop until empty ====\n");
    while (!queueEmpty(q)) {
        bool ok = pop(q, &x);
        printf("pop => %d, val=%d | size=%d empty=%d\n", ok, x, getSize(q), queueEmpty(q));
        printQueue(q);
    }

    printf("\n==== Test7: reuse after empty ====\n");
    printf("push(777)=%d\n", push(q, 777));
    printf("push(888)=%d\n", push(q, 888));
    printQueue(q);
    if (getTop(q, &x)) printf("top=%d\n", x);

    pop(q, &x); printf("pop=%d\n", x);
    pop(q, &x); printf("pop=%d\n", x);
    printf("size=%d empty=%d\n", getSize(q), queueEmpty(q));

    printf("\n==== Cleanup ====\n");
    destroyQueue(q);
    printf("All tests finished.\n");
    return 0;
}