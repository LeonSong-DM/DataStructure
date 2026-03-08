/**
 * @Author: leonsong
 * @Date:   2026-03-05 16:34:46
 * @Last Modified by:   leonsong
 * @Last Modified time: 2026-03-08 16:10:46
 * @Function: 二叉树的实现<链式存储>
 */

 
#include <stdio.h>
#include <stdlib.h>

// TODO 二叉树结点结构体
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;




// TODO 存储二叉树结点的结点
typedef struct QNode {
    TreeNode *node;
    struct QNode *next;
} QNode;

// TODO 操作队列
typedef struct Queue {
    QNode *head;     // 头指针
    QNode *tail;     // 尾指针
    int length;         // 队列长度
} Queue;



/**
 * @brief  创建并初始化一个二叉树结点
 *
 * 为新结点分配内存，并初始化其成员：
 * - val  设置为给定值
 * - left 和 right 初始化为 NULL
 *
 * @param val  结点存储的数据值
 * @return TreeNode* 
 *         - 成功：返回新创建的结点指针
 *         - 失败：返回 NULL（内存分配失败）
 */
TreeNode* initTreeNode(int val) {
    TreeNode *node = (TreeNode*) malloc(sizeof(TreeNode));
    if (!node) return NULL;
    
    node->val = val;
    node->left = NULL;
    node->right = NULL;

    return node;
}





/**
 * @brief: 初始化队列
 */
Queue* initQueue(void) {
    Queue *queue = (Queue*) malloc(sizeof(Queue));
    if (!queue) return NULL;
    
    queue->head = NULL;
    queue->tail = NULL;
    queue->length = 0;

    return queue;
}

void destroyQueue(Queue *queue) {
    if (!queue) return;

    QNode *cur_node = queue->head;

    while (cur_node) {
        QNode *next = cur_node->next;
        free(cur_node);
        cur_node = next;
    }

    free(queue);
}

/**
 * @brief: 判断队列是否为空 
 * 
 * @return: [0:非空, 1:空]
 */
int queueEmpty(Queue *queue) {
    return (!queue || queue->length == 0) ? 1:0;
}

// TODO: 入队
int push(Queue *queue, TreeNode* node) {
    if (!queue || !node) return 0;

    QNode *q_node = (QNode*) malloc(sizeof(QNode));
    if (!q_node) return 0;
    
    q_node->node = node;
    q_node->next = NULL;

    if (queue->length == 0) {
         queue->head = q_node;
    } else {
        queue->tail->next = q_node;
        
    }
    
    queue->tail = q_node;
    queue->length++;

    return 1;
}

// TODO: 出队
TreeNode* pop(Queue *queue) {
    if (!queue || queue->length == 0) return NULL;

    QNode* q_node = queue->head;
    TreeNode *t_node = q_node->node;

    if (queue->length == 1) {
        queue->tail = NULL;
    } 
    
    queue->head = queue->head->next;
    queue->length--;
    
    // printf("| %d |出队\n", t_node->val);
    return t_node;
}


/**
 * @brief: 借助链式队列对二叉树进行层序遍历并输出结果
 * 
 * @param root_node: 二叉树的根节点
 */
void levelOrderTraversal(TreeNode *root_node) {
    if (!root_node) return;
    
    // TODO 初始化队列
    Queue *queue = initQueue();
    push(queue, root_node);

    TreeNode *t_node = NULL;
    
    while (!queueEmpty(queue)) {
        t_node = pop(queue);
        printf("%d ", t_node->val);

        if (t_node->left) push(queue, t_node->left);
        if (t_node->right) push(queue, t_node->right);        
    }
    printf("\n");

    destroyQueue(queue);
}


/**
 * @brief: 递归思想实现的二叉树前序遍历
 * 
 * @param root_node: 二叉树的根节点
 */
void firstOrderTraversal(TreeNode *root_node) {
    if (!root_node) return;

    printf("%d ", root_node->val);
    if (root_node->left) firstOrderTraversal(root_node->left);
    if (root_node->right) firstOrderTraversal(root_node->right);
}


/**
 * @brief: 递归思想实现的二叉树中序遍历
 * 
 * @param root_node: 二叉树的根节点
 */
void inOrderTraversal(TreeNode *root_node) {
    if (!root_node) return;
    
    if (root_node->left) inOrderTraversal(root_node->left);
    printf("%d ", root_node->val);
    if (root_node->right) inOrderTraversal(root_node->right);
    
}


/**
 * @brief: 递归思想实现的二叉树后序遍历
 * 
 * @param root_node: 二叉树的根节点
 */
void postOrderTraversal(TreeNode *root_node) {
    if (!root_node) return;

    if (root_node->left) postOrderTraversal(root_node->left);
    if (root_node->right) postOrderTraversal(root_node->right);
    printf("%d ", root_node->val);
    
}


int main(void) {
    TreeNode *n1  = initTreeNode(1);
    TreeNode *n2  = initTreeNode(2);
    TreeNode *n3  = initTreeNode(3);
    TreeNode *n4  = initTreeNode(4);
    TreeNode *n5  = initTreeNode(5);
    TreeNode *n6  = initTreeNode(6);
    TreeNode *n7  = initTreeNode(7);
    TreeNode *n8  = initTreeNode(8);
    TreeNode *n9  = initTreeNode(9);
    TreeNode *n10 = initTreeNode(10);
    TreeNode *n11 = initTreeNode(11);
    TreeNode *n12 = initTreeNode(12);
    TreeNode *n13 = initTreeNode(13);
    TreeNode *n14 = initTreeNode(14);
    TreeNode *n15 = initTreeNode(15);
    TreeNode *n16 = initTreeNode(16);
    TreeNode *n17 = initTreeNode(17);
    TreeNode *n18 = initTreeNode(18);
    TreeNode *n19 = initTreeNode(19);
    TreeNode *n20 = initTreeNode(20);

    /* 建立二叉树关系 */

    n1->left = n2;
    n1->right = n3;

    n2->left = n4;
    n2->right = n5;

    n3->left = n6;
    n3->right = n7;

    n4->left = n8;
    n4->right = n9;

    n5->left = n10;
    n5->right = n11;

    n6->left = n12;
    n6->right = n13;

    n7->left = n14;
    n7->right = n15;

    n8->left = n16;
    n8->right = n17;

    n9->left = n18;
    n9->right = n19;

    n10->left = n20;

    printf("层次遍历: ");
    levelOrderTraversal(n1);

    printf("前序遍历: ");
    firstOrderTraversal(n1);
    printf("\n");

    printf("中序遍历: ");
    inOrderTraversal(n1);
    printf("\n");

    printf("后续遍历: ");
    postOrderTraversal(n1);
    printf("\n");

    return 0;
}
