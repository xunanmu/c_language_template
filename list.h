/**
 * 作者: 徐南木
 * 说明: list是带表头的双向循环链表
 * 编译器: mingw-w64
 * 时间: 2020/3/13 9:40
 * 详细注解: http://blog.xunanmu.com/2020/03/13/list.h/
 */

#ifndef TEMPLATE_LIST_H
#define TEMPLATE_LIST_H

#include "template.h"
typedef struct twoNodePtrVoid twoNodePtrVoid;
struct twoNodePtrVoid {
    twoNodePtrVoid *prev;
    twoNodePtrVoid *next;
};
#define prev(iteration) ({iteration= (typeof(iteration)) ((((twoNodePtrVoid *) iteration) - 1)->prev+1);iteration;})
#define next(iteration) ({iteration= (typeof(iteration)) ((((twoNodePtrVoid *) iteration) - 1)->next+1);iteration;})
#define NODE(iteration) (((twoNodePtrVoid *) iteration) - 1)
#define _list(T) list(T)
#define list(T) T##_list
#define __list(T) T##_list_node

/***********************************************************************************/
#define LIST_TYPE_SET(T)                                                            \
typedef struct __list(T) __list(T);                                                 \
struct __list(T) {                                                                  \
    struct __list(T) *prev;                                                         \
    struct __list(T) *next;                                                         \
    T data;                                                                         \
};                                                                                  \
                                                                                    \
typedef struct list(T) list(T);                                                     \
typedef struct list(T)  list(T);                                                    \
struct list(T)                                                                      \
{                                                                                   \
    size_t (*length)();                                                             \
    bool (*empty)();                                                                \
    /*在头部添加元素*/                                                              \
    bool (*push_front)(T data);                                                     \
    /*在尾部添加元素*/                                                              \
    bool (*push_back)(T data);                                                      \
    /*指定位置添加元素*/                                                            \
    bool (*push_at)(T data, int index);                                             \
    /*删除并返回头部的元素*/                                                        \
    T (*pop_front)();                                                               \
    /*删除并返回尾部的元素*/                                                        \
    T (*pop_back)();                                                                \
    /*删除并返回指定位置的元素*/                                                    \
    T (*pop_at)(int index);                                                         \
    /*返回头部的元素地址*/                                                          \
    T* (*front)();                                                                  \
    /*返回尾部的元素地址*/                                                          \
    T* (*back)();                                                                   \
    /*返回指定位置的元素地址*/                                                      \
    T* (*at)(int index);                                                            \
    /*返回头部的迭代器*/                                                            \
    T *(*begin)();                                                                  \
    /*返回尾部的迭代器*/                                                            \
    T *(*end)();                                                                    \
    /*删除此迭代器内容,返回是下一个元素的迭代器*/                                   \
    T *(*erase)(T *iterator);                                                       \
    /*在此迭代器前插入元素,返回是插入元素的迭代器*/                                 \
    T *(*insert)(T *iterator, T data);                                              \
    /*默认比较函数*/                                                                \
    int (*cmp)(const void *data, const void* temp);                                 \
    list(T) (*setcmp)(int (*cmp)(const void *data, const void* temp));              \
    /*返回此元素的第一个索引*/                                                      \
    int (*indexOf)(T data);                                                         \
    /*返回此元素的最后一个索引*/                                                    \
    int (*lastIndexOf)(T data);                                                     \
    /*删除指定元素*/                                                                \
    list(T) (*remove)(T data);                                                      \
    /*遍历所有元素*/                                                                \
    list(T) (*traversal)(void (*output)(T data));                                   \
    /*默认升序排序,设置cmp指定排序*/                                                \
    list(T) (*sort)();                                                              \
    /*反转链表*/                                                                    \
    list(T) (*reverse)();                                                           \
    /*删除所有内存*/                                                                \
    list(T) (*delete)();                                                            \
}                                                                                   \
/************************************************************************************/
#define LIST_FUNCTION_BODY(T)                                                       \
size_t length_() {                                                                  \
    return length;                                                                  \
}                                                                                   \
                                                                                    \
bool empty() {                                                                      \
    return length == 0;                                                             \
}                                                                                   \
                                                                                    \
bool push_front(T data) {                                                           \
    IS_HEAD_NULL(T)                                                                 \
    __list(T) *node = NULL;                                                         \
    MALLOC(node, __list(T), 1);                                                     \
    node->data = data;                                                              \
    node->next = head->next;                                                        \
    node->prev = head;                                                              \
    head->next->prev = node;                                                        \
    head->next = node;                                                              \
    ++length;                                                                       \
    return true;                                                                    \
}                                                                                   \
                                                                                    \
bool push_back(T data) {                                                            \
    IS_HEAD_NULL(T)                                                                 \
    __list(T) *node = NULL;                                                         \
    MALLOC(node, __list(T), 1);                                                     \
    node->data = data;                                                              \
    node->next = head;                                                              \
    node->prev = head->prev;                                                        \
    head->prev->next = node;                                                        \
    head->prev = node;                                                              \
    ++length;                                                                       \
    return true;                                                                    \
}                                                                                   \
                                                                                    \
