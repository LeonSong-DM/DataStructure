/* 循环队列实现 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

typedef struct {
    int* nums;
    int front, rear;
    int capacity;
} ArrayQueue;

/* 构造函数 */
ArrayQueue* initQueue(int capacity) {
    ArrayQueue* queue = (ArrayQueue*) malloc(sizeof(ArrayQueue));
    queue->capacity = capacity;
    queue->nums = (int*) malloc(sizeof(int) * queue->capacity);
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

/* 获取队列容量 */
int getCapacity(ArrayQueue* queue) {
    return queue->capacity;
}

/* 获取队列长度 */
int getSize(ArrayQueue* queue) {
    return (queue->rear - queue->front + queue->capacity) % queue->capacity;
}

/* 判空 */
bool queueEmpty(ArrayQueue* queue) {
    return queue->front == queue->rear;
}

/* 判满 */
bool queueFull(ArrayQueue* queue) {
    return (queue->rear + 1) % queue->capacity == queue->front;
}

/* 访问首元素 */
int peek(ArrayQueue* queue) {
    assert(getSize(queue) != 0 );
    return queue->nums[queue->front];
}

/* 入队 */
bool push(ArrayQueue* queue, int val) {
    if (queueFull(queue)) return false;
    queue->nums[queue->rear] =  val;
    queue->rear = (queue->rear + 1) % queue->capacity;
    return true;
}


/* 出队 */
bool pop(ArrayQueue* queue, int* res) {
    if (queueEmpty(queue)) return false;
    *res = queue->nums[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    return true;
}


/* 销毁队列 */
void destroyQueue(ArrayQueue* queue) {
    free(queue->nums);
    free(queue);
}

/* 打印队列 - 环形顺序 */
void printQueue(ArrayQueue* queue) {
    /* from front -> to rear */
    int length = getSize(queue);
    for (int i = 0; i < length; i++) {
        int index = (queue->front + i) % queue->capacity;
        printf("%d ", queue->nums[index]);
    }
    printf("\n");
}

int main() {
    // 测试 0：创建队列
    ArrayQueue* q = initQueue(5);  // 注意：该实现判满用 (rear+1)%cap==front，会“空出1格”
    assert(q != NULL);
    printf("capacity=%d\n", getCapacity(q));

    // 测试 1：空队列行为
    printf("\n[Test1] empty checks\n");
    printf("queueEmpty=%d, queueFull=%d, size=%d\n", queueEmpty(q), queueFull(q), getSize(q));
    int x = -1;
    printf("pop(empty)=%d\n", pop(q, &x));     // 期望 false
    // peek 在空队列会触发 assert，因此这里不调用 peek

    // 测试 2：连续入队，直到满（按你的判满逻辑，capacity=5 最多入 4 个）
    printf("\n[Test2] push until full\n");
    for (int i = 1; i <= 6; i++) {
        bool ok = push(q, i * 10);
        printf("push(%d) => %d | front=%d rear=%d size=%d full=%d\n",
               i * 10, ok, q->front, q->rear, getSize(q), queueFull(q));
        if (!ok) break;
    }
    printf("peek=%d\n", peek(q));
    printf("printQueue:\n");
    printQueue(q);

    // 测试 3：出队两个元素
    printf("\n[Test3] pop two\n");
    for (int i = 0; i < 2; i++) {
        bool ok = pop(q, &x);
        printf("pop => %d, val=%d | front=%d rear=%d size=%d empty=%d\n",
               ok, x, q->front, q->rear, getSize(q), queueEmpty(q));
    }
    printf("printQueue:\n");
    printQueue(q);

    // 测试 4：再入队若干，触发 rear 回环
    printf("\n[Test4] wrap-around push\n");
    int vals[] = {111, 222, 333, 444};
    for (int i = 0; i < 4; i++) {
        bool ok = push(q, vals[i]);
        printf("push(%d) => %d | front=%d rear=%d size=%d full=%d\n",
               vals[i], ok, q->front, q->rear, getSize(q), queueFull(q));
    }
    printf("peek=%d\n", peek(q));
    printf("printQueue:\n");
    printQueue(q);

    // 测试 5：出队直到空
    printf("\n[Test5] pop until empty\n");
    while (!queueEmpty(q)) {
        bool ok = pop(q, &x);
        printf("pop => %d, val=%d | front=%d rear=%d size=%d empty=%d\n",
               ok, x, q->front, q->rear, getSize(q), queueEmpty(q));
    }
    printf("printQueue:\n");
    printQueue(q);

    // 测试 6：空队列再入队、再出队（复用场景）
    printf("\n[Test6] reuse after empty\n");
    printf("push(777)=%d\n", push(q, 777));
    printf("push(888)=%d\n", push(q, 888));
    printf("peek=%d\n", peek(q));
    printf("printQueue:\n");
    printQueue(q);
    pop(q, &x); printf("pop val=%d\n", x);
    pop(q, &x); printf("pop val=%d\n", x);
    printf("empty=%d size=%d\n", queueEmpty(q), getSize(q));

    // 收尾：销毁
    destroyQueue(q);
    printf("\nAll tests finished.\n");
    return 0;

    /*
        更正点:
            1. getSize()写成非负
            2. 判空字符使用错误
            3. printQueue()没有按照环形顺序开始
    */
}