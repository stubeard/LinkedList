#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

/*
 *  Title:   linkedlist.h
 *  Author:  Stu Beard
 *  Version: 01.1
 */

/*
 *  Macro:   LINKED_LIST_INITIALISE
 *  -------------------------------
 *  Creates all the functions required for a linked list of the given type.
 *  
 *  Parameters:
 *      suffix  a text string to be appended to the functions and structs to differtiate
 *              them from other linked lists.
 *      type    the type of the data items to be stored in the linked list.
 *
 */\
#define LINKED_LIST_INITIALISE(suffix, type) \
typedef struct node_##suffix##_t\
{\
    type data;\
    struct node_##suffix##_t *next;\
} node_##suffix##_t;\
typedef struct linkedlist_##suffix##_t\
{\
    node_##suffix##_t *first;\
    sem_t mutex;\
} linkedlist_##suffix##_t;\
/*
 *  Function Type:   linkedlist_format_##suffix##_t
 *  -----------------------------------------------
 *  Returns a formatted string represention of an item.
 *  
 *  Parameters:
 *      *buffer a pointer to a buffer to hold the formatted string. 
 *      *data   a ponter to the item to be formatted.
 *
 *  Returns:    a bool indicating whether the item was inserted successfully.
 *
 */\
typedef char *linkedlist_format_##suffix##_t( char *buffer, type* data );\
/*
 *  Function Type:   linkedlist_compare_##suffix##_t
 *  ------------------------------------------------
 *  Compares 2 items,
 *  
 *  Parameters:
 *      *data1  a ponter to the first item to be compared.
 *      *data2  a ponter to the second item to be compared.
 *
 *  Returns:    -1 if data1<data2, 1 if data1>data2, and 0 if data1-data2,
 *
 */typedef int linkedlist_compare_##suffix##_t( type *data1, type *data2 );\
/*
 *  Function:   linkedlist_initialise_##suffix
 *  ------------------------------------------
 *  Initialises the linkedlist_##suffix##_t struct.
 *  
 *  Parameters:
 *      *list   a pointer to the linkedlist_##suffix##_t to be initialised.
 *
 */\
