/* 循环队列实现 - 维护size */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    int* nums;
    int front;
    int capacity;
    int size;  
} ArrayQueue;

ArrayQueue* initQueue(int capacity) {
    ArrayQueue* queue = (ArrayQueue*) malloc(sizeof(ArrayQueue));
    queue->capacity = capacity;
    queue->nums = (int*) malloc(sizeof(int) * capacity);
    queue->front = 0;
    queue->size = 0;
    return queue;
}

int getSize(ArrayQueue* queue) {
    return queue->size;
}

int getCapacity(ArrayQueue* queue) {
    return queue->capacity;
}

bool queueEmpty(ArrayQueue* queue) {
    return queue->size == 0;
}

bool queueFull(ArrayQueue* queue) {
    return queue->size == queue->capacity;
}

bool peek(ArrayQueue* queue, int* res) {
    if (queueEmpty(queue)) return false;
    *res = queue->nums[queue->front];
    return true;
}

bool push(ArrayQueue* queue, int val) {
    if (queueFull(queue)) return false;
    int index = (queue->front + queue->size) % queue->capacity;
    queue->nums[index] = val;
    queue->size++;
    return true;
}

bool pop(ArrayQueue* queue, int* res) {
    if (queueEmpty(queue)) return false;
    *res = queue->nums[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return true;
}


void destroyQueue(ArrayQueue* queue) {
    if (queueEmpty(queue)) return;
    free(queue->nums);
    free(queue);
}


void printQueue(ArrayQueue* queue) {
    for (int i = 0; i < queue->size; i++) {
        int index = (queue->front + i) % queue->capacity;
        printf("%d ", queue->nums[index]);
    }
    printf("\n");
}


int main() {
    printf("==== Test: initQueue ====\n");
    ArrayQueue* q = initQueue(5);
    if (!q) {
        printf("initQueue failed\n");
        return 0;
    }
    printf("capacity=%d size=%d\n", getCapacity(q), getSize(q));

    printf("\n==== Test: empty queue ====\n");
    printf("empty=%d full=%d\n", queueEmpty(q), queueFull(q));
    int x;
    printf("peek(empty)=%d\n", peek(q, &x));
    printf("pop(empty)=%d\n", pop(q, &x));

    printf("\n==== Test: push until full ====\n");
    for (int i = 1; i <= 6; i++) {
        bool ok = push(q, i * 10);
        printf("push(%d) => %d | size=%d\n", i * 10, ok, getSize(q));
        printQueue(q);
    }

    printf("\n==== Test: peek after push ====\n");
    if (peek(q, &x)) {
        printf("peek=%d\n", x);
    }

    printf("\n==== Test: pop several elements ====\n");
    for (int i = 0; i < 3; i++) {
        bool ok = pop(q, &x);
        printf("pop => %d, val=%d | size=%d\n", ok, x, getSize(q));
        printQueue(q);
    }

    printf("\n==== Test: wrap-around push ====\n");
    int vals[] = {111, 222, 333};
    for (int i = 0; i < 3; i++) {
        bool ok = push(q, vals[i]);
        printf("push(%d) => %d | size=%d\n", vals[i], ok, getSize(q));
        printQueue(q);
    }

    printf("\n==== Test: pop until empty ====\n");
    while (!queueEmpty(q)) {
        pop(q, &x);
        printf("pop => %d | size=%d\n", x, getSize(q));
        printQueue(q);
    }

    printf("\n==== Test: reuse after empty ====\n");
    push(q, 777);
    push(q, 888);
    printQueue(q);
    pop(q, &x); printf("pop=%d\n", x);
    pop(q, &x); printf("pop=%d\n", x);
    printf("empty=%d size=%d\n", queueEmpty(q), getSize(q));

    destroyQueue(q);
    printf("\n==== All tests finished ====\n");
    return 0;
}