
/**
 * 作者: 徐南木
 * 说明: stack实现list和array两种容器(默认list)
 * 编译器: mingw-w64
 * 时间: 2020/3/13 9:30
 * 详细注解: http://blog.xunanmu.com/2020/03/13/stack.h/
 */

#ifndef TEMPLATE_STACK_H
#define TEMPLATE_STACK_H

#include "template.h"

#define stack(T) T##_stack
#define __stack(T) T##_stack_node
/**************************************************************************/
#define STACK_TYPE_SET(T)                                                  \
typedef struct __stack(T) __stack(T);                                      \
struct __stack(T) {                                                        \
    __stack(T) *next;                                                      \
    T data;                                                                \
};                                                                         \
                                                                           \
typedef struct stack(T) stack(T);                                          \
struct stack(T) {                                                          \
    size_t (*length)();                                                    \
                                                                           \
    bool (*empty)();                                                       \
                                                                           \
    void (*push)(T data);                                                  \
                                                                           \
    T (*pop)();                                                            \
                                                                           \
    T* (*top)();                                                           \
                                                                           \
    void (*delete)();                                                      \
}                                                                          \
                                                                           \
/**************************************************************************/
#define STACK_LIST_FUNCTION_BODY(T)                                        \
size_t length_() {                                                         \
    return length;                                                         \
}                                                                          \
                                                                           \
bool empty() {                                                             \
    return length == 0;                                                    \
}                                                                          \
                                                                           \
void push(T data) {                                                        \
    __stack(T) *node = NULL;                                               \
    MALLOC(node, __stack(T), 1);                                           \
    node->data = data;                                                     \
    node->next = top;                                                      \
    top = node;                                                            \
    ++length;                                                              \
}                                                                          \
                                                                           \
T pop() {                                                                  \
    UNDERFLOW                                                              \
    T temp = top->data;                                                    \
    __stack(T) *node = top->next;                                          \
    free(top);                                                             \
    top = node;                                                            \
    --length;                                                              \
    return temp;                                                           \
}                                                                          \
                                                                           \
T* top_() {                                                                \
    UNDERFLOW                                                              \
    return &top->data;                                                     \
}                                                                          \
                                                                           \
void delete() {                                                            \
    __stack(T) *node;                                                      \
    while (top) {                                                          \
        node = top->next;                                                  \
        free(top);                                                         \
        top = node;                                                        \
    }                                                                      \
    length=0;                                                              \
}                                                                          \
/**************************************************************************/
#define STACK_FUNCTION_assignmen                                           \
    this.length = length_;                                                 \
    this.empty = empty;                                                    \
    this.push = push;                                                      \
    this.pop = pop;                                                        \
    this.top = top_;                                                       \
    this.delete = delete;                                                  \
/**************************************************************************/
/**************************************************************************/
#define STACK_Array_FUNCTION_BODY(T)                                       \
size_t length_()                                                           \
{                                                                          \
    return length;                                                         \
}                                                                          \
bool empty()                                                               \
{                                                                          \
    return length==0;                                                      \
}                                                                          \
void push(T data)                                                          \
{                                                                          \
    if (maxsize <= length)                                                 \
    {                                                                      \
        if( !REALLOC(top,T,maxsize+size_init))                             \
            exit(0);                                                       \
        maxsize += size_init;                                              \
    }                                                                      \
    top[length++]=data;                                                    \
}                                                                          \
T pop()                                                                    \
{                                                                          \
    UNDERFLOW                                                              \
    return top[--length];                                                  \
}                                                                          \
T* top_()                                                                  \
{                                                                          \
    UNDERFLOW                                                              \
    return &top[length-1];                                                 \
}                                                                          \
void delete()                                                              \
{                                                                          \
    if (!top)                                                              \
    {                                                                      \
        free(top);                                                         \
        top=NULL;                                                          \
        length=maxsize=0;                                                  \
    }                                                                      \
}                                                                          \
/**************************************************************************/
/**************************************************************************/
#define new_stack(T)                                                       \
({                                                                         \
    size_t length = 0;                                                     \
    __stack(T) *top = NULL;                                                \
    stack(T) this;                                                         \
    STACK_LIST_FUNCTION_BODY(T)                                            \
    STACK_FUNCTION_assignmen                                               \
    this;                                                                  \
})                                                                         \
/**************************************************************************/
#define new_stackArray(T)                                                  \
({                                                                         \
    size_t length = 0;                                                     \
    size_t maxsize = 0;                                                    \
    T *top = NULL;                                                         \
    stack(T) this;                                                         \
    STACK_Array_FUNCTION_BODY(T)                                           \
    STACK_FUNCTION_assignmen                                               \
    this;                                                                  \
})                                                                         \
/**************************************************************************/
#endif //TEMPLATE_STACK_H
