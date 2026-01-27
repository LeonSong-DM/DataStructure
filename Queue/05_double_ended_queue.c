/* 双端队列 - 基于环形数组(牺牲一个存储单元)实现 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct {
    int capacity;
    int *nums;
    int front, rear;
} DoubleEndedQueue;


DoubleEndedQueue *initDoubleEndedQueue(int capacity) {
    assert(capacity > 1);
    DoubleEndedQueue *queue = (DoubleEndedQueue*) malloc(sizeof(DoubleEndedQueue));
    queue->capacity = capacity;     // 1- capacity没有赋值给queue的内部变量
    queue->nums = (int*) malloc(sizeof(int) * queue->capacity);
    queue->front = 0;
    queue->rear = 0;
    return queue;
}


void destroyDoubleEndedQueue(DoubleEndedQueue *queue) {
    free(queue->nums);
    free(queue);
}

int getSize(DoubleEndedQueue *queue) {
    if (!queue) return -1;
    // return queue->rear % queue->capacity - queue->front % queue->capacity;   逻辑错误
    return (queue->rear - queue->front + queue->capacity) % queue->capacity;
}


bool queueEmpty(DoubleEndedQueue *queue) {
    if (!queue) return false;
    return queue->front == queue->rear;
}


bool queueFull(DoubleEndedQueue *queue) {
    if (!queue) return false;
    // return (queue->rear % queue->capacity) + 1 == queue->front;  逻辑不对
    return (queue->rear + 1) % queue->capacity == queue->front;

}

bool getFirst(DoubleEndedQueue *queue, int *res) {
    if (!queue || !res || queueEmpty(queue)) return false;

    *res = queue->nums[queue->front];
    return true;
}

bool getLast(DoubleEndedQueue *queue, int *res) {
    if (!queue || !res || queueEmpty(queue)) return false;

    *res = queue->nums[queue->rear - 1];
    return true;
}

bool push(DoubleEndedQueue *queue, int val) {
    if (!queue || queueFull(queue)) return false;

    queue->nums[queue->rear] = val;
    queue->rear = (queue->rear + 1) % queue->capacity;
    return true;
}

bool pop(DoubleEndedQueue *queue, int *res) {
    if (!queue || !res || queueEmpty(queue)) return false;

    *res = queue->nums[queue->front];
    queue->front = (queue->front + 1) % queue ->capacity;
    return true;
}


bool pushFirst(DoubleEndedQueue *queue, int val) {
    if (!queue || queueFull(queue)) return false;
    
    // f相对位置前移一位插入
    queue->front = (queue->front + queue->capacity - 1) % queue->capacity;  // 2- 注意优先级,加()区分
    queue->nums[queue->front] = val;
    return true;
} 

bool popLast(DoubleEndedQueue *queue, int *res) {
    if (!queue || !res || queueEmpty(queue)) return false;

    // rear相对位置前移一位
    queue->rear = (queue->rear + queue ->capacity -1) % queue->capacity;     // 2- 注意优先级,加()区分
    *res = queue->nums[queue->rear];
    return true;
}

int main() {
    printf("Hello World.\n");
    return 0;
}

/*
    是否工作日
    是否节假日
    时间
    楼层功能
    视觉模型 - 人是否在等电梯 ?
    有人等 - 自动识别 优先调度
    做功少. 效率高.
*/