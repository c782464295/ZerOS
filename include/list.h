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


/**
 * 用宏实现任意类型的list.
 *
 * 要使用，请在要定义列表结构的头文件中调用 DEFINE_LIST (typename)。 typename 应该是结构的非类型定义名称
 * 没有关键字“struct”。 如果我想定义一个“struct point”类型的列表，我需要做“DEFINE_LIST（point）”。 
 * 这将创建名为的列表类型
 * “typename_list_t”，可以根据需要多次重复使用。
 * 接下来，您必须在结构体内部调用 DEFINE_LINK (typename)。
 *
 * 最后，调用 IMPLEMENT LIST (typename) 你希望列表被实现的地方
 *
 * Before using an instance of the list, you should call INITIALIZE_LIST(list) to correctly it up
 *
 *
 * IMPLEMENT_LIST defines the following functions:
 * void append_nodeType_list(nodeType_list_t * list, struct nodeType *)
 *      appends to the back of the list
 *
 * void push_nodeType_list(nodeType_list_t * list, struct nodeType *)
 *      adds to the front of the list
 *
 * struct nodeType * peek_nodeType_list(nodeType_list_t * list)
 *      gets the first element from the list without removing it
 *
 * struct nodeType * pop_nodeType_list(nodeType_list_t * list)
 *      gets the first element from the list and removes it
 *
 * u32 size_nodeType_list(nodeType_list_t * list)
 *      returns the number of elements in the list
 *
 * struct nodeType * next_nodeType_list(struct nodeType * node)
 *      gets the next node in the list, null if none left
 *
 * void remove_nodeType(nodeType_list_t * list, struct nodeType * node)
 *      removes the given element from the list
 */
#include "stdtype.h"

#ifndef LIST_H
#define LIST_H


// 定义一个结构体，包含头指针，尾指针，长度
#define DEFINE_LIST(nodeType) \
struct nodeType;            \
typedef struct nodeType##list { \
    struct nodeType * head; \
    struct nodeType * tail; \
    u32 size;\
} nodeType##_list_t;

// 前向指针，后向指针
#define DEFINE_LINK(nodeType) \
struct nodeType * next##nodeType;\
struct nodeType * prev##nodeType;\
nodeType##_list_t * container;

// 初始化
#define INITIALIZE_LIST(list) \
    list.head = list.tail = (void *)0;\
    list.size = 0;

// list实现
// 添加节点
// push节点
// peek去头节点
// pop
// 返回大小
// 下一个
// remove
#define IMPLEMENT_LIST(nodeType) \
void append_##nodeType##_list(nodeType##_list_t * list, struct nodeType * node) {  \
    list->tail->next##nodeType = node;                                       \
    node->prev##nodeType = list->tail;                                       \
    list->tail = node;                                                       \
    node->next##nodeType = NULL;                                             \
    list->size += 1;                                                         \
    if (list->head == NULL) {                                                \
        list->head = node;                                                   \
    }                                                                        \
    node->container = list;                                                  \
}                                                                            \
                                                                             \
void push_##nodeType##_list(nodeType##_list_t * list, struct nodeType * node) {    \
    node->next##nodeType = list->head;                                       \
    node->prev##nodeType = NULL;                                             \
    list->head = node;                                                       \
    list->size += 1;                                                         \
    if (list->tail == NULL) {                                                \
        list->tail = node;                                                   \
    }                                                                        \
    node->container = list;                                                  \
}                                                                            \
                                                                             \
struct nodeType * peek_##nodeType##_list(nodeType##_list_t * list) {         \
    return list->head;                                                       \
}                                                                            \
                                                                             \
struct nodeType * pop_##nodeType##_list(nodeType##_list_t * list) {          \
    struct nodeType * res = list->head;                                      \
    list->head = list->head->next##nodeType;                                 \
    list->head->prev##nodeType = NULL;                                                 \
    list->size -= 1;                                                         \
    if (list->head == NULL) {                                                \
        list->tail = NULL;                                                  \
    }                                                                        \
    res->container = NULL;                                                  \
    return res;                                                              \
}                                                                            \
                                                                             \
u32 size_##nodeType##_list(nodeType##_list_t * list) {                  \
    return list->size;                                                       \
}                                                                            \
                                                                             \
struct nodeType * next_##nodeType##_list(struct nodeType * node) {           \
    return node->next##nodeType;                                             \
}                                                                            \
                                                                             \
void remove_##nodeType (nodeType##_list_t * list, struct nodeType * node) {  \
    if (node->container == list) {                                           \
        if (node->prev##nodeType == NULL) {                                 \
            list->head = node->next##nodeType;                               \
        } else {                                                             \
            node->prev##nodeType = node->next##nodeType;                     \
        }                                                                    \
        if (node->next##nodeType == NULL) {                                  \
            list->tail = node->prev##nodeType;                               \
        } else {                                                            \
            node->next##nodeType = node->prev##nodeType;                    \
        }                                                                   \
    }                                                                       \
    node->container = NULL;                                                 \
}                                                                           \





#endif



/* 使用方法如下
void test(void){


	DEFINE_LIST(page);
	
	typedef struct page{
		u32 vaddr_mapped;	// The virtual address that maps to this page	
		u32 flags;
		DEFINE_LINK(page);
	}page_t;

	page_list_t free_pages;

	INITIALIZE_LIST(free_pages);

	IMPLEMENT_LIST(page);
}
*/