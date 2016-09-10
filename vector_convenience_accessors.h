#ifndef VECTOR_CONVENIENCE_ACCESSORS_H
#define VECTOR_CONVENIENCE_ACCESSORS_H

#define VECTOR_SET(vector, index, value) \
    { \
    __typeof__ (value) _tmp = (value); \
    vector_set(vector, index, &_tmp); \
    }

#define VECTOR_GET(vector, index, type) (*(type *)vector_get(vector, index))

#endif
