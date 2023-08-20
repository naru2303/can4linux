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
***             --- PUBLIC MACROS 
*****************************************************************************************
****************************************************************************************/

/*****************************************************************************************
*****************************************************************************************
***             --- PUBLIC DEFINES  
*****************************************************************************************
****************************************************************************************/

/*****************************************************************************************
*****************************************************************************************
***             --- PUBLIC DATATYPES  
*****************************************************************************************
****************************************************************************************/

// Add Logging Print with colors 
// Add Log Queue using ringbuffer class
// Logging Hisory manager for RAM or EEPROM          
#define     LOG_EVENT_INFO       0x01U 
#define     LOG_EVENT_WARN       0x02U 
#define     LOG_EVENT_FATAL      0x04U 
#define     LOG_EVENT_DEBUG      0x08U
#define     LOG_EVENT_TRACE      0x10U
#define     LOG_EVENT_ALL        (LOG_EVENT_INFO | LOG_EVENT_WARN | LOG_EVENT_FATAL | LOG_EVENT_DEBUG | LOG_EVENT_TRACE) 

typedef u8 logging_type;  

typedef struct event_logger_t
{
    /* data */
};

typedef event_logger_t event_logger; 

typedef event_logger_t* event_logger_ptr;

#ifdef __EVENT_LOGGER_H_

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



/*****************************************************************************************
*****************************************************************************************
***             --- PRIVATE FUNCTIONS
*****************************************************************************************
****************************************************************************************/
#else 



#endif /* __EVENT_LOGGER_H_ */




#ifdef __EVENT_LOGGER_H_

/*****************************************************************************************
*****************************************************************************************
***             -- VARIABLES   
*****************************************************************************************
****************************************************************************************/

/*****************************************************************************************
*****************************************************************************************
***             -- PRIVATE MACROS    
*****************************************************************************************
****************************************************************************************/
#else 


#endif /* __EVENT_LOGGER_H_ */