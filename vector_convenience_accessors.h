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

#define VECTOR_CREATE_WITH_VALUE(size, value) \
    ({ \
    __typeof__ (value) _tmp = (value); \
    vector_create_with_value(sizeof(value), size, &_tmp); \
    })

#define VECTOR_GET(vector, index, type) (*(type *)vector_get(vector, index))

#define VECTOR_SET(vector, index, value) \
    { \
    __typeof__ (value) _tmp = (value); \
    vector_set(vector, index, &_tmp); \
    }


#define VECTOR_FRONT(vector, type) (*(type *)vector_front(vector))

#define VECTOR_BACK(vector, type) (*(type *)vector_back(vector))

#define VECTOR_PUSH_BACK(vector, value) \
    { \
    __typeof__ (value) _tmp = (value); \
    vector_push_back(vector, &_tmp); \
    }

#define VECTOR_INSERT(vector, pos, value) \
    { \
    __typeof__ (value) _tmp = (value); \
    vector_insert(vector, pos, &_tmp); \
    }

#endif
