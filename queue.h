/**
 * 作者: 徐南木
 * 说明: queue是单链表结构
 * 编译器: mingw-w64
 * 时间: 2020/3/13 9:36
 * 详细注解: http://blog.xunanmu.com/2020/03/13/queue.h/
 */
#ifndef TEMPLATE_QUEUE_H
#define TEMPLATE_QUEUE_H

#include "template.h"

#define queue(T) T##queue
#define __queue(T) T##_queue_node

/**************************************************************************/
#define QUEUE_TYPE_SET(T)                                                  \
typedef struct __queue(T) __queue(T);                                      \
struct __queue(T) {                                                        \
    __queue(T) *next;                                                      \
    T data;                                                                \
};                                                                         \
typedef struct queue(T) queue(T);                                          \
struct queue(T) {                                                          \
    size_t (*length)();                                                    \
                                                                           \
    bool (*empty)();                                                       \
                                                                           \
    void (*push)(T data);                                                  \
                                                                           \
    T (*pop)();                                                            \
                                                                           \
    T* (*front)();                                                         \
                                                                           \
    T* (*back)();                                                          \
                                                                           \
    void (*delete)();                                                      \
}                                                                          \
/**************************************************************************/

/***************************************************************************/
#define QUEUE_FUNCTION_BODY(T)                                             \
size_t length_() {                                                         \
    return length;                                                         \
}                                                                          \
                                                                           \
bool empty() {                                                             \
    return length == 0;                                                    \
}                                                                          \
                                                                           \
void push(T data) {                                                        \
    if (!front) {                                                          \
        MALLOC(front, __queue(T), 1);                                      \
        front->data = data;                                                \
        rear = front;                                                      \
        ++length;                                                          \
        return;                                                            \
    }                                                                      \
    __queue(T) *node = NULL;                                               \
    MALLOC(node, __queue(T), 1);                                           \
    node->data = data;                                                     \
    rear->next = node;                                                     \
    rear = node;                                                           \
    ++length;                                                              \
}                                                                          \
                                                                           \
T pop() {                                                                  \
    UNDERFLOW                                                              \
    T temp = front->data;                                                  \
    __queue(T) *node = front->next;                                        \
    free(front);                                                           \
    front = node;                                                          \
    --length;                                                              \
    return temp;                                                           \
}                                                                          \
                                                                           \
T *front_() {                                                              \
    UNDERFLOW                                                              \
    return &front->data;                                                   \
}                                                                          \
                                                                           \
T *back_() {                                                               \
    UNDERFLOW                                                              \
    return &rear->data;                                                    \
}                                                                          \
                                                                           \
void delete() {                                                            \
    __queue(T) *node = NULL;                                               \
    for (; length > 0; --length) {                                         \
        node = front->next;                                                \
        free(front);                                                       \
        front = node;                                                      \
    }                                                                      \
}                                                                          \
/***************************************************************************/
#define QUEUE_FUNTION_assignmen                                            \
    this.length = length_;                                                 \
    this.empty = empty;                                                    \
    this.push = push;                                                      \
    this.pop = pop;                                                        \
    this.front = front_;                                                   \
    this.back = back_;                                                     \
    this.delete = delete;                                                  \
/**************************************************************************/
/**************************************************************************/
#define new_queue(T)                                                       \
({                                                                         \
    size_t length = 0;                                                     \
    __queue(T) *front = NULL;                                              \
    __queue(T) *rear = NULL;                                               \
    queue(T) this;                                                         \
    QUEUE_FUNCTION_BODY(T)                                                 \
    QUEUE_FUNTION_assignmen                                                \
    this;                                                                  \
})                                                                         \
/**************************************************************************/
#endif //TEMPLATE_QUEUE_H
