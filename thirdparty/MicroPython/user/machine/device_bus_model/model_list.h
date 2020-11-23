/**
 *********************************************************************************************************
 *                                                Micropython
 *
 *                              (c) Copyright CMCC IOT All Rights Reserved
 *
 * @file	: os_list.h
 * @brief	: 链表操作
 * @author	: 周子涵
 * @version : V1.00.00
 * @date	: 2019年1月10日
 * 
 * The license and distribution terms for this file may be found in the file LICENSE in this distribution
*********************************************************************************************************
*/

#ifndef __MODEL_LIST_H__
#define __MODEL_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "model_def.h"  //added by chowhan at 2018-12-25



struct mpy_os_list_node
{
	struct mpy_os_list_node *prev;  		   /* 指向前一个节点							               */
	struct mpy_os_list_node *next;  		   /* 指向后一个节点							               */
};

typedef struct mpy_os_list_node mpy_os_list_t;

/**
*********************************************************************************************************
*                                      计算结构体偏移量
*
* @Description: TYPE类型的结构体s在地址0的位置。s结构体就是(type *)0，s结构体的成员地址就是
*			   (&((type *)0)->member)，那么s结构体的首地址到已知成员之间的偏移地址
*			   s_struct_offset = (&((type *)0)->member) -0
*
*			算法：
*				1. 将内存地址是0内存块转换成一个TYPE类型的指针,那么此时0地址的指针的步长就是TYPE。
*				2. 取TYPE结构体的MEMBER属性（注意此时TYPE结构体的指针的值是0）
*				3. 取TYPE结构体的MEMBER属性的地址，然后强转为unsigned long，就是MEMBER在结构体的偏移量
*
* @arguments   : TYPE:         结构体的类型
*
*				MEMBER：	  结构体的已知成员
*
* @Returns    : 结构体偏移量
*********************************************************************************************************
*/
#define mpy_os_offsetof(TYPE, MEMBER)	((unsigned long)&((TYPE *)0)->MEMBER)

/**
*********************************************************************************************************
*                                      获取结构体的入口地址（重点）
*
* @Description: 已知一个结构体里面的成员地址。反推出结构体的首地址。假设结构体首地址是x_struct_entry,那么
* 			   首地址到已知成员之间的偏移地址是x_struct_offset = offsetof(type, member)。
*			   x_struct_entry = ptr - x_struct_offset
*
* @Arguments  : ptr:          结构体的成员指针
*
*               type:         结构体的类型
*
*			    member:       已知结构体的成员
*
* @Returns    : 结构体的首地址
*********************************************************************************************************
*/
#define list_entry(ptr, type, member) 										\
		((type *)((char *)(ptr) - mpy_os_offsetof(type, member)))
		
/**
*********************************************************************************************************
*                                      获取结构体的入口地址
*
* @Description: 已知一个结构体里面的成员地址。反推出结构体的首地址。
*
* @Arguments  : pos:          已知结构体的成员地址，
*
*			    member:       已知结构体的成员
*
* @Returns    : 结构体的首地址
*********************************************************************************************************
*/
#define mpy_os_get_entry(pos, member)  	list_entry((pos)->member, typeof(*(pos)), member)
	

/**
*********************************************************************************************************
*                                      获取下一个节点所在的结构体的入口地址
*
* @Description: 已知一个结构体里面的成员地址，与节点。获取下一个节点的的首地址。
*
* @Arguments  : pos:          已知节点的地址，
*
*			    member:       已知结构体的成员
*
* @Returns    : 下一个节点所在的结构体的入口地址
*********************************************************************************************************
*/
#define mpy_list_next_entry(pos, member) 											\
		list_entry((pos)->member.next, typeof(*(pos)), member)



/**
*********************************************************************************************************
*                                      获取上一个节点所在的结构体的入口地址
*
* @Description: 已知一个结构体里面的成员地址，与节点。获取上一个节点的的首地址。
*
* @Arguments  : pos:          已知节点的地址，
*
*			    member:       已知结构体的成员
*
* @Returns    : 上一个节点所在的结构体的入口地址
*********************************************************************************************************
*/
#define mpy_list_prev_entry(pos, member) 											\
		list_entry((pos)->member.prev, typeof(*(pos)), member)
		
