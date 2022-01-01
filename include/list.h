/*
    C语言不支持泛型编程，那么不同的数据列表（list）就要生成不同数据类型的列表
    例如：
    typedef struct node{
        //循环双链表的结点结构
        DataType data;//数据域指针
        struct node *next;//指向当前结点的下一结点
        struct node *last;//指向当前结点的上一结点
    }Node;
    然后，当需要使用整型的链表时，就把DataType用typedef为int。
    其实这样做的一个最大的缺陷就是一个程序中只能存在着一个数据类型的链表
    例如，如果我需要一个int型的链表和一个float型的链表，其操作都是一样的，那么该把DataType定义为int呢还是float呢？
    这样就会比较麻烦

    但是可以用宏实现
    https://stackoverflow.com/questions/16522341/pseudo-generics-in-c
    https://github.com/UphillD/ARMadillo/blob/f92296379e082b3fb083255b04edaeed4c722194/include/common/list.h

*/
#ifndef LIST_H
#define LIST_H

#include "stdtype.h"

#endif