/**
 * @Author: leonsong
 * @Date:   2026-01-27 00:21:23
 * @Last Modified by:   leonsong
 * @Last Modified time: 2026-03-05 19:12:49
 * @Function: XXX
 */
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