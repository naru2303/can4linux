#ifdef RUNNING_OS
#include <stdio.h>
#endif /* RUNNING_OS  */
#include "utils.h"

#define __RING_BUFFER_H_
#include "ring_buffer.h"

/**
 * @name    void ring_init(ring_buffer* const me)
 * 
 * @brief   Initialize a ringbuffer object and set it up for usage.
 * 
 * @param   ring_buffer* const : object pointer to the struct.
 * 
 * @return  none.
 */
void ring_init(ring_buffer* const me, u8 __id, u8 * __link_buf, u16 size)
{
    CHECK_NULLPTR_VOID(me);

    if (RING_BUFFER_IS_POWER_OF_TWO(size) == true) 
    { 
        return; 
    }

    module_position = utils_register_module(RING_MODULE_NAME, __id);

    me->buf_size = size; 
    u8*  ptr = __link_buf;

    while(size--)
    {   
        *ptr++ = 0U; 
    }

    me->buffer = __link_buf;
    me->entries = 0U; 
    me->head = 0U; 
    me->tail = 0U;
    max_num_entries_bytes = size * RING_BUFFER_MAX_ENTRIES;
    
    return;
}


/**
 * @name    void ring_destruct(ring_buffer** const me)
 * 
 * @brief   Frees and destroys the memory either allocated on heap or stack
 * 
 * @param   ring_buffer** const: pointer to the object pointer of the rb struct
 * 
 * @return  none.
 */
void ring_destruct(ring_buffer** const me)
{
    CHECK_NULLPTR_VOID(me);

    utils_remove_module_registration(module_position);

    *me = NULLPTR; 

    return;
}


/**
 * @name    __boolean ring_insert(ring_buffer* const me, u8 const * const data_write, u16 size)
 * 
 * @brief   insert data into the ringbuffer 
 * 
 * @param   ring_buffer* const : object pointer to the struct.
 *          u8 const * const   : data to insert into the ringbuffer 
 *          u16 size           : size of the data to be inserted into the ringbuffer 
 * @return  __bolean           : true if success, false if something went wrong.
 */
__boolean ring_insert(ring_buffer* const me, u8 const * const data_write)
{
    CHECK_NULLPTR_RET(me);

    if (ring_full(me) == true)
    {
        // should not be false, should write on tail instead of head 
        return false; 
    }

    ring_copy_data(&me->buffer[me->head], (u8 const*) data_write, me->buf_size);

    me->head = me->head + me->buf_size;
    INCR_WITH_SATURATION(me->entries);
    if (me->head >= max_num_entries_bytes)
    {
        me->head = 0U; 
    }

    return true; 
}


/**
 * @name        __boolean ring_remove(ring_buffer* const me, u8 * const data_read, u16 * size)
 * 
 * @brief       removes data from the ringbuffer (latest insert)
 * 
 * @param       ring_buffer* const : object pointer to the struct.
 *              u8 * const         : ptr where the data should be read and saved
 *              u16 *              : the expected size 
 * @return      __bolean           : true if success, false if something went wrong.
 */
__boolean ring_remove(ring_buffer* const me, u8 * const data_read)
{
    CHECK_NULLPTR_RET(me);

    if (ring_empty(me) == true)
    {
        return false; 
    }   

    ring_copy_data((u8*) data_read, (u8 const*) &me->buffer[me->tail], me->buf_size);


    me->tail = me->tail + me->buf_size; 
    DECR_WITH_SATURATION(me->entries); 
    if (me->tail >= max_num_entries_bytes)
    {
        me->tail = 0U;
    }
    
    
    return true; 
}


/**
 * @name    __boolean ring_get_data_newest(ring_buffer const * const me, u8 * const data_read, u16 * size)
 * 
 * @brief   getter for the latest data added to the ringbuffer (reading without chaning head and tail)
 * 
* @param       ring_buffer const * const : object pointer to the struct.
 *              u8 * const               : ptr where the data should be read and saved
 *              u16 *                    : the expected size 
 * @return      __bolean                 : true if success, false if something went wrong.
 */
