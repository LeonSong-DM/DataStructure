/**
 * @Author: leonsong
 * @Date:   2026-03-05 20:16:47
 * @Last Modified by:   leonsong
 * @Last Modified time: 2026-03-05 20:18:05
 * @Function: XXX
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/* ================== Linked Queue (store TreeNode*) ================== */

typedef struct QNode {
    TreeNode *data;
    struct QNode *next;
} QNode;

typedef struct Queue {
    QNode *head;   // front
    QNode *tail;   // rear
    int length;
} Queue;

Queue* queue_create(void) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    if (!q) return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->length = 0;
    return q;
}

void queue_destroy(Queue *q) {
    if (!q) return;
    QNode *cur = q->head;
    while (cur) {
        QNode *next = cur->next;
        free(cur);
        cur = next;
    }
    free(q);
}

int queue_empty(const Queue *q) {
    return (!q || q->length == 0);
}

int queue_push(Queue *q, TreeNode *x) {
    if (!q) return -1;

    QNode *n = (QNode*)malloc(sizeof(QNode));
    if (!n) return -1;
    n->data = x;
    n->next = NULL;

    if (q->tail) {
        q->tail->next = n;
    } else {
        // 空队列：head 和 tail 都指向新节点
        q->head = n;
    }

    q->tail = n;
    q->length++;
    return 0;
}

TreeNode* queue_pop(Queue *q) {
    if (!q || q->length == 0) return NULL;

    QNode *front = q->head;
    TreeNode *res = front->data;

    q->head = front->next;
    if (q->head == NULL) {
        // 出队后为空，tail 也要置空
        q->tail = NULL;
    }

    q->length--;
    free(front);            // 释放“队列节点”，不是树节点
    return res;
}

/* ======================= Level Order Traversal ======================= */

void levelOrderTraversal(TreeNode *root) {
    if (!root) return;

    Queue *q = queue_create();
    if (!q) return;

    queue_push(q, root);

    // 终止条件：队列为空
    while (!queue_empty(q)) {
        TreeNode *cur = queue_pop(q);
        printf("%d ", cur->val);

        if (cur->left)  queue_push(q, cur->left);
        if (cur->right) queue_push(q, cur->right);
    }
    printf("\n");

    queue_destroy(q);
}


int main() {
    
    return 0;
}