bool push_at(T data, int index) {                                                   \
    IS_HEAD_NULL(T)                                                                 \
    if (index < 0 && index > length)                                                \
        return false;                                                               \
    __list(T) *p = head->next;                                                      \
    for (int i = 0; p != head && i < index; ++i, p = p->next);                      \
    __list(T) *node = NULL;                                                         \
    MALLOC(node, __list(T), 1);                                                     \
    node->data = data;                                                              \
    node->next = p;                                                                 \
    node->prev = p->prev;                                                           \
    p->prev->next = node;                                                           \
    p->prev = node;                                                                 \
    ++length;                                                                       \
    return true;                                                                    \
}                                                                                   \
                                                                                    \
T pop_front() {                                                                     \
    UNDERFLOW                                                                       \
    __list(T) *node = head->next;                                                   \
    T temp = node->data;                                                            \
    node->next->prev = node->prev;                                                  \
    node->prev->next = node->next;                                                  \
    free(node);                                                                     \
    --length;                                                                       \
    return temp;                                                                    \
}                                                                                   \
                                                                                    \
T pop_back() {                                                                      \
    UNDERFLOW                                                                       \
    __list(T) *node = head->prev;                                                   \
    T temp = node->data;                                                            \
    node->next->prev = node->prev;                                                  \
    node->prev->next = node->next;                                                  \
    free(node);                                                                     \
    --length;                                                                       \
    return temp;                                                                    \
}                                                                                   \
                                                                                    \
T pop_at(int index) {                                                               \
    UNDERFLOW                                                                       \
    if (index < 0 && index > length)                                                \
        puts("\npop_at():UNDERFLOW!!!"), exit(0);                                   \
    __list(T) *node = head->next;                                                   \
    for (int i = 0; node != head && i < index; ++i, node = node->next);             \
    T temp = node->data;                                                            \
    node->next->prev = node->prev;                                                  \
    node->prev->next = node->next;                                                  \
    free(node);                                                                     \
    --length;                                                                       \
    return temp;                                                                    \
}                                                                                   \
                                                                                    \
T *front() {                                                                        \
    UNDERFLOW                                                                       \
    return &head->next->data;                                                       \
}                                                                                   \
                                                                                    \
T *back() {                                                                         \
    UNDERFLOW                                                                       \
    return &head->prev->data;                                                       \
}                                                                                   \
                                                                                    \
T *at(int index) {                                                                  \
    UNDERFLOW                                                                       \
    if (index < 0 && index > length)                                                \
        puts("\nat():UNDERFLOW!!!"), exit(0);                                       \
    __list(T) *node = head->next;                                                   \
    for (int i = 0; node != head && i < index; ++i, node = node->next);             \
    return &node->data;                                                             \
}                                                                                   \
                                                                                    \
T *end() {                                                                          \
    return &head->data;                                                             \
}                                                                                   \
                                                                                    \
T *begin() {                                                                        \
    return &head->next->data;                                                       \
}                                                                                   \
                                                                                    \
T *erase(T *it) {                                                                   \
    T *temp = &((__list(T) *) NODE(it))->next->data;                                \
    /*T *temp = next(it);                                                           \
      prev(it);*/                                                                   \
    NODE(it)->prev->next = NODE(it)->next;                                          \
    NODE(it)->next->prev = NODE(it)->prev;                                          \
    free(NODE(it));                                                                 \
    --length;                                                                       \
    return temp;                                                                    \
}                                                                                   \
                                                                                    \
T *insert(T *it, T data) {                                                          \
    __list(T) *node = NULL;                                                         \
    MALLOC(node, __list(T), 1);                                                     \
    node->data = data;                                                              \
    ((twoNodePtrVoid *) node)->prev = NODE(it)->prev;                               \
    ((twoNodePtrVoid *) node)->next = NODE(it);                                     \
    NODE(it)->prev->next = ((twoNodePtrVoid *) node);                               \
    NODE(it)->prev = ((twoNodePtrVoid *) node);                                     \
    ++length;                                                                       \
    return &node->data;                                                             \
}                                                                                   \
                                                                                    \
int cmp(const void *data, const void *temp) {                                       \
    return memcmp(data, temp, sizeof(T));                                           \
}                                                                                   \
                                                                                    \
list(T) setcmp(int cmp(const void *data, const void *temp)) {                       \
    this.cmp = cmp;                                                                 \
    return this;                                                                    \
}                                                                                   \
                                                                                    \
int indexOf(T data) {                                                               \
    int i = 0;                                                                      \
    __list(T) *node = head->next;                                                   \
    while (node != head) {                                                          \
        if (this.cmp(&data, &node->data) == 0)                                      \
            return i;                                                               \
        node = node->prev;                                                          \
        ++i;                                                                        \
    }                                                                               \
    return -1;                                                                      \
}                                                                                   \
                                                                                    \
