/** 顺序表的声明 - 动态存储 */

// 创建 初始化 遍历 增删改查

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    int *data;      // 动态分配的数组
    int length;     // 当前元素个数
    int capacity;   // 当前分配容量
} DynamicSeqList;


DynamicSeqList* create_list(int initial_capacity) {
    if (initial_capacity <= 0 ) initial_capacity = 4;
    DynamicSeqList *list = (DynamicSeqList*) malloc(sizeof(DynamicSeqList) * initial_capacity);
    if (!list) return NULL;
    // 初始化
    list->data = (int*) malloc(sizeof(int) * initial_capacity);
    if (!list->data) {
        free(list);
        return NULL;
    }
    list->length = 0;
    list->capacity = initial_capacity;
    return list;
}

void destroySeqList(DynamicSeqList *list) {
    if (list) {
        free(list->data);
        free(list);
    }
}

bool extand(DynamicSeqList *list, int new_capacity) {
    if (!list || new_capacity <= list->capacity) return false;

    int *new_data = (int*) malloc(sizeof(int) * new_capacity);
    if (!new_data) return false;

    list->data = new_data;
    list->capacity = new_capacity;
    return true;
}

bool append(DynamicSeqList *list, int value) {
    if (!list) return false;

    if (list->length == list->capacity) {
        if (!extand(list, list->capacity * 2)) {
            printf("%s\n", "末尾添加元素时顺序表容量已满,且扩容失败");
        } 
    }

    list->data[list->length-1] = value;
    list->length++;
    return true;
}

bool insert(DynamicSeqList *list, int index, int value) {
    if (!list || (index < 0 || index >= list->length)) return false;
    
    if (list->length == list->capacity) {
        if (!extand(list, list->capacity * 2)) {
            printf("%s\n", "插入元素时顺序表容量已满,且扩容失败");
            return false;
        }
    }

    for (int i = list->length; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    list->length++;
    return true;
}

bool delete_at(DynamicSeqList *list, int index, int *deleted_value) {
    if (!list || (index < 0 || index >= list->length) || !deleted_value) return false;

    *deleted_value = list->data[index];
    for (int i = index; i < list->length - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    
    list->length--;
    return true;
}

bool get(DynamicSeqList *list, int index, int *result) {
    if (!list || !result || (index < 0 || index >= list->length)) return false;
    *result = list->data[index];
    return true;
}


bool set(DynamicSeqList *list, int index, int value) {
    if (!list || (index < 0 || index >= list->length)) return false;
    list->data[index] = value;
    return true;
}

void print_list(DynamicSeqList *list) {
    if (!list) {
        printf("%s\n", "The DynamicSeqList is NULL.");
        return;
    }
    for (int i = 0; i < list->length; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}


int main() {
    
}