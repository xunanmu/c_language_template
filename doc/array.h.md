---
title: array.h
categories:
  - C语言
tags:
  - 编程基础
date: 2020-03-13 02:10:34
---
[TOC]
## array泛型模板示例
``` c
#include <stdio.h>
#include "array.h"
ARRAY_TYPE_SET(char);

typedef struct person Person;
ARRAY_TYPE_SET(Person);
struct person{
    char name[8];
    char sex[4];
    int  age;
}person_3[]={
        {"南木","男",20},
        {"橙子","男",35},
        {"时光","男",16},
        {"岑子","男",22},
        {"附离","男",18},
};


int main() {

    /********array动态用法******************/
    array(char) test=new(array(char));
    for (char i = 'A'; i < 'H'; ++i) {
        test.push_back(i);
    }
    for (char i = 'A'; i < 'H'; ++i) {
        test.push_back(i);
    }
    void print_char(char c);
    test.traversal(print_char);
    test.sort().traversal(print_char).reverse().traversal(print_char);

    /*********array静态用法***************/
    array(Person) _static=new(array(Person));
    _static.setArray(person_3, 5, 5,false);
    void print_person(Person one);
    _static.sort().traversal(print_person).reverse().traversal(print_person);

    /***修改默认比较函数,按年龄比较***/
    int agecmp(const void* one,const void* two);
    _static.setcmp(agecmp);
    _static.sort().traversal(print_person).reverse().traversal(print_person);

    test.delete();

    return 0;
}

void print_char(char c) {
    printf("%c ", c);
}

void print_person(Person one) {
    printf("<%s,%s,%d>\n", one.name, one.sex, one.age);
}

int agecmp(const void *one, const void *two) {
    return ((Person *) one)->age > ((Person *) two)->age;
}
```

``` c
A B C D E F G A B C D E F G
A A B B C C D D E E F F G G
G G F F E E D D C C B B A A
<南木,男,20>
<岑子,男,22>
<时光,男,16>
<橙子,男,35>
<附离,男,18>

<附离,男,18>
<橙子,男,35>
<时光,男,16>
<岑子,男,22>
<南木,男,20>

<时光,男,16>
<附离,男,18>
<南木,男,20>
<岑子,男,22>
<橙子,男,35>

<橙子,男,35>
<岑子,男,22>
<南木,男,20>
<附离,男,18>
<时光,男,16>
```
## ARRAY_TYPE_SET()
>全局设置类型

``` c
typedef struct array(T) array(T);
struct array(T) {
    /*返回变量类型名*/
    char *(*type)();
    /*返回元素个数*/
    size_t (*length)();
    /*返回最大容量*/
    size_t (*maxsize)();
    /*空返回真*/
    bool (*empty)();
    /*在头部添加元素*/
    bool (*push_front)(T data);
    /*在尾部添加元素*/
    bool (*push_back)(T data);
    /*指定位置添加元素*/
    bool (*push_at)(T data, int index);
    /*删除并返回头部的元素*/
    T (*pop_front)();
    /*删除并返回尾部的元素*/
    T (*pop_back)();
    /*删除并返回指定位置的元素*/
    T (*pop_at)(int index);
    /*返回头部的元素*/
    T* (*front)();
    /*返回尾部的元素地址*/
    T* (*back)();
    /*返回指定位置的元素地址*/
    T* (*at)(int index);
    /*返回头部的迭代器*/
    T *(*begin)();
    /*返回尾部的迭代器*/
    T *(*end)();
    /*删除此迭代器内容,返回是下一个元素的迭代器*/
    T *(*erase)(T *iterator);
    /*在此迭代器前插入元素,返回是插入元素的迭代器*/
    T *(*insert)(T *iterator, T data);
    /*返回此迭代器的索引*/
    int (*index)(T *iterator);
    /*默认比较函数*/
    int (*cmp)(const void *data, const void* temp);
    /*返回此元素的第一个索引*/
    int (*indexOf)(T data);
    /*返回此元素的最后一个索引*/
    int (*lastIndexOf)(T data);
    /*删除指定元素*/
    array(T) (*remove)(T data);
    /*遍历所有元素*/
    array(T) (*traversal)(void (*output)(T data));
    /*n是当前数组元素个数,max_n当前数组容量,false是静态,true是动态*/
    array(T) (*setArray)(T *arr, int n, int max_n, bool set);
    /*重置数组大小*/
    array(T) (*resize)(int size);
    /*默认升序排序,设置cmp指定排序*/
    array(T) (*sort)();
    /*反转数组*/
    array(T) (*reverse)();
    /*清空,但不删除内存*/
    array(T) (*clear)();
    /*删除所有内存*/
    array(T) (*delete)();
};
```

