#include "vector.h"

#include <assert.h>
#include <stdlib.h>  // For assert(), split out when we split out vector_fail().

struct vector_t {
    size_t member_size;
    size_t size;
    size_t capacity;
    void *data;
};

static void vector_fail(const vector_t *vector, char *format, ...);

vector_t *vector_create(const size_t member_size) {
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

#if 0
vector_t *vector_create_with_value(const size_t member_size, const size_t count, const void *value) {
}

vector_t *vector_create_with_values(const size_t member_size, const size_t count, const void *values) {
}

vector_t *vector_create_with_vector(const vector_t *other) {
}
#endif

void vector_destroy(vector_t *vector) {
    assert(vector);
    free(vector);
}

size_t vector_member_size(const vector_t *vector) {
    assert(vector);
    return vector->member_size;
}

size_t vector_size(const vector_t *vector) {
    assert(vector);
    return vector->size;
}

size_t vector_max_size(const vector_t *vector) {
    assert(vector);
    return SIZE_MAX;
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
}

void vector_size_to_fit(vector_t *vector) {
}


void *vector_get(const vector_t *vector, const size_t index) {
    return NULL;
}

void vector_set(vector_t *vector, const size_t index, const void *value) {
}


void *vector_front(const vector_t *vector) {
    return NULL;
}

void *vector_back(const vector_t *vector) {
    return NULL;
}

void *vector_data(const vector_t *vector) {
    assert(vector);
    return vector->data;
}


void vector_push_back(vector_t *vector, const void* value) {
}

void vector_pop_back(vector_t *vector) {
}


void vector_insert(vector_t *vector, const size_t pos, const void *value) {
}

void vector_erase(vector_t *vector, const size_t pos) {
}

void vector_swap(vector_t *first, vector_t *second) {
}

static void vector_fail(const vector_t *vector, char *format, ...) {
    // TODO: Print the error message with varargs.
    abort();
}
