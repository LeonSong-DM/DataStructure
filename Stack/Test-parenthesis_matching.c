/* 括号匹配 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    char val;
    struct Node *next;
} Node;

typedef struct {
    Node* top;
    int size;
} LinkedNodeStack;

LinkedNodeStack* initStack() {
    LinkedNodeStack *stack = (LinkedNodeStack*) malloc(sizeof(LinkedNodeStack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

bool push(LinkedNodeStack *stack, char c) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->val = c;
    node->next = stack->top;

    stack->top = node;
    stack->size++;
    return true;
}

bool pop(LinkedNodeStack *stack, char* c) {
    // 判空
    if (stack->size == 0) return false;
    Node *current_top = stack->top;
    *c = current_top->val;

    stack->top = current_top->next;
    stack->size--;
    free(current_top);
    return true;
}

void destroyStack(LinkedNodeStack* stack) {
    assert(stack != NULL);
    Node *current = stack->top;
    while (current)
    {
        Node *node = current;
        current = node->next;
        free(node);
    }
    free(stack);
}


bool isValidBrackets(const char* s) {
    LinkedNodeStack *stack = initStack();
    // 计算长度
    int len = 0;
    while (s[len] != '\0') {
        char c = s[len];
        if (c == '(' || c == '{' || c == '[') {
            push(stack, c);
        } else if (c == ')' || c == '}' || c == ']') {
            char c_;    // 出栈元素
            bool flag = pop(stack, &c_);

            // 栈为空
            if ( !flag ) return false;

            // 出栈比对
            if (c == ')') {
                if (c_ != '(') return false;
            } else if (c == '}') {
                if (c_ != '{') return false;
            } else if (c == ']') {
                if (c_ != '[') return false;
            }
        }
        len++;
    }
    // 栈中有剩余
    if (stack->size !=0 ) return false;
    destroyStack(stack);
    return true;
}

typedef struct {
    const char* input;
    bool expected;
    const char* note;
} TestCase;



int main() {
    TestCase tests[] = {
        /* 空/基础 */
        {"", true, "empty string"},
        {" ", true, "only spaces (if ignoring non-brackets)"},
        {"(", false, "single ("},
        {")", false, "single )"},
        {"[]", true, "simple []"},
        {"{}", true, "simple {}"},
        {"()", true, "simple ()"},

        /* 串联 */
        {"()[]{}", true, "concat pairs"},
        {"([]){}", true, "nested + concat"},
        {"(((())))", true, "deep nesting"},
        {"[({})]", true, "mixed nesting"},

        /* 经典错误 */
        {"(]", false, "mismatch type"},
        {"([)]", false, "crossing mismatch"},
        {"((()", false, "missing closing"},
        {"())", false, "extra closing"},
        {"(()))", false, "extra closing after valid prefix"},
        {")(", false, "starts with closing"},
        {"{[}", false, "early close mismatch"},
        {"{[]})", false, "extra closing at end"},

        /* 含其它字符：看你实现是否“忽略非括号字符” */
        {"a(b)c", true, "letters inside"},
        {"a(b]c", false, "letters + mismatch"},
        // {"if (a[0] == '{') { return; }", true, "code-like string"},
        {"func(x[2}])", false, "code-like mismatch"},

        /* 边界：只有开括号很多 */
        {"(((((((((((", false, "many openings"},
        {")))))))))))", false, "many closings"},

        /* 更复杂混合 */
        {"{[()()]()}", true, "LeetCode classic valid"},
        {"{[(])}", false, "LeetCode classic invalid"},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int pass = 0;

    for (int i = 0; i < n; i++) {
        bool got = isValidBrackets(tests[i].input);
        bool ok = (got == tests[i].expected);
        printf("[%02d] %s | input: \"%s\" | expected=%d got=%d | %s\n",
               i + 1, ok ? "PASS" : "FAIL",
               tests[i].input, tests[i].expected, got, tests[i].note);
        pass += ok;
    }

    printf("\nSummary: %d/%d passed.\n", pass, n);
    return 0;
}

