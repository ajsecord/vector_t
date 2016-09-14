/*
 Copyright 2016-present Adrian Secord. All Rights Reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#ifndef VECTOR_SYSTEM_H
#define VECTOR_SYSTEM_H

/**
 @file vector_system.h

 Interactions with the underlying system (optional).

 It is occasionally useful to control a library's interactions with the underlying runtime system,
 for example, memory allocation, printing error messages, etc. The vector_t library allows you to
 redefine the methods it uses for:

 - Memory allocation and deallocation,
 - Aborting in situations where the library can't continue, and,
 - Printing error messages.

 The functions in this file allow you to redefine these methods and provides the default functions
 vector_t uses. The default functions simply call the standard C99 functions, for example, @c
 vector_default_global_abort_func() calls @c abort().

 Everything in this file is optional and not needed for normal usage.
 */
 
#include <stdarg.h>
#include <stdio.h>

#include "vector.h"

/** A function that causes abnormal program termination, similar to abort(3). */
typedef void (*vector_abort_func_t)();

/** A function that frees memory allocations, similar to free(3). */
typedef void (*vector_free_func_t)(void *ptr);

/** A function that copies memory, similar to memcpy(3). */ 
typedef void *(*vector_memcpy_func_t)(void *restrict dst, const void *restrict src, size_t n);

/** A function that moves memory, similar to memmove(3). */
typedef void *(*vector_memmove_func_t)(void *dst, const void *src, size_t len);

/** A function that attempts to reallocate a memory block, similar to realloc(3). */
typedef void *(*vector_realloc_func_t)(void *ptr, size_t size);

/** A function that prints a formatted string to a stream with a variadic argument list, similar to vfprintf(3). */
typedef int (*vector_vfprintf_func_t)(FILE * restrict stream, const char * restrict format, va_list ap);

/**
 Return the library's abort() function.

 @return A function that acts like abort().
 */
VECTOR_EXTERN vector_abort_func_t vector_get_global_abort_func(void);

/**
 Set the library's abort() function.
 
 Called when something unrecoverable has happened, the function should never return to the caller.

 @param abort_func A function that acts like abort().
 */
VECTOR_EXTERN void vector_set_global_abort_func(const vector_abort_func_t abort_func);

/**
 The default library abort() function.
 
 This function simply calls the system abort() function.
 */
VECTOR_EXTERN void vector_default_global_abort_func();

/**
 Return the library's free() function.

 @return A function that acts like free().
 */
VECTOR_EXTERN vector_free_func_t vector_get_global_free_func(void);

/**
 Set the library's free() function.
 
 Called to deallocate memory previously allocated with @c vector_get_global_realloc_func.

 @param free_func A function that acts like free().
 */
VECTOR_EXTERN void vector_set_global_free_func(const vector_free_func_t free_func);

/**
 The default library free() function.
 
 This function simply calls the system free() function.
 */
VECTOR_EXTERN void vector_default_global_free_func(void *ptr);

/**
 Return the library's memcpy() function.

 @return A function that acts like memcpy().
 */
VECTOR_EXTERN vector_memcpy_func_t vector_get_global_memcpy_func(void);

/**
 Set the library's memcpy() function.
 
 Called to copy memory from one location to another.

 @param memcpy_func A function that acts like memcpy().
 */
VECTOR_EXTERN void vector_set_global_memcpy_func(const vector_memcpy_func_t memcpy_func);

/**
 The default library memcpy() function.
 
 This function simply calls the system memcpy() function.
 */
VECTOR_EXTERN void *vector_default_global_memcpy_func(void *restrict dst, const void *restrict src, size_t n);

/**
 Return the library's memmove() function.

 @return A function that acts like memmove().
 */
VECTOR_EXTERN vector_memmove_func_t vector_get_global_memmove_func(void);

/**
 Set the library's memmove() function.
 
 Called to move memory from one location to another.

 @param memmove_func A function that acts like memmove().
 */
VECTOR_EXTERN void vector_set_global_memmove_func(const vector_memmove_func_t memmove_func);

/**
 The default library memmove() function.
 
 This function simply calls the system memmove() function.
 */
VECTOR_EXTERN void *vector_default_global_memmove_func(void *dst, const void *src, size_t len);

/**
 Return the library's realloc() function.

 @return A function that acts like realloc().
 */
VECTOR_EXTERN vector_realloc_func_t vector_get_global_realloc_func(void);

/**
 Set the library's realloc() function.

 Called to attempt to change the allocation size of a block of memory, or allocate a new memory
 block. Memory allocated by this function will be deallocated by the function returned by
 @c vector_get_global_free_func().

 @param realloc_func A function that acts like realloc().
 */
VECTOR_EXTERN void vector_set_global_realloc_func(const vector_realloc_func_t realloc_func);

/**
 The default library realloc() function.
 
 This function simply calls the system realloc() function.
 */
VECTOR_EXTERN void *vector_default_global_realloc_func(void *ptr, size_t size);

/**
 Return the library's vfprintf() function.

 @return A function that acts like vfprintf().
 */
VECTOR_EXTERN vector_vfprintf_func_t vector_get_global_vfprintf_func(void);

/**
 Set the library's vfprintf() function.
 
 Called to format and print a string to a stream.

 @param vfprintf_func A function that acts like vfprintf().
 */
VECTOR_EXTERN void vector_set_global_vfprintf_func(const vector_vfprintf_func_t vfprintf_func);

/**
 The default library vfprintf() function.
 
 This function simply calls the system vfprintf() function.
 */
VECTOR_EXTERN int vector_default_global_vfprintf_func(FILE * restrict stream, const char * restrict format, va_list ap);

#endif
