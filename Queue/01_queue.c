/* 队列的顺序实现 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define MAXLENGTH 5

typedef struct {
    int data[MAXLENGTH];
    int front, rear;
} SeqQueue;

SeqQueue* initQueue() {
    SeqQueue* queue = (SeqQueue*) malloc(sizeof(SeqQueue));
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

bool queueEmpty(SeqQueue* queue) {
    return queue->front == queue->rear;
}

int getSize(SeqQueue* queue) {
    return queue->rear - queue->front;
}

bool push(SeqQueue* queue, int val) {
    // 判满
    if (queue->rear == MAXLENGTH) return false;

    queue->data[queue->rear++] = val;
    return true;
}

bool pop(SeqQueue* queue, int* val) {
    if (queueEmpty(queue)) return false;
    *val = queue->data[queue->front++];
    return true;
}

int main() {

}