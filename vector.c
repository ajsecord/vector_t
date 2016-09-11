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

#include "vector.h"
#include "vector_system.h"

#include <assert.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

// TODO: Audit each function for what happens if the assert() condition fails in release mode.

static size_t VECTOR_MAX_SIZE = SIZE_MAX;
static size_t VECTOR_MAX_MESSAGE_SIZE = 256;

struct vector_t {
    size_t member_size;
    size_t size;
    size_t capacity;
    float expansion_factor;
    void *data;
};

static void vector_abort(const vector_t *vector, char *format, ...);
static void *vector_realloc(void *ptr, const size_t size);
static void vector_free(void *ptr);
static void *vector_memcpy(void *restrict dst, const void *restrict src, size_t n);
static void *vector_memmove(void *dst, const void *src, size_t len);

static size_t capacity_for_size(const size_t cur_size, const size_t required_size, const float expansion_factor);

static inline void *element(const vector_t *vector, const size_t index) {
    assert(vector && index < vector->size);
    return vector->data + index * vector->member_size;
}

vector_t *vector_create(const size_t member_size) {
    assert(member_size > 0);
    vector_t *vector = vector_realloc(NULL, sizeof(vector_t));
    if (vector) {
        vector->member_size = member_size;
        vector->size = 0;
        vector->capacity = 0;
        vector->expansion_factor = 2;
        vector->data = NULL;
    }
    return vector;
}

vector_t *vector_create_with_size(const size_t member_size, const size_t size) {
    vector_t *vector = vector_create(member_size);
    if (vector) {
        vector_resize(vector, size);
    }
    return vector;
}

vector_t *vector_create_with_value(const size_t member_size, const size_t count, const void *value) {
    assert(count == 0 || value);
    vector_t *vector = vector_create(member_size);
    if (vector) {
        vector_resize(vector, count);
        for (size_t i = 0; i < count; ++i) {
            vector_memcpy(element(vector, i), value, member_size);
        }
    }
    return vector;
}

vector_t *vector_create_with_values(const size_t member_size, const size_t count, const void *values) {
    assert(count == 0 || values);
    vector_t *vector = vector_create(member_size);
    if (vector) {
        vector_resize(vector, count);
        vector_memcpy(vector->data, values, count * member_size);
    }
    return vector;
}

vector_t *vector_create_with_vector(const vector_t *other) {
    assert(other);
    vector_t *vector = vector_create(other->member_size);
    if (vector) {
        vector_resize(vector, other->size);
        vector_memcpy(vector->data, other->data, other->size * other->member_size);
    }
    return vector;
}

void vector_destroy(vector_t *vector) {
    assert(vector);
    vector_free(vector);
}

size_t vector_member_size(const vector_t *vector) {
    assert(vector);
    return vector->member_size;
}

bool vector_empty(const vector_t *vector) {
    assert(vector);
    return vector->size == 0;
}

size_t vector_size(const vector_t *vector) {
    assert(vector);
    return vector->size;
}

size_t vector_max_size(const vector_t *vector) {
    assert(vector);
    return VECTOR_MAX_SIZE;
}

size_t vector_capacity(const vector_t *vector) {
    assert(vector);
    return vector->capacity;
}

void vector_reserve(vector_t *vector, const size_t capacity) {
    assert(vector);
    if (vector->capacity < capacity) {
        void *new_data = vector_realloc(vector->data, vector->member_size * capacity);
        if (!new_data) {
            vector_abort(vector, "Could not allocate %u bytes.", vector->member_size * capacity);
            return;
        }
        vector->data = new_data;
        vector->capacity = capacity;
    }
    assert(vector->capacity >= capacity);
}

void vector_clear(vector_t *vector) {
    assert(vector);
    vector->size = 0;
}

void vector_resize(vector_t *vector, const size_t size) {
    assert(vector);
    vector_reserve(vector, size);
    vector->size = size;
}

void vector_size_to_fit(vector_t *vector) {
    assert(vector);
    if (vector->capacity > vector->size) {
        void *new_data = vector_realloc(vector->data, vector->size * vector->member_size);
        if (!new_data) {
            vector_abort(vector, "Could not shrink allocation to %u bytes.",
                        vector->member_size * vector->member_size);
            return;
        }
        vector->capacity = vector->size;
    }
    assert(vector->capacity == vector->size);
}

void *vector_get(const vector_t *vector, const size_t index) {
    return element(vector, index);
}

void vector_set(vector_t *vector, const size_t index, const void *value) {
    assert(vector && value && index < vector->size);
    vector_memcpy(element(vector, index), value, vector->member_size);
}

void *vector_front(const vector_t *vector) {
    assert(vector && vector->size >= 1);
    return vector->data;
}

