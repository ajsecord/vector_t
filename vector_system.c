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

#include "vector_system.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static vector_abort_func_t global_abort_func = vector_default_global_abort_func;
static vector_free_func_t global_free_func = vector_default_global_free_func;
static vector_memcpy_func_t global_memcpy_func = vector_default_global_memcpy_func;
static vector_memmove_func_t global_memmove_func = vector_default_global_memmove_func;
static vector_realloc_func_t global_realloc_func = vector_default_global_realloc_func;
static vector_vfprintf_func_t global_vfprintf_func = vector_default_global_vfprintf_func;

vector_abort_func_t vector_get_global_abort_func(void) {
    return global_abort_func;
}

void vector_set_global_abort_func(const vector_abort_func_t abort_func) {
    global_abort_func = abort_func;
}

void vector_default_global_abort_func() {
    abort();
}

vector_free_func_t vector_get_global_free_func(void) {
    return global_free_func;
}

void vector_set_global_free_func(const vector_free_func_t free_func) {
    global_free_func = free_func;
}

void vector_default_global_free_func(void *ptr) {
    free(ptr);
}

vector_memcpy_func_t vector_get_global_memcpy_func(void) {
    return global_memcpy_func;
}

void vector_set_global_memcpy_func(const vector_memcpy_func_t memcpy_func) {
    global_memcpy_func = memcpy_func;
}

void *vector_default_global_memcpy_func(void *restrict dst, const void *restrict src, size_t n) {
    return memcpy(dst, src, n);
}

vector_memmove_func_t vector_get_global_memmove_func(void) {
    return global_memmove_func;
}

void vector_set_global_memmove_func(const vector_memmove_func_t memmove_func) {
    global_memmove_func = memmove_func;
}

void *vector_default_global_memmove_func(void *dst, const void *src, size_t len) {
    return memmove(dst, src, len);
}

vector_vfprintf_func_t vector_get_global_vfprintf_func(void) {
    return global_vfprintf_func;
}

void vector_set_global_vfprintf_func(const vector_vfprintf_func_t vfprintf_func) {
    global_vfprintf_func = vfprintf_func;
}

int vector_default_global_vfprintf_func(FILE * restrict stream, const char * restrict format, va_list ap) {
    return vfprintf(stream, format, ap);
}

vector_realloc_func_t vector_get_global_realloc_func(void) {
    return global_realloc_func;
}

void vector_set_global_realloc_func(const vector_realloc_func_t realloc_func) {
    global_realloc_func = realloc_func;
}

void *vector_default_global_realloc_func(void *ptr, size_t size) {
    return realloc(ptr, size);
}

