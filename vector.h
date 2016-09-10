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

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <stdbool.h>
#include <stddef.h>

#include "vector_environment.h"


/** An anonymous structure for storing a vector's state. */
struct vector_t;

/** An array of fixed-sized members that can grow at runtime, similar to C++'s std::vector. */
typedef struct vector_t vector_t;

VECTOR_EXTERN vector_t *vector_create(const size_t member_size);
VECTOR_EXTERN vector_t *vector_create_with_size(const size_t member_size, const size_t size);
VECTOR_EXTERN vector_t *vector_create_with_value(const size_t member_size, const size_t count, const void *value);
VECTOR_EXTERN vector_t *vector_create_with_values(const size_t member_size, const size_t count, const void *values);
VECTOR_EXTERN vector_t *vector_create_with_vector(const vector_t *other);
VECTOR_EXTERN void vector_destroy(vector_t *vector);

VECTOR_EXTERN size_t vector_member_size(const vector_t *vector);
VECTOR_EXTERN bool vector_empty(const vector_t *vector);
VECTOR_EXTERN size_t vector_size(const vector_t *vector);
VECTOR_EXTERN size_t vector_max_size(const vector_t *vector);

VECTOR_EXTERN size_t vector_capacity(const vector_t *vector);
VECTOR_EXTERN void vector_reserve(vector_t *vector, const size_t capacity);

VECTOR_EXTERN void vector_clear(vector_t *vector);
VECTOR_EXTERN void vector_resize(vector_t *vector, const size_t size);
VECTOR_EXTERN void vector_size_to_fit(vector_t *vector);

VECTOR_EXTERN void *vector_get(const vector_t *vector, const size_t index);
VECTOR_EXTERN void vector_set(vector_t *vector, const size_t index, const void *value);

VECTOR_EXTERN void *vector_front(const vector_t *vector);
VECTOR_EXTERN void *vector_back(const vector_t *vector);
VECTOR_EXTERN void *vector_data(const vector_t *vector);

VECTOR_EXTERN void vector_push_back(vector_t *vector, const void* value);
VECTOR_EXTERN void vector_pop_back(vector_t *vector);

VECTOR_EXTERN void vector_insert(vector_t *vector, const size_t pos, const void *value);
VECTOR_EXTERN void vector_erase(vector_t *vector, const size_t pos);
VECTOR_EXTERN void vector_swap(vector_t *first, vector_t *second);


#endif
