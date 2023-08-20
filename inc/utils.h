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



/*****************************************************************************************
*****************************************************************************************
***             --- Custom Data Types 
*****************************************************************************************
****************************************************************************************/

typedef unsigned char u8; 
typedef unsigned short int u16; 
typedef unsigned long int u32; 
typedef unsigned long long int u64; 

typedef signed char s8; 
typedef short int s16; 
typedef long int s32; 
typedef long long int s64; 

typedef float f32; 
typedef double f64; 

typedef unsigned char __boolean; 


/*****************************************************************************************
*****************************************************************************************
***             --- LIMITS 
*****************************************************************************************
****************************************************************************************/

#define MAX_U8  
#define MAX_16
#define MAX_U32
#define MAX_U64
 
 /*****************************************************************************************
*****************************************************************************************
***             --- MACROS 
*****************************************************************************************
****************************************************************************************/

#define CONVERT_BCD_BIN(__X)                        ((((__X) >> 4U) & 0x0FU) * 10U + ((__X) & 0x0FU))
#define CONVERT_BIN_BCD(__X)                        ((((__X) / 10U) << 4U) | ((__X) % 10U))

#define INCR_WITH_SATURATION(__X)                   ((__X) = ((((__X) + 1U) < (__X))   ? (__X)   : ((__X) + 1U) ))
#define INCR_WITH_SATURATION_LIM(__X, __LIM)        ((__X) = ((((__X) + 1U) > (__LIM)) ? (__X)   : ((__X) + 1U) ))
#define DECR_WITH_SATURATION(__X)                   ((__X) = ((((__X) - 1U) > (__X))   ? (__X)   : ((__X) - 1U) ))
#define DECR_WITH_SATURATION_LIM(__X, __LIM)        ((__X) = (((__X) > 0U) && ((__X) > (__LIM)) ? (__X) - 1U) : (__X))

#define SWAP16(__X)                                 ((((__X) >> 8)  & 0x00FF)     | (((__X) << 8) & 0xFF00))
#define SWAP32(__X)                                 ((((__X) >> 24) & 0x000000FF) | (((__X) >> 8) & 0x0000FF00) | \
                                                    (((__X) << 8)   & 0x00FF0000) | (((__X) << 24) & 0xFF000000))

#define BYTE_8(__X)                                 ((u8) ((__X)  & 0x00FFU))
#define BYTE_16(__X)                                ((u8) (((__X) & 0xFF00U) >> 8U))
#define BYTE_32(__X)                                ((u8) (((__X) & 0xFF0000U) >> 16U))

#define GET_MIN(__X, __Y)                           (((__X) < (__Y)) ? (__X) : (__Y)) 
#define GET_MAX(__X, __Y)                           (((__X) > (__Y)) ? (__X) : (__Y)) 

#define GET_ABS(__X)                                (((__X) < 0U) ? (-__X) : (__X))
 
#define TRUE 1U 
#define FALSE 0U 

#define true TRUE
#define false FALSE

#define NULLPTR (void*) 0

//TODO add some kind of assert 
#define CHECK_NULLPTR_RET(__X)                          do {  if( (__X) == NULLPTR )     return false; } while (0)                                         
                                                     
#define CHECK_NULLPTR_VOID(__X)                          do {  if( (__X) == NULLPTR )     return; } while (0)     


 /*****************************************************************************************
*****************************************************************************************
***             --- INLINE UTILS FUNCS 
*****************************************************************************************
****************************************************************************************/



/**
 * @name    void ring_destruct(ring_buffer** const me)
 * 
 * @brief   Frees and destroys the memory either allocated on heap or stack
 * 
 * @param   ring_buffer** const: pointer to the object pointer of the rb struct
 * 
 * @return  none.
 */
inline static void utils_cpu_relax(void)
{
#if defined(__x86_64__) || defined(__i386__)
  asm volatile("pause" ::: "memory");
#else
#error "Extend for other architectures ..."
#endif
}

#define MAX_NUMBER_MODULES    64U
#define UNDEFINED_MODULE_ID   0xFFU

static char * __module_names[MAX_NUMBER_MODULES] = { NULLPTR }; 
static u8     __modules_ids[MAX_NUMBER_MODULES] = { 0U };
static u8     place_holder = 0U; 
static u8     free_place_holder = UNDEFINED_MODULE_ID; 


/**
 * @name    void ring_destruct(ring_buffer** const me)
 * 
 * @brief   Frees and destroys the memory either allocated on heap or stack
 * 
 * @param   ring_buffer** const: pointer to the object pointer of the rb struct
 * 
 * @return  none.
 */
inline static u8 utils_register_module(char * const __module_name, u8 const __id)
{
  u8 ret = (free_place_holder == UNDEFINED_MODULE_ID) ? place_holder : free_place_holder;
  __module_names[ret] = __module_name; 
  __modules_ids[ret] = __id; 
  if (free_place_holder == UNDEFINED_MODULE_ID)
  {
    INCR_WITH_SATURATION(place_holder);
  }
  free_place_holder = UNDEFINED_MODULE_ID;
  return ret; 
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
inline static void utils_remove_module_registration(u8 __pos)
{
  __module_names[__pos] = NULLPTR; 
  __modules_ids[__pos] = UNDEFINED_MODULE_ID;
  free_place_holder = __pos;
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
inline static char * utils_get_registered_module_name(u8 __pos)
{
  return __module_names[__pos]; 
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
inline static u8 utils_get_registered_module_id(u8 __pos)
{
  return __modules_ids[__pos];
}