## type()
>返回类型名

``` c
char *type() {
    return tostring(array(T));
}
```

## length()
>`size_t length();`
>返回当前元素个数


## maxsize()
>`size_t maxsize();`
>返回数组容器当前容量


## empty()
>`bool empty();`
>判断容器是否为空,空返回`true`


## push_front()
>`bool push_front(T data);`
>在头部添加元素;这个有动态和静态实现两种方式
>内存申请失败或者静态空间不足会返回`false`

## push_back()
`bool push_back(T data);`
>在尾部添加元素;

## push_at()
>`bool push_at(T data, int index);`
>指定位置添加元素,超出范围返回`false`

## pop_front()
>`T pop_front();`
>删除头部元素,并返回删除的元素;
>同push也有静态和动态两种实现,会自动调整内存大小


## pop_back()
>`T pop_back();` 
>删除尾部元素,并返回删除的元素

## pop_at()
>`T pop_at(int index);`
>pop_at(int index);删除指定索引的元素,并返回删除的元素

## front()
>`T* front();`
>返回头部元素的指针;
>你可以头部指针直接修改元素


```c
*a.front()=5;
/*或者*/
a.front()[0]=5;
```

## back()
>`T* back();`
>返回尾部元素指针;

## at()
>`at(int index)`返回指定元素的指针;
```c
*a.at(i)==a.front()[i];
```
## begin()
`T *begin();`
>返回头部迭代器

```c
T *it=a.begin();
while(it!=end())
    ++it;
```
## end()
`T* end();`
>返回尾迭代器(其实就是最后元素的下一个指针)

## erase()
>`T* erase(T* iteration,T data);`
>删除此迭代器,返回下一个元素的迭代器

## insert()
>`T *insert(T *iteration, T data);`
>在此迭代器前插入,返回插入元素的迭代器

## index()
>`int index(T *iteration);`
>返回迭代器索引

## cmp()
>`int cmp(const void *data, const void* temp);`
>默认比较函数,和qsort()的比较函数一样

## setcmp()
>`array(T) setcmp(int (*cmp)(const void *data, const void* temp));`
>设置比较函数,和qsort()的一样,返回自己

## indexOf()
>`int indexOf(T data);`
>返回此元素的第一个索引,可以通过`setcmp()`设置查找条件,如果没有则返回-1

## lastIndexOf()
>`int lastIndexOf(T data);`
>返回此元素的最后一个索引,可以通过`setcmp()`设置查找条件,如果没有则返回-1

## remove()
>`array(T) remove(T data);`
>删除所有值data的元素,可以通过`setcmp()`设置删除条件
>返回自己

``` c
struct person{
    char name[8];
    char sex[4];
    int  age;
}person_3[]={
        {"南木","男",20},
        {"橙子","男",35},
        {"时光","男",16},
        {"岑子","男",22},
        {"附离","男",18},
};
/*删除18岁以下的*/
void cmp(const void* a,const void* b)
{
    if(((struct person*)b)->age<18)
        return 0;
    else 
        return 1;
}
/*remove()里面参数随便填就好了,
 *cmp()的a是自己的,b是容器里的
 */
a.setcmp(cmp).remove(data);
```
## traversal()
>`array(T) traversal(void (*output)(T data)); `
>遍历容器,需要自己实现输出函数,返回自己

## setArray()
>`array(T) setArray(T arrays[],int n,int max_n,bool flag); `
> array外面的静态数组地址,n是数组元素数量,max_n是静态数组最大容量,flag值为false是浅复制(直接交换指针),true是完全复制(与静态数组是不同的数组)
>返回值是自己

## sort()
>`array(T) sort();`
> 默认升序排序,setcmp()可设置比较函数,返回自己

## reverse()
>`array(T) reverse();`
>反转容器元素,返回自己

## clear()
>`array(T) clear();`
>清空容器元素,不删除内存,返回自己

## resize()
>`array(T) resize(int size);`
>重新设置动态数组大小,返回自己

## delete()
>`array(T) delete();`
>清空元素,并释放内存,返回自己

## 后记
>如果有什么错误,请加QQ编程交流群:982865797 反馈