int lastIndexOf(T data) {                                                           \
    int i = 0;                                                                      \
    __list(T) *node = head->prev;                                                   \
    while (node != head) {                                                          \
        if (this.cmp(&data, &node->data) == 0)                                      \
            return (int) length - i - 1;                                            \
        node = node->prev;                                                          \
        ++i;                                                                        \
    }                                                                               \
    return -1;                                                                      \
}                                                                                   \
                                                                                    \
list(T) remove_(T data) {                                                           \
    __list(T) *node = head->next, *p = NULL;                                        \
    while (node != head) {                                                          \
        if (this.cmp(&data, &node->data) == 0) {                                    \
            p = node->next;                                                         \
            erase(&node->data);                                                     \
            node = p;                                                               \
        } else                                                                      \
            node = node->next;                                                      \
    }                                                                               \
    return this;                                                                    \
}                                                                                   \
                                                                                    \
list(T) traversal(void output(T data)) {                                            \
    if(empty())                                                                     \
        return this;                                                                \
    T *it = &head->data;                                                            \
    while (next(it) != end())                                                       \
        output(*it);                                                                \
    puts("");                                                                       \
    return this;                                                                    \
}                                                                                   \
                                                                                    \
list(T) reverse() {                                                                 \
    __list(T) *front = head->prev, *back = head->next;                              \
    while (front != back && front->next != back) {                                  \
        swap(front->data, back->data);                                              \
        front = front->prev;                                                        \
        back = back->next;                                                          \
    }                                                                               \
    return this;                                                                    \
}                                                                                   \
                                                                                    \
list(T) delete() {                                                                  \
    while (!empty())                                                                \
        pop_back();                                                                 \
    free(head);                                                                     \
    head = NULL;                                                                    \
    return this;                                                                    \
}                                                                                   \
                                                                                    \
/**                                                                                 \
 * 本来想用归并的感觉效率和快排一样,然后想了想用Java那种复制数据到                  \
 * 数组,然后直接套用glib的qsort(),然后想了想这个空间复制度连最好情况都需要n+logn                                 \
 * 最坏情况可能是2n;最后我还是用快排算了,这个可能最坏情况就是10亿数爆栈                                            \
 * */                                                                            \
T *partition(T *front, T *back) {                                                   \
    T *first = front;                                                               \
    T piovt = *front;                                                               \
    while (front != back) {                                                         \
        /*this.cmp(&piovt)>=0;*/                                                    \
        while (front != back && this.cmp(back, &piovt) >= 0)                        \
            prev(back);                                                             \
        while (front != back && this.cmp(&piovt, front) >= 0)                       \
            next(front);                                                            \
        if (front != back)                                                          \
            swap(*front, *back);                                                    \
    }                                                                               \
    swap(*front, *first);                                                           \
    return front;                                                                   \
}                                                                                   \
                                                                                    \
void quick_sort(T *start, T *end) {                                                 \
    if (start == end)                                                               \
        return;                                                                     \
    T *index = partition(start, end);                                               \
    if (start != index)                                                             \
        quick_sort(start, prev(index));                                             \
    if (end != index)                                                               \
        quick_sort(next(index), end);                                               \
}                                                                                   \
                                                                                    \
list(T) sort() {                                                                    \
    quick_sort(begin(), &head->prev->data);                                         \
    return this;                                                                    \
}                                                                                   \
/************************************************************************************/
#define LIST_FUNTION_assignmen                                                      \
    this.length = length_;                                                          \
    this.empty = empty;                                                             \
    this.push_front = push_front;                                                   \
    this.push_back = push_back;                                                     \
    this.push_at = push_at;                                                         \
    this.pop_front = pop_front;                                                     \
    this.pop_back = pop_back;                                                       \
    this.pop_at = pop_at;                                                           \
    this.front = front;                                                             \
    this.back = back;                                                               \
    this.at = at;                                                                   \
    this.begin = begin;                                                             \
    this.end = end;                                                                 \
    this.erase = erase;                                                             \
    this.insert = insert;                                                           \
    this.cmp = cmp;                                                                 \
    this.setcmp = setcmp;                                                           \
    this.indexOf = indexOf;                                                         \
    this.lastIndexOf = lastIndexOf;                                                 \
    this.remove = remove_;                                                          \
    this.traversal = traversal;                                                     \
    this.sort = sort;                                                               \
    this.reverse = reverse;                                                         \
    this.delete = delete;                                                           \
/***********************************************************************************/
#define new_list(T)                                                                 \
({                                                                                  \
    size_t length = 0;                                                              \
    list(T) this;                                                                   \
    __list(T) *head = NULL;                                                         \
    LIST_FUNCTION_BODY(T)                                                           \
    LIST_FUNTION_assignmen                                                          \
    this;                                                                           \
})                                                                                  \
/***********************************************************************************/
/**************************************************/
#define IS_HEAD_NULL(T)                            \
    if (!head)                                     \
    {                                              \
        MALLOC(head,__list(T),1);                  \
        head->next=  head;                         \
        head->prev= head;                          \
    }                                              \
/***************************************************/
#endif //TEMPLATE_LIST_H
