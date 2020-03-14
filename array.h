/**
 * 作者: 徐南木
 * 说明: array是弹性动态管理,空元素太多会自动清除一部分空间
 * 编译器: mingw-w64
 * 时间: 2020/3/13 9:33
 * 详细注解: http://blog.xunanmu.com/2020/03/13/array.h/
 */

#ifndef TEMPLATE_ARRAY_H
#define TEMPLATE_ARRAY_H

#include "template.h"

#define array(T) T##_array

/************************************************************************************/
#define ARRAY_TYPE_SET(T)                                                           \
typedef struct array(T) array(T);                                                   \
struct array(T) {                                                                   \
    /*返回变量类型名*/                                                              \
    char *(*type)();                                                                \
    /*返回元素个数*/                                                                \
    size_t (*length)();                                                             \
    /*返回最大容量*/                                                                \
    size_t (*maxsize)();                                                            \
    /*空返回真*/                                                                    \
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
    /*返回此迭代器的索引*/                                                          \
    int (*index)(T *iterator);                                                      \
    /*默认比较函数*/                                                                \
    int (*cmp)(const void *data, const void* temp);                                 \
    array(T) (*setcmp)(int (*cmp)(const void *data, const void* temp));             \
    /*返回此元素的第一个索引*/                                                      \
    int (*indexOf)(T data);                                                         \
    /*返回此元素的最后一个索引*/                                                    \
    int (*lastIndexOf)(T data);                                                     \
    /*删除指定元素*/                                                                \
    array(T) (*remove)(T data);                                                     \
    /*遍历所有元素*/                                                                \
    array(T) (*traversal)(void (*output)(T data));                                  \
    /*n是当前数组元素个数,max_n当前数组容量,false是静态,true是动态*/                \
    array(T) (*setArray)(T *arr, int n, int max_n, bool set);                       \
    /*重置数组大小*/                                                                \
    array(T) (*resize)(int size);                                                   \
    /*默认升序排序,设置cmp指定排序*/                                                \
    array(T) (*sort)();                                                             \
    /*反转数组*/                                                                    \
    array(T) (*reverse)();                                                          \
    /*清空,但不删除内存*/                                                           \
    array(T) (*clear)();                                                            \
    /*删除所有内存*/                                                                \
    array(T) (*delete)();                                                           \
}                                                                                   \
                                                                                    \
/**********************************************************************************/
#define STATIC_ARRAY_FUNCTION_BODY(T)                                              \
bool push_front(T data) {                                                          \
    if (maxsize == length) return false;                                           \
    memmove(array + 1, array, length++);                                           \
    array[0] = data;                                                               \
    printf("%d", __LINE__);                                                        \
    return true;                                                                   \
}                                                                                  \
                                                                                   \
bool push_back(T data) {                                                           \
    if (maxsize == length) return false;                                           \
    array[length++] = data;                                                        \
    return true;                                                                   \
}                                                                                  \
                                                                                   \
bool push_at(T data, int index) {                                                  \
    if (maxsize == length) return false;                                           \
    if (index < 0 && index > length)                                               \
        return false;                                                              \
    memmove(&array[index + 1], &array[index], length - index);                     \
    array[index] = data;                                                           \
    length++;                                                                      \
    return true;                                                                   \
}                                                                                  \
                                                                                   \
T pop_front() {                                                                    \
    UNDERFLOW                                                                      \
    T temp = array[0];                                                             \
    memmove(array, array + 1, --length);                                           \
    return temp;                                                                   \
}                                                                                  \
                                                                                   \
T pop_back() {                                                                     \
    UNDERFLOW                                                                      \
    return array[--length];                                                        \
}                                                                                  \
                                                                                   \
T pop_at(int index) {                                                              \
    UNDERFLOW                                                                      \
    if (index < 0 && index >= length)                                              \
    {                                                                              \
        printf("error:%s文件内%s函数产生下溢操作!",__FILE__,__func__);             \
        exit(0);                                                                   \
    }                                                                              \
    T temp = array[index];                                                         \
    memmove(array + index + 1, array + index, --length - index);                   \
    return temp;                                                                   \
}                                                                                  \
/***********************************************************************************/
#define ARRAY_FUNCTION_BODY(T)                                                      \
char *type() {                                                                      \
    return tostring(array(T));                                                      \
}                                                                                   \
                                                                                    \
size_t length_() {                                                                  \
    return length;                                                                  \
}                                                                                   \
                                                                                    \
size_t maxszie_() {                                                                 \
    return maxsize;                                                                 \
}                                                                                   \
                                                                                    \
bool empty() {                                                                      \
    return length == 0;                                                             \
}                                                                                   \
                                                                                    \
bool push_front(T data) {                                                           \
    auto_memory_add(T)                                                              \
    memmove(array + 1, array, length++);                                            \
    array[0] = data;                                                                \
    printf("%d", __LINE__);                                                         \
    return true;                                                                    \
}                                                                                   \
                                                                                    \
