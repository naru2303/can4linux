/*
Copyright (c) 2023 Houssem Chekili <houssem.chekili@outlook.de>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//TODO 
// Race Condition (support of mutex)
// Assert 
// correct entries and size from remove, now working as LIFO and not FIFO

/*****************************************************************************************
*****************************************************************************************
***             --- PUBLIC MACROS 
*****************************************************************************************
****************************************************************************************/

/*****************************************************************************************
*****************************************************************************************
***             --- PRIVATE MACROS 
*****************************************************************************************
******************/

#ifdef __RING_BUFFER_H_
    #define RING_BUFFER_IS_POWER_OF_TWO(__X) ((__X & (__X - 1)) == 0)
#endif /* __RING_BUFFER_H_ */
/*****************************************************************************************
*****************************************************************************************
***             --- PUBLIC DEFINES  
*****************************************************************************************
****************************************************************************************/

/*****************************************************************************************
*****************************************************************************************
***             -- PRIVATE DEFINES  
*****************************************************************************************
****************************************************************************************/
#ifdef __RING_BUFFER_H_
    #define RING_MODULE_NAME "RING_BUFFER"
#endif /*  __RING_BUFFER_H_   */

// Depending on the architecture, reserve a number of bytes. 
#ifdef BIG_MEM_PLATFORM
    #warning "Compiling for big memory platforms!"
    #define RING_BUFFER_MAX_ENTRIES  1024U
#else 
    #define RING_BUFFER_MAX_ENTRIES  64U
#endif /* BIG_MEM_PLATFORM */


/*****************************************************************************************
*****************************************************************************************
***             --- PUBLIC DATATYPES  
*****************************************************************************************
****************************************************************************************/

struct ring_buffer_t
{
    volatile u16 tail; 
    volatile u16 head; 
    volatile u16 entries; 
    
    u16 buf_size;
    u8* buffer;
};

typedef struct ring_buffer_t ring_buffer; 

typedef struct ring_buffer_t* ring_buffer_ptr; 

#ifdef __RING_BUFFER_H_

/*****************************************************************************************
*****************************************************************************************
***             --- PRIVATE DATATYPES  
*****************************************************************************************
****************************************************************************************/

/*****************************************************************************************
*****************************************************************************************
***             --- PUBLIC FUNCTIONS 
*****************************************************************************************
****************************************************************************************/

void ring_init(ring_buffer* const me, u8 __id, u8 * __link_buf, u16 size); 
void ring_destruct(ring_buffer** const me); 

__boolean ring_insert(ring_buffer* const me, u8 const * const data_write);
__boolean ring_remove(ring_buffer* const me, u8 * const data_read);

__boolean ring_get_data_newest(ring_buffer const * const me, u8 * const data_read); 
u8 ring_get_number_entries(ring_buffer const * const me); 
__boolean ring_set_data_newest(ring_buffer* const me, u8 const * const data_write); 

void ring_erase_data(ring_buffer* const me);

u8 const ring_get_module_position(void);

#ifdef RUNNING_OS 
void ring_dump_data(ring_buffer const * const me); 
#endif /* RUNNING_OS */

/*****************************************************************************************
*****************************************************************************************
***             --- PRIVATE FUNCTIONS
*****************************************************************************************
****************************************************************************************/

static inline __boolean ring_full(ring_buffer const * const me); 
static inline __boolean ring_empty(ring_buffer const * const me); 

// could be moved to utils
static inline void ring_copy_data(u8* __dest, u8 const * __src, u16 size);

#else 

extern void ring_init(ring_buffer* const me, u8 __id, u8 * __link_buf, u16 size);  
extern void ring_destruct(ring_buffer** const me); 

extern __boolean ring_insert(ring_buffer* const me, u8 const * const data_write);
extern __boolean ring_remove(ring_buffer* const me, u8 * const data_read);

extern __boolean ring_get_data_newest(ring_buffer const * const me, u8 * const data_read); 
extern u8 ring_get_number_entries(ring_buffer const * const me); 
extern __boolean ring_set_data_newest(ring_buffer* const me, u8 const * const data_write, u16 size); 

extern void ring_erase_data(ring_buffer* const me);

extern u8 const ring_get_module_position(void);

#ifdef RUNNING_OS 
#warning "Compiling for OS, STDOUT will be used!"
extern void ring_dump_data(ring_buffer const * const me); 
#endif /* RUNNING_OS */

#endif /* __RING_BUFFER_H_ */




#ifdef __RING_BUFFER_H_

/*****************************************************************************************
*****************************************************************************************
***             -- VARIABLES   
*****************************************************************************************
****************************************************************************************/

static u8  module_position = 0U; 
static u16 tail_position = 0U; 

static u16 max_num_entries_bytes = 0U; 
#else 



#endif /* __RING_BUFFER_H_ */

