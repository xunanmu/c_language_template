---
title: queue.h
categories:
  - C语言
tags:
  - 数据结构
date: 2020-03-13 02:30:04
---
## queue示例
``` c
#include <stdio.h>
#include "queue.h"

QUEUE_TYPE_SET(char);

typedef struct person Person;
struct person {
    char name[10];
    char sex[4];
    int age;
} person_3[] = {
        {"南木", "男", 20},
        {"橙子", "男", 35},
        {"时光", "男", 16},
        {"岑子", "男", 22},
        {"附离", "男", 18},
};
QUEUE_TYPE_SET(Person);

void print_char(char c);
void print_person(Person one);

int main() {
    queue(char) charQueue = new(queue(
                                        char));
    for (char i = 'A'; i < 'H'; ++i) {
        charQueue.push(i);
    }
    while (!charQueue.empty())
        print_char(charQueue.pop());

    puts("");
    queue(Person) personQueue = new(queue(Person));
    for (int i = 0; i < 5; ++i) {
        personQueue.push(person_3[i]);
    }
    while (!personQueue.empty())
        print_person(personQueue.pop());
    return 0;

}
c
void print_char(char c) {
    printf("%c ", c);
}

void print_person(Person one) {
    printf("<%s,%s,%d>\n", one.name, one.sex, one.age);
}
```
**结果**
``` c
A B C D E F G
<南木,男,20>
<橙子,男,35>
<时光,男,16>
<岑子,男,22>
<附离,男,18>
```

## length()
> `size_t length();`
> 返回长度

## empty()
> `bool empty();`
> 返回真假,空为真

## push()
> `void push(T data);`
> 入队,返回值为空
 
## pop()
> `T pop();`
> 出队,返回出队的值

## front()
> `T* front();`
> 返回队头指针

## back()
>`T* back();`
>返回队尾指针

## delete()
>`void delete();`
>清空所有元素

## 后记
>`queue`只有链表容器,后期实现双端队列
>> 如果有什么错误,请加QQ编程交流群:982865797 反馈