/**
*********************************************************************************************************
*                                      初始化链表
*
* @Description: 这个函数用来初始化一个新链表。新链表是一个双向链表。
*
* @rguments   : l:         头节点，不能为空。
*
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void mpy_os_list_init(mpy_os_list_t * l)
{
	l->next = l->prev = l;
}

/**
*********************************************************************************************************
*                                      向链表中插入节点
*
* @Description: 这个函数用来向链表中插入节点。
*
* @Arguments  : _new:		   需要插入的节点
*				p:	           需要插入的节点的上一个节点。
*				n:			   需要插入的节点的下一个节点
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void __list_add(mpy_os_list_t *_new, mpy_os_list_t * p, mpy_os_list_t *n)
{
	n->prev = _new;
	_new->next = n;
	_new->prev = p;
	p->next = _new;
}

/**
*********************************************************************************************************
*                                      向链表中当前节点后插入节点
*
* @Description: 这个函数用来向链表的指定节点后面插入新节点。
*
* @Arguments  : _new:          需要插入的节点。
*				curr:		   链表的指定节点，即插在它后面
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void mpy_os_list_add_next(mpy_os_list_t *_new, mpy_os_list_t *curr)
{
	__list_add(_new, curr, curr->next);
}

/**
*********************************************************************************************************
*                                      向链表中当前节点前插入节点
*
* @Description: 这个函数用来向链表的指定节点前面插入新节点。
*
* @Arguments  : _new:          需要插入的节点。
*				curr:		   链表的指定节点，即插在它前面
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void mpy_os_list_add_prev(mpy_os_list_t *_new, mpy_os_list_t *curr)
{
	__list_add(_new, curr->prev, curr);
}

/**
*********************************************************************************************************
*                                      链表尾部添加节点
*
* @Description: 这个函数用来向链表尾部添加一个节点。
*
* @rguments   : t:			尾节点，不能为空。
*
*				n:			需要插入的节点
*
* @Returns    : 无
*
* @Notes	  : 这个函数操作的链表是一个双向链表非环链表(一个头节点的前指针指向自己，尾节点的后指针指向自
*				己的双向链表)。
*********************************************************************************************************
*/
os_inline void mpy_os_list_tail_add(mpy_os_list_t *n, mpy_os_list_t * t)
{
	t->next = n;
	n->prev = t;
	n->next = n;
}

/**
*********************************************************************************************************
*                                      删除链表的头节点
*
* @Description: 这个函数用来删除链表的头节点。
*
* @Arguments  : next:          需要删除节点的后节点。
*				curr:		   需要删的除节点
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void __delete_head(mpy_os_list_t *next, mpy_os_list_t *curr)
{
	next->prev = next;
	mpy_os_list_init(curr);
}

/**
*********************************************************************************************************
*                                      删除链表的头节点
*
* @Description: 删除链表的头节点
*
* @Arguments  : curr:          需要删除的节点
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void mpy_os_list_delete_head(mpy_os_list_t *curr)
{
	__delete_head(curr->next, curr);
}

/**
*********************************************************************************************************
*                                      删除链表的尾节点
*
* @Description: 这个函数用来删除链表的尾节点。
*
* @Arguments  : prev:          需要删除节点的前节点。
*				curr:		   需要删的除节点
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void __delete_tail(mpy_os_list_t *prev, mpy_os_list_t *curr)
{
	prev->next = prev;
	mpy_os_list_init(curr);
}

/**
*********************************************************************************************************
*                                      删除链表的尾节点
*
* @Description: 删除链表的尾节点
*
* @Arguments  : curr:          需要删除的节点
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void mpy_os_list_delete_tail(mpy_os_list_t *curr)
{
	__delete_tail(curr->prev, curr);
}

/**
*********************************************************************************************************
*                                      删除链表节点
*
* @Description: 这个函数用来删除一个链表的节点。
*
* @Arguments  : prev:          需要删除的节点的上一个节点。
*				next:		   需要删除的节点的下一个节点
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void __list_del(mpy_os_list_t *prev, mpy_os_list_t *next)
{
	next->prev = prev;
	prev->next = next;
}

/**
*********************************************************************************************************
*                                      删除链表节点
*
* @Description: 这个函数用来删除一个链表的节点。
*
* @Arguments  : list:          链表节点，需要删除的节点。
*
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void mpy_os_list_remove(mpy_os_list_t *list)
{
	__list_del(list->prev, list->next);
}

/**
*********************************************************************************************************
*                                      删除链表节点,并初始化节点  
 *
* @Description: 这个函数用来删除一个链表的节点。
*
* @Arguments  : list:          链表节点，需要删除的节点。
*
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void mpy_os_list_del_init(mpy_os_list_t *list)
{
	__list_del(list->prev, list->next);
	mpy_os_list_init(list);
}

/**
*********************************************************************************************************
*                                      检查链表是否为空
*
* @Description: 这个函数用来测试一个链表是否为空链表。
*
* @Arguments  : list:         链表节点，用于测试。
*
*
* @Returns    : 真：链表为空；假：链表非空
*
* @Notes	  : 此链表为双向循环链表
*********************************************************************************************************
*/
os_inline int mpy_os_list_isempty(const mpy_os_list_t *list)
{
    return list->next == list;
}

