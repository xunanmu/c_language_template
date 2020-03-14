---
title: stack.h
categories:
  - C语言
tags:
  - 数据结构
date: 2020-03-13 02:21:19
---
## stack.h示例
``` c
#include <stdio.h>
#include "stack.h"
STACK_TYPE_SET(char);

typedef struct person Person;
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
STACK_TYPE_SET(Person);


void print_char(char c);
void print_person(Person one);

int main() {
    /********stack默认list******************/
    stack(char) test=new(stack(char));
    for (char i = 'A'; i < 'H'; ++i) {
        test.push(i);
    }
    for (char i = 'A'; i < 'H'; ++i) {
        test.push(i);
    }
    while (!test.empty())
        print_char(test.pop());

    /*********stack数组用法**************/
    stack(Person) personStack=new(stackArray(Person));
    for (int  i = 0; i < 5; ++i) {
        personStack.push(person_3[i]);
    }
    while (!personStack.empty())
        print_person(personStack.pop());
    return 0;

}

void print_char(char c) {
    printf("%c ", c);
}

void print_person(Person one) {
    printf("<%s,%s,%d>\n", one.name, one.sex, one.age);
}
```
**结果**
``` c
G F E D C B A G F E D C B A <附离,男,18>
<岑子,男,22>
<时光,男,16>
<橙子,男,35>
<南木,男,20>
```
## length()
>`size_t length();`
>返回长度

## empty()
>`bool empty();`
>返回真假,空为真

## push()
>`void push(T data);`
>压入栈,返回值为空

## pop()
>`T pop();`
>弹出栈,返回弹出的值

## top()
>`T* top();`
>返回一个栈顶指针,你可以自己修改栈顶`a.top()=9`

## delete()
>`void delete();`
>清空所有元素

## 后记
> `stack`现在有两种容器实现,一个是链表(默认),一个数组
> 后期可能会实现双端队列
>> 如果有什么错误,请加QQ编程交流群:982865797 反馈