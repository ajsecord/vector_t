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
