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

/**
 Create an empty vector.

 @param element_size The size of an element in bytes.

 @return A new initialized vector.
 */
VECTOR_EXTERN vector_t *vector_create(const size_t element_size);

/**
 Create a vector of size @c @size.
 
 The elements of the new vector are uninitialized.

 @param element_size The size of an element in bytes.
 @param size         The number of elements in the vector.

 @return A new initialized vector of size @c size.
 */
VECTOR_EXTERN vector_t *vector_create_with_size(const size_t element_size, const size_t size);

/**
 Create a vector of @c count copies of @c *value.

 @param element_size The size of an element in bytes.
 @param count        The number of elements in the vector.
 @param value        The value to copy.

 @return A new initialized vector of size @c size.
 */
VECTOR_EXTERN vector_t *vector_create_with_value(const size_t element_size, const size_t count, const void *value);

/**
 Create a vector by copying an array of values.
 
 The @c values pointer must point to at least @c count elements of @c element_size bytes each.

 @param element_size The size of an element in bytes.
 @param count        The number of values.
 @param values       An array of values.

 @return A new initialized vector with a copy of @c values.
 */
VECTOR_EXTERN vector_t *vector_create_with_values(const size_t element_size, const size_t count, const void *values);

/**
 Create a vector by copying another vector.

 @param other The vector to copy.

 @return A new intialized vector copy of @c other.
 */
VECTOR_EXTERN vector_t *vector_create_with_vector(const vector_t *other);

/**
 Destroy a vector and deallocate its memory.

 @param vector A vector.
 */
VECTOR_EXTERN void vector_destroy(vector_t *vector);

/**
 Return a vector's element size.

 @param vector A vector.

 @return The size of the vector's elements in bytes.
 */
VECTOR_EXTERN size_t vector_element_size(const vector_t *vector);

/**
 Return if a vector is empty.

 @param vector A vector.

 @return True if the vector is empty.
 */
VECTOR_EXTERN bool vector_empty(const vector_t *vector);

/**
 Return the number of elements in a vector.

 @param vector A vector.

 @return The size of the vector.
 */
VECTOR_EXTERN size_t vector_size(const vector_t *vector);

/**
 Return the maximum possible number of elements this vector can contain.
 
 The practical maximum size is likely to be limited by available memory,
 but this function returns the largest size the vector can represent.

 @param vector A vector.

 @return The maximum possible size of a vector.
 */
VECTOR_EXTERN size_t vector_max_size(const vector_t *vector);

/**
 Return the number of elements a vector can grow to without reallocation.

 @param vector A vector.

 @return The vector's capacity.
 */
VECTOR_EXTERN size_t vector_capacity(const vector_t *vector);

/**
 Ensure that a vector can grow to at least @c capacity elements without reallocation.
 
 The resulting capacity may be greater than requested. If memory allocation fails,
 the global handler returned by @c vector_get_global_abort_func() is called.

 @param vector   A vector.
 @param capacity The new capacity.
 */
VECTOR_EXTERN void vector_reserve(vector_t *vector, const size_t capacity);

/**
 Remove all elements from a vector.

 @param vector A vector.
 */
VECTOR_EXTERN void vector_clear(vector_t *vector);

/**
 Resize a vector.
 
 If @c size is greater than the vector's current size, the new elements will be uninitialized.

 @param vector A vector.
 @param size   The new size.
 */
VECTOR_EXTERN void vector_resize(vector_t *vector, const size_t size);

/**
 Resize the a vector's internal storage to fit its size.
 
 The vector's capacity will be reduced to the minimum required to store the elements in the vector.

 @param vector A vector.
 */
VECTOR_EXTERN void vector_size_to_fit(vector_t *vector);

/**
 Get an element from a vector.

 @param vector A vector.
 @param index  An index in the range of [0, size - 1].

 @return A pointer to the element.
 */
VECTOR_EXTERN void *vector_get(const vector_t *vector, const size_t index);

/**
 Set an element of a vector.

 @param vector A vector.
 @param index  An index in the range of [0, size - 1].
 @param value  A pointer to the new value of at least @c member_size bytes.
 */
VECTOR_EXTERN void vector_set(vector_t *vector, const size_t index, const void *value);

/**
 Return a vector's first element.

 @param vector A vector.
 
 @return A pointer to the first element.
 */
VECTOR_EXTERN void *vector_front(const vector_t *vector);

/**
 Return a vector's last element.

 @param vector A vector.
 
 @return A pointer to the last element.
 */
VECTOR_EXTERN void *vector_back(const vector_t *vector);

/**
 Return a pointer to a vector's storage.

 @param vector A vector.
 
 @return A pointer to at least @c member_size x @c size bytes.
 */
VECTOR_EXTERN void *vector_data(const vector_t *vector);

/**
 Append an element to a vector, increasing its size by one.

 @param vector A vector.
 @param value  A pointer to the new value of at least @c member_size bytes.
 */
VECTOR_EXTERN void vector_push_back(vector_t *vector, const void* value);

/**
 Remove the last element of a vector, decreasing its size by one.

 @param vector A vector.
 */
VECTOR_EXTERN void vector_pop_back(vector_t *vector);

/**
 Insert an element into a vector.
 
 Elements with positions greater than @c pos will be shifted to make room for the new element.

 @param vector A vector.
 @param pos    The index of the new element.
 @param value  A pointer to the new value of at least @c member_size bytes.
 */
VECTOR_EXTERN void vector_insert(vector_t *vector, const size_t pos, const void *value);

/**
 Erase an element of a vector, decreasing its size by one.

 @param vector A vector.
 @param pos    The index of the element to erase.
 */
VECTOR_EXTERN void vector_erase(vector_t *vector, const size_t pos);

/**
 Swap the contents of two vectors.
 
 The contents are swapped with no copying or reallocation.

 @param first  The first vector.
 @param second The second vector.
 */
VECTOR_EXTERN void vector_swap(vector_t *first, vector_t *second);

/**
 Return the expansion factor of a vector.
 
 The expansion factor of a vector is used by the default capacity function to increase the vector's
 storage by more than is strictly necessary to avoid poor performance from frequent allocations.
 The expansion factor controls the space/time tradeoff of balancing unused memory and allocation
 calls.
 
 The factor should be greater than one.

 @param vector A vector.

 @return The expansion factor as a floating-point number, e.g. 1.5.
 */
VECTOR_EXTERN float vector_expansion_factor(const vector_t *vector);

/**
 Set the expansion factor of a vector.
 
 @see vector_expansion_factor

 @param vector           A vector.
 @param expansion_factor The expansion factor as a floating-point number, e.g. 1.5.
 */
VECTOR_EXTERN void vector_set_expansion_factor(vector_t *vector, const float expansion_factor);

/**
 Return the capacity that would be used for a particular size.
 
 This function does not change @c vector in any way.

 @param vector A vector.
 @param size   The speculative size of the vector.

 @return A capacity in elements.
 */
VECTOR_EXTERN size_t vector_capacity_for_size(const vector_t *vector, const size_t size);

#endif
