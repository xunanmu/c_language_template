/**
 * 作者: 徐南木
 * 说明: 模板头文件
 * 编译器: mingw-w64
 * 时间: 2020/2/12 14:25
 * 详细注解: http://blog.xunanmu.com/2020/03/13/template.h/
 */
#ifndef TEMPLATE_TEMPLATE_H
#define TEMPLATE_TEMPLATE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/*类型模板宏定义*/
//#define typeof()  __typeof__()
#define typeof(T)  __typeof(T)
#define var __auto_type
#define ___(T,type) T##_##type
#define __(T,type) ___(T,type)
#define _(type) __(T,type)

/* 作者: 徐南木
 * 说明: 函数模板宏,funcname是函数名
 *       functype是一个接口宏,用来确定函数类型
 * 时间: 2020/2/12 14:29
 * 废弃;
 */
//#define $(funcname) __(funcname,functype)

/*函数宏定义*/
#define init(x) __(init,x)()

/* 作者: 徐南木
 * 说明: 用指针new出来的对象必须使用delete释放
 * 时间: 2020/2/12 14:44
 */
#define new(type) new##_##type
/*#define delete(x) __(delete,x)*/

#define _tostring(x) #x
#define tostring(x) _tostring(x)
#define _tochar(x) *#x
#define tochar(x) _tochar(x)

#define size_init 100//初始块

/* 作者: 徐南木
 * 说明: 交换变量
 * @return: void
 * 时间: 2020/2/12 15:07
 */
#define swap(a,b) do{\
typeof(a) t = (a);\
         (a)= (b);\
         (b)= (t);\
}while(0)

/* 作者: 徐南木
 * 说明: 接收地址交换指定块变量
 *       能交换所有元素
 * @return: void
 * 时间: 2020/2/12 15:29
 */
#define SWAP(a,b,size)({\
    char buffer[(size)];\
    memmove(buffer,(a),(size));\
    memmove((a),(b),(size));\
    memmove((b),buffer,(size));\
})

/* 作者: 徐南木
 * 说明: 申请内存
 * @return: void
 * 时间: 2020/2/12 15:41
 */
#define MALLOC(ptr,type,n)({\
    ptr=(type*)malloc(sizeof(type)*(n));\
    if(!ptr){\
        printf("error:%s文件%s函数内,%s申请失败!\n",__FILE__,__func__,tostring(ptr));\
        exit(0);}\
})

/* 作者: 徐南木
 * 说明: 改变内存大小
 *       如果失败返回false
 * @return: bool
 * 时间: 2020/2/12 15:44
 */
#define REALLOC(ptr,type,n)({\
    void* new_ptr=realloc(ptr,sizeof(type)*(n));\
    bool flag=true;\
    if(!new_ptr){\
        printf("error:%s文件%s函数内,%s内存改变失败!\n",__FILE__,__func__,tostring(ptr));\
        flag=false;}\
    else \
        ptr=(type*)new_ptr;\
        flag;\
})

#define UNDERFLOW                                             \
if (empty())                                                  \
{                                                             \
printf("error:%s文件内%s函数产生下溢操作!",__FILE__,__func__);\
exit(0);                                                      \
}

#define _node(T) T##_node
#define singly_pointer_node(T)                                             \
typedef struct _node(T) _node(T);                                          \
struct _node(T) {                                                          \
    _node(T) *next;                                                        \
    T data;                                                                \
}

#endif //TEMPLATE_TEMPLATE_H
