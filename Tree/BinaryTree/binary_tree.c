/**
 * @Author: leonsong
 * @Date:   2026-03-03 16:36:37
 * @Last Modified by:   leonsong
 * @Last Modified time: 2026-03-03 21:46:16
 * @Function: 实现二叉树
 */
#include <stdio.h>
#include <stdlib.h>

// TODO 声明结点结构体
typedef struct TreeNode {
    int val;                    // 结点值
    int height;                 // 结点高度
    struct TreeNode *left;      // 左孩子结点指针
    struct TreeNode *right;     // 右孩子结点指针
} TreeNode;

// TODO 结点结构体的构造函数
TreeNode* inintTreeNode(int val) {
    // 分配内存空间
    TreeNode *node = (TreeNode*) malloc(sizeof(TreeNode));
    if (!node) return NULL;

    // 初始化
    node -> val = val;
    node -> height = 0;
    node -> left = NULL;
    node -> right = NULL;

    return node;
}


int main() {
    // 初始化结点
    TreeNode *n1 = initTreeNode(1);
    TreeNode *n2 = initTreeNode(2);
    TreeNode *n3 = initTreeNode(3);
    TreeNode *n4 = initTreeNode(4);
    TreeNode *n5 = initTreeNode(5);

    // 构建引用
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;
    
    return 0;
}
