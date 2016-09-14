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

VECTOR_EXTERN vector_abort_func_t vector_get_global_abort_func(void);
VECTOR_EXTERN void vector_set_global_abort_func(const vector_abort_func_t abort_func);
VECTOR_EXTERN void vector_default_global_abort_func();

VECTOR_EXTERN vector_free_func_t vector_get_global_free_func(void);
VECTOR_EXTERN void vector_set_global_free_func(const vector_free_func_t free_func);
VECTOR_EXTERN void vector_default_global_free_func(void *ptr);

VECTOR_EXTERN vector_memcpy_func_t vector_get_global_memcpy_func(void);
VECTOR_EXTERN void vector_set_global_memcpy_func(const vector_memcpy_func_t memcpy_func);
VECTOR_EXTERN void *vector_default_global_memcpy_func(void *restrict dst, const void *restrict src, size_t n);

VECTOR_EXTERN vector_memmove_func_t vector_get_global_memmove_func(void);
VECTOR_EXTERN void vector_set_global_memmove_func(const vector_memmove_func_t memmove_func);
VECTOR_EXTERN void *vector_default_global_memmove_func(void *dst, const void *src, size_t len);

VECTOR_EXTERN vector_realloc_func_t vector_get_global_realloc_func(void);
VECTOR_EXTERN void vector_set_global_realloc_func(const vector_realloc_func_t realloc_func);
VECTOR_EXTERN void *vector_default_global_realloc_func(void *ptr, size_t size);

VECTOR_EXTERN vector_vfprintf_func_t vector_get_global_vfprintf_func(void);
VECTOR_EXTERN void vector_set_global_vfprintf_func(const vector_vfprintf_func_t vfprintf_func);
VECTOR_EXTERN int vector_default_global_vfprintf_func(FILE * restrict stream, const char * restrict format, va_list ap);

#endif
