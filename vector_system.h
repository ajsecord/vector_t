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

#include "vector.h"

typedef void (*vector_abort_func_t)(const vector_t *vector, const char *message);
typedef void *(*vector_realloc_func_t)(void *ptr, size_t size);
typedef void (*vector_free_func_t)(void *ptr);
typedef void *(*vector_memcpy_func_t)(void *restrict dst, const void *restrict src, size_t n);
typedef void *(*vector_memmove_func_t)(void *dst, const void *src, size_t len);

VECTOR_EXTERN vector_abort_func_t vector_get_global_abort_func(void);
VECTOR_EXTERN void vector_set_global_abort_func(const vector_abort_func_t abort_func);
VECTOR_EXTERN void vector_default_global_abort_func(const vector_t *vector, const char* message);

VECTOR_EXTERN vector_realloc_func_t vector_get_global_realloc_func(void);
VECTOR_EXTERN void vector_set_global_realloc_func(const vector_realloc_func_t realloc_func);
VECTOR_EXTERN void *vector_default_global_realloc_func(void *ptr, size_t size);

VECTOR_EXTERN vector_free_func_t vector_get_global_free_func(void);
VECTOR_EXTERN void vector_set_global_free_func(const vector_free_func_t free_func);
VECTOR_EXTERN void vector_default_global_free_func(void *ptr);

VECTOR_EXTERN vector_memcpy_func_t vector_get_global_memcpy_func(void);
VECTOR_EXTERN void vector_set_global_memcpy_func(const vector_memcpy_func_t memcpy_func);
VECTOR_EXTERN void *vector_default_global_memcpy_func(void *restrict dst, const void *restrict src, size_t n);

VECTOR_EXTERN vector_memmove_func_t vector_get_global_memmove_func(void);
VECTOR_EXTERN void vector_set_global_memmove_func(const vector_memmove_func_t memmove_func);
VECTOR_EXTERN void *vector_default_global_memmove_func(void *dst, const void *src, size_t len);

#endif
