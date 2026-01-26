/** 顺序表的声明 - 静态存储 */
// 创建 初始化 遍历 增删改查

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXLENGTH 10

typedef struct {
    int arr[MAXLENGTH];
    int length;
} SequenceList;

/* 添加元素 */
bool add(SequenceList *sl, int value) {
    if (sl == NULL) return false;
    if (sl->length < MAXLENGTH) {
        sl->arr[sl->length] = value;
        sl->length++;
        return true;
    } else {
        printf("Value %d Add Failed, The Sequence List in full.\n", value);
        return false;
    }
}

/* 访问元素 */
bool access(SequenceList *sl, int index, int *result) {
    if (sl == NULL || result == NULL) return false;
    if (index < 0 || index > sl->length - 1) {
        return false;
    }
    *result = sl->arr[index];
    return true;
}

/* 删除元素 */
bool delete(SequenceList *sl, int index, int *result) {
    if (sl == NULL || result == NULL) return false;
    if (index < 0 || index > sl->length - 1) {
        return false;
    }
    *result = sl->arr[index];
    // 注意索循环条件
    for (int i = index; i < sl->length - 1; i++) {
        sl->arr[i] = sl->arr[i+1];
    }
    sl->length--;
    return true;
}

bool insert(SequenceList *sl, int index, int value) {
    if (sl == NULL) return false;
     // 顺序表已满  index不合法
     if (sl->length == MAXLENGTH || (index < 0 || index > sl->length - 1)) {
        return false;
     } else if (index == sl->length){   // 末尾插入
        sl->arr[sl->length] = value;
        return true;
     }
     // 中间插入
     for (int i = sl->length - 1; i >= index; i--) {
        sl->arr[i + 1] = sl->arr[i];
     }
     sl->arr[index] = value;
     sl->length++;
     return true;
}

bool search(SequenceList *sl, int value, int *index) {
    if (sl == NULL || index == NULL) return false;
     for (int i = 0; i < sl->length; i++) {
        if (sl->arr[i] == value) {
            *index = i;
            return true;
        } 
     }
     return false;
}



/* 遍历 */
void output(SequenceList *sequence_list) {
    if (sequence_list == NULL) return;
    if (sequence_list->length == 0) {
        printf("%s\n", "The Sequence List is Empty.");
    } else {
        printf("Length: %d Content: ", sequence_list->length);
        for (int i = 0; i < sequence_list->length; i++) {
            printf("%d ", sequence_list->arr[i]);
        }
        printf("\n");
    }
}

int main() {
    // 创建 & 初始化
    SequenceList sl = {0};
    add(&sl, 10);
    add(&sl, 20);
    add(&sl, 30);
    add(&sl, 40);
    add(&sl, 50);
    add(&sl, 60);
    add(&sl, 70);
    add(&sl, 80);
    add(&sl, 90);
    add(&sl, 100);
    // 超额添加
    add(&sl, 0); 
    // 遍历输出
    output(&sl);

    // 访问指定索引元素
    int val;
    access(&sl, 5, &val);
    printf("The target index value is : %d\n", val);

    // 删除指定索引元素
    int deleted_val;
    delete(&sl, 5, &deleted_val);
    printf("The deleted value is : %d\n", deleted_val);

    // 遍历
    output(&sl);

    // 插入元素
    insert(&sl, 5, 60);
    output(&sl);

    // 查找元素
    int target = 20;
    int target_index;
    search(&sl, target, &target_index);
    printf("target index is: %d\n", target_index);
    return 0;
}

