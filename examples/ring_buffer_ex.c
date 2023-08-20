
#include <stdio.h> 
#include <string.h>

#include "utils.h"
#include "ring_buffer.h"

#define SOMETHING_WENT_WRONG(__X) do {  if( (__X) == false )  { printf("Something is Wrong!!\n");} } while (0)     

int main() 
{ 
    char buffer[1024U] = {0U}; 
    u16 s = 30;
    ring_buffer ring_stack; 
    ring_buffer_ptr ring_obj = &ring_stack ; 

    u8 data[30U];
    u8 data2[20U];
    u8 data3[20U]; 

    memset(&data[0], 0xAAU, 30);
    memset(&data2[0], 0xBBU, 20);

    ring_init(ring_obj, 2, &buffer[0], s);

    SOMETHING_WENT_WRONG(ring_insert(ring_obj, &data[0]));

    ring_dump_data(ring_obj); 

    SOMETHING_WENT_WRONG(ring_insert(ring_obj, &data2[0]));

    ring_dump_data(ring_obj); 

    SOMETHING_WENT_WRONG(ring_remove(ring_obj, &data3[0U])); 

    ring_dump_data(ring_obj);

    printf("Data Read: ");
    for(u16 i=0U; i<s; ++i)
    {
        printf("%x ", data3[i]);
    }

    printf("\n");

    ring_destruct(&ring_obj);

    printf("test %x", buffer[31]);

    return 0; 
}