/**
*********************************************************************************************************
*                                      检查链表是结束
*
* @Description: 这个函数用来测试一个链表是否是最后一个节点。
*
* @Arguments  : list:         链表节点，用于测试。
*
*
* @Returns    : 真：链表结束；假：链表没有结束
*
* @Notes	  : 这个函数操作的链表是一个双向链表非环链表(一个头节点的前指针指向自己，尾节点的后指针指向自
*				己的双向链表)。
*********************************************************************************************************
*/
os_inline int mpy_os_list_is_end(const mpy_os_list_t *list)
{
    return list->next == list;
}

/**
*********************************************************************************************************
*                                      检查链表是结束
*
* @Description: 这个函数用来测试一个链表是否是最后一个节点。
*
* @Arguments  : head:         链表头节点
*
*				list:         链表节点
*
* @Returns    : 真：链表结束；假：链表没有结束
*
* @Notes	  : 这个函数操作的链表是一个双向链表环形链表。
*********************************************************************************************************
*/
os_inline int mpy_os_cycle_list_is_end(const mpy_os_list_t *head, const mpy_os_list_t *list)
{
    return head == list->next;
}

/**
*********************************************************************************************************
* @brief                                 查找头节点
*
* @Description: 查找头节点。链表非环形双向链表
*
* @param	  :	n 		链表节点
*
* @return	  : 尾节点
*********************************************************************************************************
*/	
os_inline mpy_os_list_t *mpy_os_list_find_head(mpy_os_list_t * n)
{
	mpy_os_list_t *t = n;
	while ( t->prev != t){
		t = t->prev;
	}
	return t;
}

/**
*********************************************************************************************************
* @brief                                 查找尾节点
*
* @Description: 查找尾节点。链表非环形双向链表
*
* @param	  :	n 		链表节点
*
* @return	  : 尾节点
*********************************************************************************************************
*/
os_inline mpy_os_list_t *mpy_os_list_find_tail(mpy_os_list_t * n)
{
	mpy_os_list_t *t = n;
	while (t->next != t){ 
		t = t->next;
	}
	return t;
}

