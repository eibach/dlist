/* SPDX-License-Identifier: MIT */

#ifndef _DLIST_H
#define _DLIST_H

#include <stddef.h>

/**
 * Simple double linked list implementation
 * 
 * This double linked list implementation uses a head node for managing the
 * ĺist. The "next"-field of the head node points to the first element of the
 * list, the "previous"-node to the last element.
 * The :c:type:`dlist_node` struct is meant to be embedded in a
 * "container"-struct.
 */

/**
 * List node
 */
struct dlist_node {
	struct dlist_node *next;
	struct dlist_node *previous;
};

/**
 * Initialize list
 * 
 * @param node: The list node to be intialized
 */
static inline void dlist_init_node(struct dlist_node *node)
{
	node->next = node;
	node->previous = node;
}

static inline void _dlist_insert_between(struct dlist_node *add,
										 struct dlist_node *previous,
										 struct dlist_node *next)
{
	previous->next = add;
	add->previous = previous;
	next->previous = add;
	add->next = next;
}

/**
 * Add new node after specified node 
 * 
 * @param add: the new node
 * @param node: the node to add the element after
 */
static inline void dlist_add(struct dlist_node *add,
							struct dlist_node *node)
{
	_dlist_insert_between(add, node, node->next);
}

/**
 * Add new node before specified node 
 * 
 * @param add: the new node
 * @param node: the node to add the element before
 */
static inline void dlist_add_tail(struct dlist_node *add,
                            struct dlist_node *node)
{
	_dlist_insert_between(add, node->previous, node);
}

/**
 * Delete a node from a list
 * 
 * @param del: the node to delete
 */
static inline void dlist_del(struct dlist_node *del)
{
	del->previous->next = del->next;
	del->next->previous = del->previous;
	dlist_init_node(del);
}

/**
 * Check if a list is empty
 * 
 * @param head: the head node of the list
 * :return: non-zero if list is empty.
 */
static inline int dlist_is_empty(const struct dlist_node *head)
{
	return head->next == head;
}

/**
 * Check if node is last element in the list
 * 
 * @param node: node to check
 * @param head: the head node of the list
 * :return: non-zero if node is last element.
 */
static inline int dlist_is_last(const struct dlist_node *node,
							const struct dlist_node *head)
{
	return node->next == head;
}

/**
 * Iterate over all elements of the list
 * 
 * @param it: iterator of type :c:type:`dlist_node`
 * @param head: the head node of the list
 */
#define dlist_for_each(it, head) \
	for (it = (head)->next; it != (head); it = it->next)


/**
 * Get the containing struct of a dlist_node
 * 
 * @param ptr: the pointer to the dlist_node
 * @param type: the type of the container struct the dlist_node is embedded in
 * @param member: the name of the dlist_node member within the container struct
 */
#define dlist_get_container(ptr, type, member) \
    (type *)((char*)ptr - offsetof(type, member))

/**
 * Iterate over all containers of the elements of the list
 * @param pos:    the type * to use as a loop cursor.
 * @param head:   the head for your list.
 * @param member: the name of the list_struct within the struct.
 */
#define dlist_for_each_container(it, it_type, head, member)              \
    for (it = dlist_get_container((head)->next, it_type, member);  \
         &it->member != (head);    \
         it = dlist_get_container(it->member.next, it_type, member))

#endif