bool push_back(T data) {                                                            \
    auto_memory_add(T)                                                              \
    array[length++] = data;                                                         \
    return true;                                                                    \
}                                                                                   \
                                                                                    \
bool push_at(T data, int index) {                                                   \
    auto_memory_add(T)                                                              \
    if (index < 0 && index > length)                                                \
        return false;                                                               \
    memmove(&array[index + 1], &array[index], length - index);                      \
    array[index] = data;                                                            \
    length++;                                                                       \
    return true;                                                                    \
}                                                                                   \
                                                                                    \
T pop_front() {                                                                     \
    auto_memory_sub(T)                                                              \
    UNDERFLOW                                                                       \
    T temp = array[0];                                                              \
    memmove(array, array + 1, --length);                                            \
    return temp;                                                                    \
}                                                                                   \
                                                                                    \
T pop_back() {                                                                      \
    auto_memory_sub(T)                                                              \
    UNDERFLOW                                                                       \
    return array[--length];                                                         \
}                                                                                   \
                                                                                    \
T pop_at(int index) {                                                               \
    auto_memory_sub(T)                                                              \
    UNDERFLOW                                                                       \
    if (index < 0 && index >= length) {                                             \
        printf("error:%s文件内%s函数产生下溢操作!", __FILE__, __func__);            \
        exit(0);                                                                    \
    }                                                                               \
    T temp = array[index];                                                          \
    memmove(array + index + 1, array + index, --length - index);                    \
    return temp;                                                                    \
}                                                                                   \
                                                                                    \
T* front() {                                                                        \
    UNDERFLOW                                                                       \
    return &array[0];                                                               \
}                                                                                   \
                                                                                    \
T* back() {                                                                         \
    UNDERFLOW                                                                       \
    return &array[length - 1];                                                      \
}                                                                                   \
                                                                                    \
T* at(int index) {                                                                  \
    if (index < 0 && index >= length) {                                             \
        printf("error:%s文件内%s函数访问异常!", __FILE__, __func__);                \
        exit(0);                                                                    \
    }                                                                               \
    return &array[index];                                                           \
}                                                                                   \
                                                                                    \
T *begin() {                                                                        \
    return array;                                                                   \
}                                                                                   \
                                                                                    \
T *end() {                                                                          \
    return array + length;                                                          \
}                                                                                   \
                                                                                    \
T *erase(T *it) {                                                                   \
    memmove(it, it + 1, --length - (it - array));                                   \
    return it;                                                                      \
}                                                                                   \
                                                                                    \
T *insert(T *it, T data) {                                                          \
    /*                                                                              \
    if (maxsize <= length){                                                         \
        if(! REALLOC(array,T,maxsize+size_init))                                    \
        {                                                                           \
            printf("error:内存异常\n!");                                            \
            exit(0);                                                                \
        }                                                                           \
        maxsize += size_init;                                                       \
    }                                                                               \
    */                                                                              \
    /*为了不让it失效,采用静态方式*/                                                 \
    if (maxsize <= length) {                                                        \
        printf("error:%s文件内%s函数产生上溢操作!", __FILE__, __func__);            \
        exit(0);                                                                    \
    }                                                                               \
    memmove(it + 1, it, length - (it - array));                                     \
    *it = data;                                                                     \
    ++length;                                                                       \
    return it;                                                                      \
}                                                                                   \
                                                                                    \
int cmp(const void *data, const void* temp){                                        \
    return memcmp(data,temp, sizeof(T));                                            \
}                                                                                   \
                                                                                    \
int index_(T *it) {                                                                 \
    return it-array;                                                                \
}                                                                                   \
                                                                                    \
int indexOf(T data) {                                                               \
    for (int i = 0; i < length; ++i)                                                \
    {                                                                               \
        if (this.cmp(&data,array+i)==0)                                             \
            return i;                                                               \
    }                                                                               \
    return -1;                                                                      \
}                                                                                   \
                                                                                    \
int lastIndexOf(T data) {                                                           \
    for (int i = length-1; i >= 0; --i)                                             \
    {                                                                               \
        if (this.cmp(&data,array+i)==0)                                             \
            return i;                                                               \
    }                                                                               \
    return -1;                                                                       \
}                                                                                   \
                                                                                    \
array(T) setcmp(int (*cmp)(const void *data, const void* temp)) {                   \
    this.cmp=cmp;                                                                   \
    return this;                                                                    \
}                                                                                   \
                                                                                    \
array(T) remove_(T data) {                                                          \
    for (int i = 0; i < length; ++i) {                                              \
        if (this.cmp(&data,array+i)==0)                                             \
            this.pop_at(i);                                                         \
    }                                                                               \
    return this;                                                                    \
}                                                                                   \
                                                                                    \