void *vector_back(const vector_t *vector) {
    assert(vector && vector->size >= 1);
    return element(vector, vector->size - 1);
}

void *vector_data(const vector_t *vector) {
    assert(vector);
    return vector->data;
}

void vector_push_back(vector_t *vector, const void* value) {
    assert(vector && value);
    const size_t new_capacity = vector_capacity_for_size(vector, ++vector->size);
    vector_reserve(vector, new_capacity);
    vector_memcpy(element(vector, vector->size - 1), value, vector->member_size);
}

void vector_pop_back(vector_t *vector) {
    assert(vector && vector->size >= 1);
    if (vector->size > 0) {
        --vector->size;
    }
}

void vector_insert(vector_t *vector, const size_t pos, const void *value) {
    assert(vector && value && pos <= vector->size);
    const size_t new_capacity = vector_capacity_for_size(vector, vector->size + 1);
    vector_reserve(vector, new_capacity);
    if (pos <= vector->size) {
        ++vector->size;
        const size_t byte_count = (vector->size - 1) * vector->member_size;
        if (byte_count > 0) {
            vector_memmove(element(vector, pos + 1), element(vector, pos), byte_count);
        }
        vector_memcpy(element(vector, pos), value, vector->member_size);
    }
}

void vector_erase(vector_t *vector, const size_t pos) {
    assert(vector && pos <= vector->size);
    if (pos < vector->size) {
        const size_t byte_count = (vector->size - 1) * vector->member_size;
        if (byte_count > 0) {
            vector_memmove(element(vector, pos), element(vector, pos + 1), byte_count);
        }
        --vector->size;
    }
}

void vector_swap(vector_t *first, vector_t *second) {
    assert(first && second && first->member_size == second->member_size);
    size_t tmp_size = first->size;
    size_t tmp_capacity = first->capacity;
    float tmp_expansion_factor = first->expansion_factor;
    void *tmp_data = first->data;
    first->size = second->size;
    first->capacity = second->capacity;
    first->data = second->data;
    second->size = tmp_size;
    second->capacity = tmp_capacity;
    second->expansion_factor = tmp_expansion_factor;
    second->data = tmp_data;
}

float vector_expansion_factor(const vector_t *vector) {
    assert(vector);
    return vector->expansion_factor;
}

void vector_set_expansion_factor(vector_t *vector, const float expansion_factor) {
    assert(vector && expansion_factor > 1);
    vector->expansion_factor = expansion_factor;
}

size_t vector_capacity_for_size(const vector_t *vector, const size_t size) {
    assert(vector);
    return capacity_for_size(vector->capacity, size, vector->expansion_factor);
}

static void vector_abort(const vector_t *vector, char *format, ...) {
    char message[VECTOR_MAX_MESSAGE_SIZE];

    va_list argp;
    va_start(argp, format);
    vsnprintf(message, VECTOR_MAX_MESSAGE_SIZE, format, argp);
    va_end(argp);

    vector_abort_func_t abort_func = vector_get_global_abort_func();
    assert(abort_func);
    abort_func(vector, message);
}

static void *vector_realloc(void *ptr, const size_t size) {
    vector_realloc_func_t realloc_func = vector_get_global_realloc_func();
    return realloc_func(ptr, size);
}

static void vector_free(void *ptr) {
    vector_free_func_t free_func = vector_get_global_free_func();
    free_func(ptr);
}

static void *vector_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    vector_memcpy_func_t memcpy_func = vector_get_global_memcpy_func();
    return memcpy_func(dst, src, n);
}

static void *vector_memmove(void *dst, const void *src, size_t len) {
    vector_memmove_func_t memmove_func = vector_get_global_memmove_func();
    return memmove_func(dst, src, len);
}

// TODO: Expose this as an advanced global function the user can replace.
static size_t capacity_for_size(const size_t cur_capacity,
                                const size_t required_size,
                                const float expansion_factor) {
    size_t new_capacity = cur_capacity;
    while (new_capacity < required_size) {
        size_t expanded_capacity = (size_t)(new_capacity * expansion_factor);
        if (expanded_capacity <= new_capacity) {
            // This case happens when the increment is smaller than a single integer, which is
            // expected when the current capacity is zero or very small, but it can also happen with
            // very small expansion factors.
            expanded_capacity = new_capacity + 1;
        }
        new_capacity = expanded_capacity;
    }
    return new_capacity;
}

#if 0
// TODO: Expose this linear version as an example.
static size_t capacity_for_size(const size_t cur_capacity,
                                const size_t required_size,
                                const float expansion_factor) {
    return cur_capacity >= required_size ? cur_capacity : required_size;
}
#endif

