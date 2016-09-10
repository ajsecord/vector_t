#include "vector.h"

#include <assert.h>
#include <stdio.h>

typedef void (*test_func_t)(void);

static void test_create() {
    vector_t *vector = vector_create(3);
    assert(vector && vector_member_size(vector) == 3);
    vector_destroy(vector);
}

static void test_create_with_size() {
    vector_t *vector = vector_create_with_size(3, 42);
    assert(vector && vector_size(vector) == 42);
    vector_destroy(vector);
}

static void test_create_with_value() {
    const size_t size = 42;
    const int value = 23;
    vector_t *vector = vector_create_with_value(sizeof(int), size, &value);
    assert(vector && vector_size(vector) == size);
    for (int i = 0; i < size; ++i) {
        assert(*(int *)vector_get(vector, i) == value);
    }
    vector_destroy(vector);
}

int main(int argc, char *argv[]) {
    test_func_t tests[] = {
        test_create,
        test_create_with_size,
        test_create_with_value,
    };

    const size_t num_tests = sizeof(tests) / sizeof(test_func_t);
    for (size_t i = 0; i < num_tests; ++i) {
        tests[i]();
    }

    printf("%i tests pass\n", (int)num_tests);

    return 0;
}