array(T) traversal(void (*output)(T data))                                          \
{                                                                                   \
    for (int i = 0; i < length; ++i) {                                              \
        output(array[i]);                                                           \
    }                                                                               \
    puts("");                                                                       \
    return this;                                                                    \
}                                                                                   \
                                                                                    \
array(T) sort()                                                                     \
{                                                                                   \
    qsort(array,length, sizeof(T),this.cmp);                                        \
    return this;                                                                    \
}                                                                                   \
                                                                                    \
array(T) reverse()                                                                  \
{                                                                                   \
    int l=-1,r=length;                                                              \
    while (++l<--r)                                                                 \
        swap(array[l],array[r]);                                                    \
    return this;                                                                    \
}                                                                                   \
                                                                                    \
array(T) resize(int size)                                                           \
{                                                                                   \
    REALLOC(array,T,size);                                                          \
    maxsize=size;                                                                   \
    maxsize>=length?:(length=maxsize);                                              \
    return this;                                                                    \
}                                                                                   \
                                                                                    \
array(T) clear()                                                                    \
{                                                                                   \
    length=0;                                                                       \
    return this;                                                                    \
}                                                                                   \
                                                                                    \
array(T) delete(){                                                                  \
    free(array);                                                                    \
    length=maxsize=0;                                                               \
    return this;                                                                    \
}                                                                                   \
                                                                                    \
array(T) setArray(T arrays[],int n,int max_n,bool flag)                             \
{                                                                                   \
    array=arrays;                                                                   \
    length=n;                                                                       \
    maxsize=max_n;                                                                  \
    if (flag)                                                                       \
    {                                                                               \
        ARRAY_FUNCTION_TRUE                                                         \
    }                                                                               \
    else{                                                                           \
            STATIC_ARRAY_FUNCTION_BODY(T)                                           \
            ARRAY_FUNCTION_FALSE                                                    \
    }                                                                               \
    return this;                                                                    \
}                                                                                   \
/***********************************************************************************/

/***************************************************/
#define auto_memory_add(T)                          \
if (maxsize <= length)                              \
{                                                   \
if(! REALLOC(array,T,maxsize+size_init))            \
        return false;                               \
     maxsize += size_init;                          \
}                                                   \
/***************************************************/
#define auto_memory_sub(T)                          \
if (maxsize - length > 200)                         \
{                                                   \
if(! REALLOC(array,T,maxsize-size_init))            \
{                                                   \
    printf("error:内存异常\n!");                    \
    exit(0);                                        \
}                                                   \
maxsize -= size_init;                               \
}                                                   \
/***************************************************/
/***************************************************/
#define ARRAY_FUNCTION_TRUE                         \
this.push_front=push_front;                         \
this.push_back=push_back;                           \
this.push_at=push_at;                               \
this.pop_front=pop_front;                           \
this.pop_back=pop_back;                             \
this.pop_at=pop_at;                                 \
this.resize=resize;                                 \
this.delete=delete;                                 \
/***************************************************/
#define ARRAY_FUNCTION_FALSE                        \
this.push_front=push_front;                         \
this.push_back=push_back;                           \
this.push_at=push_at;                               \
this.pop_front=pop_front;                           \
this.pop_back=pop_back;                             \
this.pop_at=pop_at;                                 \
this.resize=NULL;                                   \
this.delete=NULL;                                   \
/******************array函数体初始化****************/
#define ARRAY_FUNCTION_assignmen                    \
this.type=type;                                     \
this.length=length_;                                \
this.maxsize=maxszie_;                              \
this.empty=empty;                                   \
this.push_front=push_front;                         \
this.push_back=push_back;                           \
this.push_at=push_at;                               \
this.pop_front=pop_front;                           \
this.pop_back=pop_back;                             \
this.pop_at=pop_at;                                 \
this.front=front;                                   \
this.back=back;                                     \
this.at=at;                                         \
this.begin=begin;                                   \
this.end=end;                                       \
this.erase=erase;                                   \
this.insert=insert;                                 \
this.index=index_;                                  \
this.cmp=cmp;                                       \
this.setcmp=setcmp;                                 \
this.indexOf=indexOf;                               \
this.lastIndexOf=lastIndexOf;                       \
this.remove=remove_;                                \
this.traversal=traversal;                           \
this.setArray=setArray;                             \
this.sort=sort;                                     \
this.reverse=reverse;                               \
this.clear=clear;                                   \
this.resize=resize;                                 \
this.delete=delete;                                 \
/***************************************************/

/***************************************************/
#define new_array(T)                                \
({                                                  \
    T *array=NULL;                                  \
    size_t length = 0;                              \
    size_t maxsize = 0;                             \
    array(T) this;                                  \
    ARRAY_FUNCTION_BODY(T)                          \
    ARRAY_FUNCTION_assignmen                        \
    this;                                           \
})                                                  \
/***************************************************/
#endif //TEMPLATE_ARRAY_H
