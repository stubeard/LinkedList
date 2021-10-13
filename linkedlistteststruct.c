#include "linkedlist.h"
#include <stdbool.h>

// type must be declared before initialising the linkedlist
typedef struct struct_string_s
{
    char string[ 32 ];
} struct_string_t;

LINKED_LIST_INITIALISE( struct, struct_string_t )

int sort_ascending( struct_string_t *data1, struct_string_t *data2 )
{
    return( strcmp( data1->string, data2->string ) );
}

int sort_descending( struct_string_t *data1, struct_string_t *data2 )
{
    return( -strcmp( data1->string, data2->string ) );
}


char *format( char *buffer, struct_string_t *data )
{
    memset( buffer, 0, sizeof( buffer ) );
    if( data )
    {
        sprintf( buffer, "%s", data->string );
    }
    return buffer;
}


int main(int argc, char *argv[])
{
    linkedlist_struct_t list_of_structs1;
    linkedlist_struct_t list_of_structs2;
    
    linkedlist_initialise_struct( &list_of_structs1 );
    linkedlist_initialise_struct( &list_of_structs2 );
    
    struct_string_t structs1[ 9 ];
    struct_string_t structs2[ 9 ];
    
    char *strings1[] = { "nine", "one", "two", "eight", "three", "seven", "four", "five", "six" }; 
    char *strings2[] = { "one", "seven", "eight", "three", "two", "four", "five", "six", "nine" }; 
    
    for( int i = 0 ; i < 9 ; ++i )
    {
        strcpy( structs1[ i ].string, strings1[ i ] );    
        strcpy( structs2[ i ].string, strings2[ i ] );    
    }

    for( int i = 0 ; i < 9 ; ++i )
    {
        linkedlist_add_struct( &list_of_structs1, structs1[ i ] );
        linkedlist_push_struct( &list_of_structs2, structs2[ i ] );
    }
    
    linkedlist_sort_struct( &list_of_structs1, &sort_ascending );
    linkedlist_sort_struct( &list_of_structs2, &sort_descending );
    
    linkedlist_reverse_struct( &list_of_structs2 );
    
    linkedlist_print_struct( &list_of_structs1, &format );
    linkedlist_print_struct( &list_of_structs1, &format );
    
    bool result = linkedlist_compare_struct( &list_of_structs1, &list_of_structs2, &sort_ascending );
    
    printf( "%s\n", result ? "Passed" : "Failed" );
    
    return !result;
}