__boolean ring_get_data_newest(ring_buffer const * const me, u8 * const data_read)
{
    CHECK_NULLPTR_RET(me);

    ring_copy_data((u8*) data_read, (u8 const*) &me->buffer[me->tail], me->buf_size);
    
    return true;
}


/**
 * @name    inline u8 ring_get_number_entries(ring_buffer const * const me)
 * 
 * @brief   returns the maximum number of entries 
 * 
 * @param   ring_buffer const * const : object pointer to the struct.
 *  
 * @return  u8 : number of entries returned
 */
inline u8 ring_get_number_entries(ring_buffer const * const me)
{
    CHECK_NULLPTR_RET(me);
    return me->entries; 
} 


/**
 * @name    __boolean ring_set_data_newest(ring_buffer* const me, u8 const * const data_write, u16 size)
 * 
 * @brief   sets the news data with other passed data
 * 
 * @param   ring_buffer* const : object ptr to the struct 
 *          const * const      : data to be set 
 *          u16                : size of the data
 * @return  __bolean           : true if success, false if something went wrong.
 */
__boolean ring_set_data_newest(ring_buffer* const me, u8 const * const data_write)
{
    CHECK_NULLPTR_RET(me);

    ring_copy_data(&me->buffer[me->head], (u8 const*) data_write, me->buf_size);
    
    return true;
}


/**
 * @name    void ring_erase_data(ring_buffer* const me)
 * 
 * @brief   resets the ringbuffer, fast process
 * 
 * @param   ring_buffer* const : object ptr to the struct 
 * 
 * @return  none.
 */
void ring_erase_data(ring_buffer* const me)
{
    CHECK_NULLPTR_VOID(me);

    me->head = 0U;
    me->tail = 0U;  
    me->entries = 0U; 
    me->buf_size = 0U;
    me->buffer = NULLPTR;
    
    return;
}


/**
 * @name Base for all architecture implementation classes.
 * 
 * @brief
 * 
 * @param
 * 
 * @return
 */
u8 const ring_get_module_position(void)
{ 
    return module_position;
}


#ifdef RUNNING_OS
/**
 * @name Base for all architecture implementation classes.
 * 
 * @brief
 * 
 * @param
 * 
 * @return
 */
void ring_dump_data(ring_buffer const * const me)
{ 
    char * module_name = utils_get_registered_module_name(module_position); 
    u8     id          = utils_get_registered_module_id(module_position);
    printf("+++Dumping Data of+++ : %s with ID %d\n", module_name, id);
    printf("Head   -> %d\n", me->head);
    printf("Tail   -> %d\n", me->tail);
    printf("Entries-> %d\n", me->entries);
    u8 tracker = 0U; 
    u8 pos = 0U;
    u8 i = 0U;
    if(me->entries > 0)
    {
        while(tracker < me->entries)
        {
            printf("Data-> %d: ", tracker);
            for(i=pos; i<me->buf_size; ++i)
            {
                printf("%x ", me->buffer[i]);
            }
            printf("\n");
            INCR_WITH_SATURATION(tracker);
            pos += me->buf_size;
        }
    }
   return; 
}
#endif /* RUNNING_OS */


/**
 * @name Base for all architecture implementation classes.
 * 
 * @brief
 * 
 * @param
 * 
 * @return
 */
static inline __boolean ring_full(ring_buffer const * const me)
{
    return (me->entries == RING_BUFFER_MAX_ENTRIES);
}


/**
 * @name Base for all architecture implementation classes.
 * 
 * @brief
 * 
 * @param
 * 
 * @return
 */
static inline __boolean ring_empty(ring_buffer const * const me)
{
    return (me->entries == 0U);
}


/**
 * @name Base for all architecture implementation classes.
 * 
 * @brief
 * 
 * @param
 * 
 * @return
 */
static inline void ring_copy_data(u8* __dest, u8 const * __src, u16 size)
{
    while (size--) 
    {
        *__dest++ = *__src++;
    }
}