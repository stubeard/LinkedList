#include "linkedlist.h"
#include <stdbool.h>

LINKED_LIST_INITIALISE( usint, unsigned short int )

int sort_ascending( unsigned short int *data1, unsigned short int *data2 )
{
    if( *data1 < *data2 )
    {
        return -1;
    }
    else if( *data1 > *data2 )
    {
        return 1;
    }
    return 0;
}

int sort_descending( unsigned short int *data1, unsigned short int *data2 )
{
    if( *data1 < *data2 )
    {
        return 1;
    }
    else if( *data1 > *data2 )
    {
        return -1;
    }
    return 0;
}


char *format( char *buffer, unsigned short int *data )
{
    memset( buffer, 0, sizeof( buffer ) );
    if( data )
    {
        sprintf( buffer, "%u", *data );
    }
    return buffer;
}


int main(int argc, char *argv[])
{
    linkedlist_usint_t list_of_usints1;
    linkedlist_usint_t list_of_usints2;
    
    linkedlist_initialise_usint( &list_of_usints1 );
    linkedlist_initialise_usint( &list_of_usints2 );
    
    unsigned short int usints1[] = { 9, 1, 2, 8, 3, 7, 4, 5, 6 }; 
    unsigned short int usints2[] = { 1, 7, 8, 3, 2, 4, 5, 6, 9 }; 
    
    for( int i = 0 ; i < 9 ; ++i )
    {
        linkedlist_add_usint( &list_of_usints1, usints1[ i ] );
        linkedlist_push_usint( &list_of_usints2, usints2[ i ] );
    }
    
    linkedlist_sort_usint( &list_of_usints1, &sort_ascending );
    linkedlist_sort_usint( &list_of_usints2, &sort_descending );
    
    linkedlist_reverse_usint( &list_of_usints2 );
    
    linkedlist_print_usint( &list_of_usints1, &format );
    linkedlist_print_usint( &list_of_usints2, &format );
    
    bool result = linkedlist_compare_usint( &list_of_usints1, &list_of_usints2, &sort_ascending );
    
    printf( "%s\n", result ? "Passed" : "Failed" );
    
    return !result;
}
