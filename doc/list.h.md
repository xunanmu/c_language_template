---
title: list.h
categories:
  - C语言
tags:
  - 数据结构
date: 2020-03-13 02:32:59
---
## list模板示例
``` c
#include "list.h"
#include <time.h>
LIST_TYPE_SET(int);

int main(){
    list(int) this=new(list(int));
    for (int i = 0; i < 10; ++i) {
        this.push_front(i);
        this.push_back(i);
    }
    void print(int data) {
        printf("%d ", data);
    }
    int cp(const void *a, const void *b) {
        return *(int *) a - *(int *) b;
    }
    this.traversal(print).reverse().traversal(print).remove(1).traversal(print);
    printf("length:%d\n", this.length());
    this.sort().traversal(print);


    srand((unsigned) time(NULL));
    time_t t = time(0);

    for (int i = 0; i < 1000000000; ++i)
        this.push_back(rand() % 0xfffffff);
    printf("\n申请time:%lds\n", time(0) - t);

    t = time(0);
    this.setcmp(cp).sort();
    printf("\n排序time:%lds\n", time(0) - t);
    this.delete();

    return 0;
}c
```

`十亿个int直接内存不够了`
``` c
9 8 7 6 5 4 3 2 1 0 0 1 2 3 4 5 6 7 8 9
9 8 7 6 5 4 3 2 1 0 0 1 2 3 4 5 6 7 8 9
9 8 7 6 5 4 3 2 0 0 2 3 4 5 6 7 8 9
length:18
0 0 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9
error:D:\jetbrians\c\template\test.c文件push_back函数内,node申请失败!
```
**一亿个int结果**
``` c
9 8 7 6 5 4 3 2 1 0 0 1 2 3 4 5 6 7 8 9
9 8 7 6 5 4 3 2 1 0 0 1 2 3 4 5 6 7 8 9
9 8 7 6 5 4 3 2 0 0 2 3 4 5 6 7 8 9
length:18
0 0 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9

申请time:6s

排序time:7s
```
## next()
>`next(iteration)`这个是全局宏函数
>类似++iteration,c语言无法做到重载操作符只能用宏实现
```
    __auto_type it=list.begin();
    while(it!=list.end())
    {
        printf("%d",*it);
        next(it);
    }
    //或者
    __auto_type _it=list.begin();
    while(it!=list.end())
    {
        printf("%d",*next(_it));//此时打印_it是第二个
    }
```

## prev()
>`prev(iteration)`宏函数
>类似--iteration

## length()
>`size_t length();`
>返回长度

## empty()
>`bool empty();`
>判断容器是否为空,空返回`true`

## push_front()
>`bool push_front(T data);`
>内存申请失败或者静态空间不足会返回`false`

## push_back()
>`bool push_back(T data);`
>在尾部添加元素;

## push_at()
>`bool push_at(T data, int index);`
>指定位置添加元素,超出范围返回`false`
>建议不要经常使用,时间复杂度O(n);

## pop_front()
>`T pop_front();`
>删除头部元素,并返回删除的元素;

## pop_back()
>`T pop_back();` 
>删除尾部元素,并返回删除的元素

## pop_at()
>`T pop_at(int index);`
>pop_at(int index);删除指定索引的元素,并返回删除的元素
>建议不要经常使用,时间复杂度O(n);

## front()
>`T* front();`
>返回头部元素的指针;
>你可以头部指针直接修改元素

```c
*a.front()=5;
```

## back()
>`T* back();`
>返回尾部元素指针;

## at()
>`at(int index)`返回指定元素的指针;
>建议不要经常使用,时间复杂度O(n);

## begin()
`T *begin();`
>返回头部迭代器

## end()
`T* end();`
>返回尾迭代器(其实就是最后元素的下一个指针)

## erase()
>`T* erase(T* iteration,T data);`
>删除此迭代器,返回下一个元素的迭代器

## insert()
>`T *insert(T *iteration, T data);`
>在此迭代器前插入,返回插入元素的迭代器

## cmp()
>`int cmp(const void *data, const void* temp)`
>默认比较函数,和qsort()的比较函数一样

## setcmp()
>`list(T) setcmp(int (*cmp)(const void *data, const void* temp))`
>设置比较函数,和qsort()的一样,返回自己

## indexOf()
>`int indexOf(T data)`
>返回此元素的第一个索引,如果没有则返回-1
>可以通过`setcmp()`设置查询条件

## lastIndexOf()
>`int lastIndexOf(T data)`
>返回此元素的最后一个索引,如果没有则返回-1
>可以通过`setcmp()`设置查询条件

## remove()
>`list(T) remove(T data)`
>删除所有值data的元素,返回自己
>可以通过`setcmp()`设置删除条件

## traversal()
`list(T) traversal(void (*output)(T data)) `
>遍历容器,需要自己实现输出函数,返回自己

## reverse()
`list(T) reverse()`
>反转容器元素,返回自己

## delete()
`list(T) delete()`
>清空元素,并释放内存,返回自己

## 后记
>如果有什么错误,请加QQ编程交流群:982865797 反馈