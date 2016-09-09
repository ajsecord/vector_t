#include "vector.h"

#include <assert.h>

static size_t MEMBER_SIZE = 3;  // Just because it's not the obvious power-of-two.

static void test_creation() {
    vector_t *vector = vector_create(MEMBER_SIZE);
    assert(vector);
    assert(vector_member_size(vector) == MEMBER_SIZE);
    vector_destroy(vector);
}

typedef void (*test_func_t)(void);


int main(int argc, char *argv[]) {
    test_func_t tests[] = {
        test_creation
    };

    const size_t num_tests = sizeof(tests) / sizeof(test_func_t);
    for (size_t i = 0; i < num_tests; ++i) {
        tests[i]();
    }

    printf("%i tests pass", num_tests);

    return 0;
}
