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

#include <assert.h>
#include <stdlib.h>  // For assert(), split out when we split out vector_fail().
#include <string.h>

// TODO: Audit each function for what happens if the assert() condition fails in release mode.

static size_t VECTOR_MAX_SIZE = SIZE_MAX;

struct vector_t {
    size_t member_size;
    size_t size;
    size_t capacity;
    void *data;
};

static void vector_fail(const vector_t *vector, char *format, ...);

static inline void *element(const vector_t *vector, const size_t index) {
    assert(vector && index < vector->size);
    return vector->data + index * vector->member_size;
}

vector_t *vector_create(const size_t member_size) {
    assert(member_size > 0);
    vector_t *vector = malloc(sizeof(vector_t));
    if (vector) {
        vector->member_size = member_size;
        vector->size = 0;
        vector->capacity = 0;
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
            memcpy(element(vector, i), value, member_size);
        }
    }
    return vector;
}

vector_t *vector_create_with_values(const size_t member_size, const size_t count, const void *values) {
    assert(count == 0 || values);
    vector_t *vector = vector_create(member_size);
    if (vector) {
        vector_resize(vector, count);
        memcpy(vector->data, values, count * member_size);
    }
    return vector;
}

vector_t *vector_create_with_vector(const vector_t *other) {
    assert(other);
    vector_t *vector = vector_create(other->member_size);
    if (vector) {
        vector_resize(vector, other->size);
        memcpy(vector->data, other->data, other->size * other->member_size);
    }
    return vector;
}

void vector_destroy(vector_t *vector) {
    assert(vector);
    free(vector);
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
        void *new_data = realloc(vector->data, vector->member_size * capacity);
        if (!new_data) {
            vector_fail(vector, "Could not allocate %u bytes.", vector->member_size * capacity);
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
        void *new_data = realloc(vector->data, vector->size * vector->member_size);
        if (!new_data) {
            vector_fail(vector, "Could not shrink allocation to %u bytes.",
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
    memcpy(element(vector, index), value, vector->member_size);
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
    vector_reserve(vector, ++vector->size);
    memcpy(element(vector, vector->size - 1), value, vector->member_size);
}

void vector_pop_back(vector_t *vector) {
    assert(vector && vector->size >= 1);
    if (vector->size > 0) {
        --vector->size;
    }
}

void vector_insert(vector_t *vector, const size_t pos, const void *value) {
    assert(vector && value && pos <= vector->size);
    vector_reserve(vector, vector->size + 1);
    if (pos <= vector->size) {
        ++vector->size;
        const size_t byte_count = (vector->size - 1) * vector->member_size;
        if (byte_count > 0) {
            memmove(element(vector, pos + 1), element(vector, pos), byte_count);
        }
        memcpy(element(vector, pos), value, vector->member_size);
    }
}

void vector_erase(vector_t *vector, const size_t pos) {
    assert(vector && pos <= vector->size);
    if (pos < vector->size) {
        const size_t byte_count = (vector->size - 1) * vector->member_size;
        if (byte_count > 0) {
            memmove(element(vector, pos), element(vector, pos + 1), byte_count);
        }
        --vector->size;
    }
}

void vector_swap(vector_t *first, vector_t *second) {
    assert(first && second && first->member_size == second->member_size);
    size_t tmp_size = first->size;
    size_t tmp_capacity = first->capacity;
    void *tmp_data = first->data;
    first->size = second->size;
    first->capacity = second->capacity;
    first->data = second->data;
    second->size = tmp_size;
    second->capacity = tmp_capacity;
    second->data = tmp_data;
}

static void vector_fail(const vector_t *vector, char *format, ...) {
    // TODO: Print the error message with varargs.
    abort();
}
