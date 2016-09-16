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

#ifndef VECTOR_CONVENIENCE_ACCESSORS_H
#define VECTOR_CONVENIENCE_ACCESSORS_H

/**
 @file vector_convenience_accessors.h
 
 Access vector elements by value instead of reference.
 
 Requires macros in C, since the language doesn't work with type information.
 */

/**
 Create a vector of @c count copies of @c value.
 
 The vector's @c member_size is initialized to @c sizeof(value).

 @param count The number of elements in the vector.
 @param value The value to copy.

 @return A new initialized vector of size @c count.
 */
#define VECTOR_CREATE_WITH_VALUE(count, value) \
    ({ \
    __typeof__ (value) _tmp = (value); \
    vector_create_with_value(sizeof(value), count, &_tmp); \
    })

/**
 Get an element from a vector by value.
 
 The vector's @c member_size must match @c sizeof(value).

 @param vector A vector.
 @param index  An index in the range of [0, size - 1].
 @param type   The type of the element, e.g. int.

 @return The element.
 */
#define VECTOR_GET(vector, index, type) \
    ({ \
    assert(vector_element_size(vector) == sizeof(type)); \
    (*(type *)vector_get(vector, index)); \
    })

/**
 Set an element of a vector by value.

 The vector's @c member_size must match @c sizeof(value).

 @param vector A vector.
 @param index  An index in the range of [0, size - 1].
 @param value  The new value.
 */
#define VECTOR_SET(vector, index, value) \
    { \
    assert(vector_element_size(vector) == sizeof(value)); \
    __typeof__ (value) _tmp = (value); \
    vector_set(vector, index, &_tmp); \
    }

/**
 Return a vector's first element by value.

 The vector's @c member_size must match @c sizeof(value).

 @param vector A vector.
 @param type   The type of the element, e.g. int.

 @return The first element.
 */
#define VECTOR_FRONT(vector, type) \
    ({ \
    assert(vector_element_size(vector) == sizeof(type)); \
    (*(type *)vector_front(vector)); \
    })

/**
 Return a vector's last element by value.

 The vector's @c member_size must match @c sizeof(value).

 @param vector A vector.
 @param type   The type of the element, e.g. int.

 @return The last element.
 */
#define VECTOR_BACK(vector, type) \
    ({ \
    assert(vector_element_size(vector) == sizeof(type)); \
    (*(type *)vector_back(vector)); \
    })

/**
 Append an element to a vector by value, increasing its size by one.

 The vector's @c member_size must match @c sizeof(value).

 @param vector A vector.
 @param value  The new value.
 */
#define VECTOR_PUSH_BACK(vector, value) \
    { \
    assert(vector_element_size(vector) == sizeof(value)); \
    __typeof__ (value) _tmp = (value); \
    vector_push_back(vector, &_tmp); \
    }

/**
 Insert an element into a vector by value.

 Elements with positions greater than @c pos will be shifted to make room for the new element.

 The vector's @c member_size must match @c sizeof(value).

 @param vector A vector.
 @param pos    The index of the new element.
 @param value  The new value.
 */
#define VECTOR_INSERT(vector, pos, value) \
    { \
    assert(vector_element_size(vector) == sizeof(value)); \
    __typeof__ (value) _tmp = (value); \
    vector_insert(vector, pos, &_tmp); \
    }

#endif