/**
*********************************************************************************************************
*                                      在链表指定节点的后面插入新节点
*
* @Description: 这个函数用来向链表中插入节点。链表必须是双向链表，并且不为空，否则出错。
*
* @Arguments  : curr_node:    当前链表中指定的节点
*
*               new_node:     待插入的非空节点
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void mpy_os_list_insert_after(mpy_os_list_t *curr_node, mpy_os_list_t *new_node)
{
	mpy_os_list_add_next(new_node, curr_node);
}


/**
*********************************************************************************************************
*                                      在链表指定节点的前面插入新节点
*
* @Description: 这个函数用来向链表中插入节点。链表必须是双向链表，并且不为空，否则出错。
*
* @Arguments  : curr_node:    当前链表中指定的节点
*
*               new_node:     待插入的非空节点
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void mpy_os_list_insert_before(mpy_os_list_t *curr_node, mpy_os_list_t *new_node)
{
	mpy_os_list_add_prev(new_node, curr_node);
}

/**
*********************************************************************************************************
*                                      合并两个链表
*
* @Description: 这个函数用来合并两个链表。链表必须是双向非环形链表，并且不为空，否则出错。
*
* @Arguments  : l1_tail:     链表1尾节点
*
*               l2_head:     链表2头节点
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void mpy_os_list_merge(mpy_os_list_t *l1_tail, mpy_os_list_t *l2_head)
{
	l1_tail->next = l2_head;
	l2_head->prev = l1_tail;
}

/**
*********************************************************************************************************
*                                      合并两个链表
*
* @Description: 这个函数用来合并两个链表。链表必须是双向环形链表，并且不为空，否则出错。
*
* @Arguments  : l1：		 链表1头节点
*
*				l1_tail:     链表1尾节点
*
*               l2:     	 链表2头节点
*
*               l2_tail:     链表2尾节点
*
* @Returns    : 无
*
* @note		  : 头尾相接模式，链表秩序不变
*********************************************************************************************************
*/
os_inline void __cycle_list_merge(mpy_os_list_t *l1, mpy_os_list_t *l1_tail,  mpy_os_list_t *l2, mpy_os_list_t *l2_tail)
{
	l1_tail->next = l2;
	l1->prev = l2_tail;
	l2_tail->next = l1; 
	l2->prev = l1_tail;
}

/**
*********************************************************************************************************
*                                      合并两个链表
*
* @Description: 这个函数用来合并两个链表。链表必须是双向环形链表，并且不为空，否则出错。
*
* @Arguments  : l1_tail:     链表1尾节点
*
*               l2_head:     链表2头节点
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void mpy_os_list_cycle_merge(mpy_os_list_t *l1, mpy_os_list_t *l2)
{
	__cycle_list_merge(l1, l1->prev, l2, l2->prev);
}

/**
*********************************************************************************************************
*                                      摧毁整个链表
*
* @Description: 这个函数用来摧毁整个链表。链表必须是双向链表，并且不为空，否则出错。不删除头链表。
*
* @Arguments  : head:     需要摧毁的链表头节点
*
*               tail:     需要摧毁的链表尾节点
*
*				free_fun：释放内存的函数, 比如 free函数
*
* @Returns    : 无
*********************************************************************************************************
*/
os_inline void mpy_os_list_destroy(mpy_os_list_t *head, mpy_os_list_t *tail, void (free_fun)(void *))
{
	mpy_os_list_t *node;

	for (node = tail->prev; node != head; node = node->prev)
	{
		mpy_os_list_del_init(node->next);
		free_fun(node->next);
	}
}

/**
*********************************************************************************************************
*                                      安全遍历链表
*
* @Description: 这个接口用来安全遍历链表。链表必须是双向链表，并且不为空，否则出错。
*
* @Arguments  : pos   :     for循环参数，指针类型，链表节点指针
*
*               n     :     临时参数，指针类型，指向pos的下一个节点
*
*				head  :		链表头节点
*
*				member:		链表节点中的结构体成员
*
* @Returns    : 无
*
* @Notes	  : 这不是一个完整的函数，只是一个for循环，所以使用时请注意.
*				list_for_each_entry_safe(pos, n, head, member){
*					在此处添加处理信息	
*				}
*********************************************************************************************************
*/

#define mpy_list_for_each_entry_safe(pos, n, head, member)					\
	for (pos = list_entry((head)->next, typeof(*pos), member),			    \
		 n = mpy_list_next_entry(pos, member);		                        \
		 &pos->member != (head);											\
		 pos = n, n = mpy_list_next_entry(n, member))

#endif
