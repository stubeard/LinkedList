#include "linkedlist.h"
#include <stdbool.h>

LINKED_LIST_INITIALISE( string, char * )

int sort_ascending( char **data1, char **data2 )
{
    return( strcmp( *data1, *data2 ) );
}

int sort_descending( char **data1, char **data2 )
{
    return( -strcmp( *data1, *data2 ) );
}


char *format( char *buffer, char **data )
{
    memset( buffer, 0, sizeof( buffer ) );
    if( data )
    {
        sprintf( buffer, "%s", *data );
    }
    return buffer;
}


int main(int argc, char *argv[])
{
    linkedlist_string_t list_of_strings1;
    linkedlist_string_t list_of_strings2;
    
    linkedlist_initialise_string( &list_of_strings1 );
    linkedlist_initialise_string( &list_of_strings2 );
    
    char *strings1[] = { "nine", "one", "two", "eight hundred", "three", "seven", "four", "five", "six" }; 
    char *strings2[] = { "one", "seven", "eight hundred", "three", "two", "four", "five", "six", "nine" }; 
    
    for( int i = 0 ; i < 9 ; ++i )
    {
        linkedlist_add_string( &list_of_strings1, strings1[ i ] );
        linkedlist_push_string( &list_of_strings2, strings2[ i ] );
    }
    
    linkedlist_sort_string( &list_of_strings1, &sort_ascending );
    linkedlist_sort_string( &list_of_strings2, &sort_descending );
    
    linkedlist_reverse_string( &list_of_strings2 );
    
    linkedlist_print_string( &list_of_strings1, &format );
    linkedlist_print_string( &list_of_strings2, &format );
    
    bool result = linkedlist_compare_string( &list_of_strings1, &list_of_strings2, &sort_ascending );
    
    printf( "%s\n", result ? "Passed" : "Failed" );
    
    return !result;
}
