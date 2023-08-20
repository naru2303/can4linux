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



#ifndef __VISIBILITY_H_
#define __VISIBILITY_H_


#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define CAN4LIN_EXPORT __attribute__ ((dllexport))
    #define CAN4LIN_IMPORT __attribute__ ((dllimport))
  #else
    #define CAN4LIN_EXPORT __declspec(dllexport)
    #define CAN4LIN_IMPORT __declspec(dllimport)
  #endif
  #ifdef CAN4LIN_BUILDING_LIBRARY
    #define CAN4LIN_PUBLIC CAN4LIN_EXPORT
  #else
    #define CAN4LIN_PUBLIC CAN4LIN_IMPORT
  #endif
  #define CAN4LIN_PUBLIC_TYPE CAN4LIN_PUBLIC
  #define CAN4LIN_LOCAL
#else
  #define CAN4LIN_EXPORT __attribute__ ((visibility("default")))
  #define CAN4LIN_IMPORT
  #if __GNUC__ >= 4
    #define CAN4LIN_PUBLIC __attribute__ ((visibility("default")))
    #define CAN4LIN_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define CAN4LIN_PUBLIC
    #define CAN4LIN_LOCAL
  #endif
  #define CAN4LIN_PUBLIC_TYPE
#endif


#endif /*   __VISIBILITY_H_   */