void linkedlist_initialise_##suffix( linkedlist_##suffix##_t *list )\
{\
    if( list )\
    {\
        memset( list, 0, sizeof( linkedlist_##suffix##_t ) );\
        sem_init( &list->mutex, 0, 1 );\
    }\
}\
/*
 *  Function:   linkedlist_add_##suffix
 *  -----------------------------------
 *  Adds a new item to the end of the linkedlist_add_##suffix.
  *  
 *  Parameters:
 *      *list   a pointer to the linkedlist_##suffix##_t.
 *      data    the item to be added to the list.
 *
 *  Returns:    a bool indicating whether the item was added successfully.
 *
 */\
bool linkedlist_add_##suffix( linkedlist_##suffix##_t *list, type data )\
{\
    if( list )\
    {\
        sem_wait( &list->mutex );\
        node_##suffix##_t **node_ptr_ptr = &list->first;\
        while( *node_ptr_ptr )\
        {\
            node_ptr_ptr = &(*node_ptr_ptr)->next;\
        }\
        if( ( (*node_ptr_ptr) = malloc( sizeof( node_##suffix##_t ) ) ) )\
        {\
            memset( (*node_ptr_ptr), 0, sizeof( node_##suffix##_t ) );\
            (*node_ptr_ptr)->data = data;\
            sem_post( &list->mutex );\
            return true;\
        }\
        sem_post( &list->mutex );\
    }\
    return false;\
}\
/*
 *  Function:   linkedlist_remove_##suffix
 *  --------------------------------------
 *  Adds a new item to the end of the linkedlist_add_##suffix.
 *  
 *  Parameters:
 *      *list   a pointer to the linkedlist_##suffix##_t.
 *      index   the index of the item to be removed from the list.
 *
 *  Returns:    the item at the requested index, or an array of bytes 
 *              with sizeof type initialised to 0. 
 *
 */\
type linkedlist_remove_##suffix( linkedlist_##suffix##_t *list, unsigned int index )\
{\
    type data;\
    memset( &data, 0, sizeof( type ) );\
    if( list )\
    {\
        sem_wait( &list->mutex );\
        node_##suffix##_t **node_ptr_ptr = &list->first;\
        unsigned int i = 0;\
        while( ( *node_ptr_ptr ) && ( i < index ) )\
        {\
            node_ptr_ptr = &(*node_ptr_ptr)->next;\
            ++i;\
        }\
        if( *node_ptr_ptr )\
        {\
            node_##suffix##_t *node_ptr = ( *node_ptr_ptr );\
            ( *node_ptr_ptr ) = ( *node_ptr_ptr )->next;\
            data = node_ptr->data;\
            free( node_ptr );\
        }\
        sem_post( &list->mutex );\
    }\
    return data;\
}\
/*
 *  Function:   linkedlist_size_##suffix
 *  ------------------------------------
 *  Returns the size of the linkedlist_add_##suffix.
 *
 *  Parameters:
 *      *list   a pointer to the linkedlist_##suffix##_t.
 *
 *  Returns:    the number of nodes in the linkedlist_add_##suffix.
 *
 */\
unsigned int linkedlist_size_##suffix( linkedlist_##suffix##_t *list )\
{\
    unsigned int size = 0;\
    if( list )\
    {\
        sem_wait( &list->mutex );\
        node_##suffix##_t **node_ptr_ptr = &list->first;\
        while( *node_ptr_ptr )\
        {\
            node_ptr_ptr = &(*node_ptr_ptr)->next;\
            ++size;\
        }\
        sem_post( &list->mutex );\
    }\
    return size;\
}\
/*
 *  Function:   linkedlist_get_##suffix
 *  -----------------------------------
 *  Retrieves but does not remove an item from the linkedlist_##suffix##_t.
 *  
 *  Parameters:
 *      *list   a pointer to the linkedlist_##suffix##_t.
 *      index   the index of the item to be retrieved from the list.
 *
 *  Returns:    the item at the requested index, or an array of bytes 
 *              with size set to sizeof(type) and initialised to 0. 
 *
 */\
type linkedlist_get_##suffix( linkedlist_##suffix##_t *list, unsigned int index )\
{\
    type data;\
    memset( &data, 0, sizeof( type ) );\
    if( list )\
    {\
        sem_wait( &list->mutex );\
        node_##suffix##_t * node_ptr = list->first;\
        unsigned int i = 0;\
        while( ( node_ptr ) && ( i < index ) )\
        {\
            node_ptr = node_ptr->next;\
            ++i;\
        }\
        if( node_ptr )\
        {\
            data = node_ptr->data;\
        }\
        sem_post( &list->mutex );\
    }\
    return data;\
}\
/*
 *  Function:   linkedlist_set_##suffix
 *  -----------------------------------
 *  Sets the value of the item at the requested index in the linkedlist_##suffix.
 *   
 *  Parameters:
 *      *list   a pointer to the linkedlist_##suffix##_t.
 *      index   the index of the item to be updated in the list.
 *      data    the value to which the item at the requested index should be set to.
 *
 *  Returns:    the previous value of the item at the requested index, or 
 *              an array of bytes with size set to sizeof(type) and initialised to 0.
 *
 */\
type linkedlist_set_##suffix( linkedlist_##suffix##_t *list, unsigned int index, type data )\
{\
    type old_data;\
    memset( &old_data, 0, sizeof( type ) );\
    if( list )\
    {\
        sem_wait( &list->mutex );\
        node_##suffix##_t *node_ptr = list->first;\
        unsigned int i = 0;\
        while( ( node_ptr ) && ( i < index ) )\
        {\
            node_ptr = node_ptr->next;\
            ++i;\
        }\
        if( node_ptr )\
        {\
            old_data = node_ptr->data;\
            node_ptr->data = data;\
        }\
        sem_post( &list->mutex );\
    }\
    return old_data;\
}\
/*
 *  Function:   linkedlist_insert_##suffix
 *  --------------------------------------
 *  Inserts an item into the linked list at the requested index.
 *  
 *  Parameters:
 *      *list   a pointer to the linkedlist_##suffix##_t.
 *      index   the index where the item is to be inserted in the list.
 *      data    the item to be inserted into the list.
 *
 *  Returns:    a bool indicating whether the item was inserted successfully.
 *
 */\
bool linkedlist_insert_##suffix( linkedlist_##suffix##_t *list, unsigned int index, type data )\
{\
    if( list )\
    {\
        sem_wait( &list->mutex );\
        node_##suffix##_t **node_ptr_ptr = &list->first;\
        unsigned int i = 0;\
        while( ( *node_ptr_ptr ) && ( i < index ) )\
        {\
            node_ptr_ptr = &(*node_ptr_ptr)->next;\
            ++i;\
        }\
        node_##suffix##_t *next_node_ptr = *node_ptr_ptr;\
        if( ( (*node_ptr_ptr) = malloc( sizeof( node_##suffix##_t ) ) ) )\
        {\
            memset( (*node_ptr_ptr), 0, sizeof( node_##suffix##_t ) );\
            (*node_ptr_ptr)->data = data;\
            (*node_ptr_ptr)->next = next_node_ptr;\
            sem_post( &list->mutex );\
            return true;\
        }\
        sem_post( &list->mutex );\
    }\
    return false;\
}\
/*
 *  Function:   linkedlist_print_##suffix
 *  -------------------------------------
 *  Prints the contents of the linkedlist_##suffix.
 *  
 *  Parameters:
 *      *list                   a pointer to the linkedlist_##suffix##_t to be printed.
 *      linkedlist_format_fn    a pointer to a function which returns an item as a formatted string.
 *
 */\
void linkedlist_print_##suffix( linkedlist_##suffix##_t *list, linkedlist_format_##suffix##_t linkedlist_format_fn )\
{\
    if( ( list ) && ( linkedlist_format_fn ) )\
    {\
        sem_wait( &list->mutex );\
        /*printf( "list=[" );*/\
        node_##suffix##_t *node_ptr = list->first;\
        char buffer[ 256 ];\
        while( node_ptr )\
        {\
            printf( "%s", linkedlist_format_fn( buffer, &node_ptr->data ) );\
            node_ptr = node_ptr->next;\
            if( node_ptr )\
            {\
                printf( " " );\
            }\
        }\
        printf( "\n" );\
        sem_post( &list->mutex );\
    }\
}\
/*
 *  Function:   linkedlist_reverse_##suffix
 *  ---------------------------------------
 *  Reverses the order of the items in the linkedlist_##suffix.
 *  
 *  Parameters:
 *      *list   a pointer to the linkedlist_##suffix##_t to be reversed.
 *
 */\
void linkedlist_reverse_##suffix( linkedlist_##suffix##_t *list )\
{\
    if( list )\
    {\
        sem_wait( &list->mutex );\
        if(list->first)\
        {\
            node_##suffix##_t *current_node_ptr = list->first;\
            node_##suffix##_t *next_node_ptr    = current_node_ptr->next;\
            /*clear the next pointer for the first node*/\
            current_node_ptr->next = NULL;\
            while( ( current_node_ptr ) && ( next_node_ptr ) )\
            {\
                /*store the next address*/\
                node_##suffix##_t *next_next_node_ptr = next_node_ptr->next;\
                /*point the next node at the current one*/\
                next_node_ptr->next = current_node_ptr;\
                current_node_ptr = next_node_ptr;\
                next_node_ptr = next_next_node_ptr;\
            }\
            /*loop ends when next_node_ptr is NULL, at which point current_node_ptr
              points to the last node in the list, so set list->first to that.*/\
            list->first = current_node_ptr;\
        }\
        sem_post( &list->mutex );\
    }\
}\
/*
 *  Function:   linkedlist_compare_##suffix
 *  ---------------------------------------
 *  Compares the contents of two linkedlist_##suffix lists.
 *  
 *  Parameters:
 *      *list1                  a pointer to the first linkedlist_##suffix##_t to be compared.
 *      *list2                  a pointer to the second linkedlist_##suffix##_t to be compared.
 *      linkedlist_compare_fn   a pointer to a function which compares 2 items.
 *
 *  Returns:    true if the contents of the linked list are identical, false otherwise.
 *
 */\
bool linkedlist_compare_##suffix( linkedlist_##suffix##_t *list1, linkedlist_##suffix##_t *list2, linkedlist_compare_##suffix##_t linkedlist_compare_fn )\
{\
    if( ( list1 ) && ( list2 ) && ( linkedlist_compare_fn ) )\
    {\
        sem_wait( &list1->mutex );\
        sem_wait( &list2->mutex );\
        node_##suffix##_t **list1_node_ptr_ptr = &list1->first;\
        node_##suffix##_t **list2_node_ptr_ptr = &list2->first;\
        while( ( *list1_node_ptr_ptr ) && ( *list2_node_ptr_ptr ) )\
        {\
            if( linkedlist_compare_fn( &(*list1_node_ptr_ptr)->data,\
                                       &(*list2_node_ptr_ptr)->data ) )\
            {\
                sem_post( &list2->mutex );\
                sem_post( &list1->mutex );\
                return false;\
            }\
            list1_node_ptr_ptr = &(*list1_node_ptr_ptr)->next;\
            list2_node_ptr_ptr = &(*list2_node_ptr_ptr)->next;\
        }\
        if( ( *list1_node_ptr_ptr ) || ( *list2_node_ptr_ptr ) )\
        {\
            sem_post( &list2->mutex );\
            sem_post( &list1->mutex );\
            return false;\
        }\
        sem_post( &list2->mutex );\
        sem_post( &list1->mutex );\
        return true;\
    }\
    else\
    {\
        return( ( ! list1 ) && ( ! list2 ) );\
    }\
}\
/*
 *  Function:   linkedlist_sort_##suffix
 *  ------------------------------------
 *  Sorts the contents of linkedlist_##suffix##_t struct into ascending order.
 *  
 *  Parameters:
 *      *list                   a pointer to the linkedlist_##suffix to be sorted.
 *      linkedlist_compare_fn   a pointer to a function which compares 2 items.
 *
 */\
void linkedlist_sort_##suffix( linkedlist_##suffix##_t *list, linkedlist_compare_##suffix##_t linkedlist_compare_fn )\
{\
    if( ( list ) && ( linkedlist_compare_fn ) )\
    {\
        sem_wait( &list->mutex );\
        node_##suffix##_t **node_ptr_ptr = &list->first;\
        while( ( *node_ptr_ptr ) && ( *node_ptr_ptr )->next )\
        {\
            if( linkedlist_compare_fn( &(*node_ptr_ptr)->data, &(*node_ptr_ptr)->next->data) > 0 )\
            {\
               node_##suffix##_t *node1 = (*node_ptr_ptr)->next;\
               node_##suffix##_t *node2 = (*node_ptr_ptr)->next->next;\
               (*node_ptr_ptr)->next->next = (*node_ptr_ptr);\
               (*node_ptr_ptr)->next = node2;\
               (*node_ptr_ptr) = node1;\
               node_ptr_ptr = &list->first;\
            }\
            else\
            {\
                node_ptr_ptr = &( *node_ptr_ptr )->next;\
            }\
        }\
        sem_post( &list->mutex );\
    }\
}\
/*
 *  Function:   linkedlist_push_##suffix
 *  ------------------------------------
 *  Pushes an item onto the beginning of the linkedlist_##suffix.
 *  
 *  Parameters:
 *      *list   a pointer to the linkedlist_##suffix.
 *      data    the item to be pushed onto the list.
 *
 *  Returns:    a bool indicating whether the item was inserted successfully.
 *
 */\
bool linkedlist_push_##suffix( linkedlist_##suffix##_t *list, type data )\
{\
    return linkedlist_insert_##suffix( list, 0, data );\
}\
/*
 *  Function:   linkedlist_pop_##suffix
 *  -----------------------------------
 *  Pops and removes the first item in the linkedlist_##suffix.
 *  
 *  Parameters:
 *      *list   a pointer to the linkedlist_##suffix.
 *
 *  Returns:    the first item in the list.
 *
 */\
type linkedlist_pop_##suffix( linkedlist_##suffix##_t *list )\
{\
    return linkedlist_remove_##suffix( list, 0 );\
}\
/*
 *  Function:   linkedlist_poll_##suffix
 *  ------------------------------------
 *  Polls and removes the last item in the linkedlist_##suffix.
 *  
 *  Parameters:
 *      *list   a pointer to the linkedlist_##suffix.
 *
 *  Returns:    the last item in the list.
 *
 */\
type linkedlist_poll_##suffix( linkedlist_##suffix##_t *list )\
{\
    unsigned int index = linkedlist_size_##suffix( list );\
    return linkedlist_remove_##suffix( list, index ? index - 1 : 0 );\
}\
/*
 *  Function:   linkedlist_peek_##suffix
 *  ------------------------------------
 *  Returns but does not remove the first item in the linkedlist_##suffix.
 *  
 *  Parameters:
 *      *list   a pointer to the linkedlist_##suffix.
 *
 *  Returns:    the first item in the list.
 *
 */\
type linkedlist_peek_##suffix( linkedlist_##suffix##_t *list )\
{\
    return linkedlist_get_##suffix( list, 0 );\
}

#endif //__LINKED_LIST_H__
