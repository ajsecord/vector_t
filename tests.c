#include "vector.h"
#include "vector_convenience_accessors.h"

#include <assert.h>
#include <stdio.h>

typedef void (*test_func_t)(void);

static inline void assert_invariants(const vector_t *vector) {
    assert(vector);
    assert(vector_capacity(vector) >= vector_size(vector));
    assert(vector_size(vector) <= vector_max_size(vector));
}

static void test_create() {
    vector_t *vector = vector_create(3);

    assert_invariants(vector);
    assert(vector_member_size(vector) == 3);
    assert(vector_empty(vector));

    vector_destroy(vector);
}

static void test_create_with_size() {
    vector_t *vector = vector_create_with_size(3, 42);

    assert_invariants(vector);
    assert(vector_member_size(vector) == 3);
    assert(vector_size(vector) == 42);

    vector_destroy(vector);
}

static void test_create_with_value() {
    const size_t size = 42;
    const int value = 23;
    vector_t *vector = vector_create_with_value(sizeof(int), size, &value);

    assert_invariants(vector);
    assert(vector_member_size(vector) == sizeof(int));
    assert(vector_size(vector) == size);
    for (int i = 0; i < size; ++i) {
        assert(*(int *)vector_get(vector, i) == value);
    }

    vector_destroy(vector);
}

static void test_convenience_create_with_value() {
    const size_t size = 42;
    vector_t *vector = VECTOR_CREATE_WITH_VALUE(size, 23);

    assert_invariants(vector);
    assert(vector_member_size(vector) == sizeof(int));
    assert(vector_size(vector) == size);
    for (int i = 0; i < size; ++i) {
        assert(*(int *)vector_get(vector, i) == 23);
    }

    vector_destroy(vector);
}

static void test_create_with_values() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);

    assert_invariants(vector);
    assert(vector_member_size(vector) == sizeof(int));
    assert(vector_size(vector) == 3);
    for (int i = 0; i < 3; ++i) {
        assert(*(int *)vector_get(vector, i) == values[i]);
    }

    vector_destroy(vector);
}

static void test_reserve() {
    vector_t *vector = vector_create(sizeof(int));
    vector_reserve(vector, 100);

    assert_invariants(vector);
    assert(vector_capacity(vector) >= 100);

    vector_destroy(vector);
}

static void test_clear() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);
    vector_clear(vector);

    assert_invariants(vector);
    assert(vector_empty(vector));

    vector_destroy(vector);
}

static void test_resize_up() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);
    vector_resize(vector, 10);

    assert_invariants(vector);
    assert(vector_size(vector) == 10);
    for (int i = 0; i < 3; ++i) {
        assert(*(int *)vector_get(vector, i) == values[i]);
    }

    vector_destroy(vector);
}

static void test_resize_down() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);
    vector_resize(vector, 2);

    assert_invariants(vector);
    assert(vector_size(vector) == 2);
    for (int i = 0; i < 2; ++i) {
        assert(*(int *)vector_get(vector, i) == values[i]);
    }

    vector_destroy(vector);
}

static void test_size_to_fit() {
    vector_t *vector = vector_create(sizeof(int));
    vector_reserve(vector, 10);

    assert_invariants(vector);
    assert(vector_empty(vector));
    assert(vector_capacity(vector) >= 10);

    vector_size_to_fit(vector);
    assert(vector_capacity(vector) == vector_size(vector));

    vector_destroy(vector);
}

static void test_set() {
    int value = 42;
    vector_t *vector = vector_create_with_value(sizeof(int), 1, &value);
    value = 23;
    vector_set(vector, 0, &value);

    assert_invariants(vector);
    assert(*(int *)vector_get(vector, 0) == 23);

    vector_destroy(vector);
}

static void test_convenience_get() {
    int value = 42;
    vector_t *vector = vector_create_with_value(sizeof(int), 1, &value);

    assert_invariants(vector);
    assert(VECTOR_GET(vector, 0, int) == 42);

    vector_destroy(vector);
}

static void test_convenience_set() {
    int value = 42;
    vector_t *vector = vector_create_with_value(sizeof(int), 1, &value);
    VECTOR_SET(vector, 0, 23);

    assert_invariants(vector);
    assert(*(int *)vector_get(vector, 0) == 23);

    vector_destroy(vector);
}

static void test_front() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);

    assert_invariants(vector);
    assert(*(int *)vector_front(vector) == 42);

    vector_destroy(vector);
}

static void test_convenience_front() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);

    assert_invariants(vector);
    assert(VECTOR_FRONT(vector, int) == 42);

    vector_destroy(vector);
}

static void test_back() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);

    assert_invariants(vector);
    assert(*(int *)vector_back(vector) == 7);

    vector_destroy(vector);
}

static void test_convenience_back() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);

    assert_invariants(vector);
    assert(VECTOR_BACK(vector, int) == 7);

    vector_destroy(vector);
}

static void test_data() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);

    assert_invariants(vector);
    assert(*(int *)vector_data(vector) == 42);

    vector_destroy(vector);
}

static void test_push_back_empty() {
    vector_t *vector = vector_create(sizeof(int));
    int value = 42;
    vector_push_back(vector, &value);
    
    assert_invariants(vector);
    assert(vector_size(vector) == 1);
    assert(*(int *)vector_get(vector, 0) == 42);

    vector_destroy(vector);
}

static void test_push_back() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);
    int value = 42;
    vector_push_back(vector, &value);

    assert_invariants(vector);
    assert(vector_size(vector) == 4);
    assert(*(int *)vector_get(vector, 3) == 42);

    vector_destroy(vector);
}

static void test_convenience_push_back() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);
    VECTOR_PUSH_BACK(vector, 42);

    assert_invariants(vector);
    assert(vector_size(vector) == 4);
    assert(*(int *)vector_get(vector, 3) == 42);

    vector_destroy(vector);
}

static void test_pop_back() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);
    vector_pop_back(vector);

    assert_invariants(vector);
    assert(vector_size(vector) == 2);

    vector_destroy(vector);
}

static void test_pop_back_to_empty() {
    const int value = 42;
    vector_t *vector = vector_create_with_value(sizeof(int), 1, &value);
    vector_pop_back(vector);

    assert_invariants(vector);
    assert(vector_empty(vector));

    vector_destroy(vector);
}

static void test_insert_empty() {
    vector_t *vector = vector_create(sizeof(int));
    int value = 42;
    vector_insert(vector, 0, &value);

    assert_invariants(vector);
    assert(vector_size(vector) == 1);
    assert(*(int *)vector_get(vector, 0) == 42);

    vector_destroy(vector);
}

static void test_insert() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);
    int value = 77;
    vector_insert(vector, 0, &value);

    assert_invariants(vector);
    assert(vector_size(vector) == 4);
    assert(*(int *)vector_get(vector, 0) == 77);
    for (int i = 0; i < 3; ++i) {
        assert(*(int *)vector_get(vector, i + 1) == values[i]);
    }

    vector_destroy(vector);
}

static void test_convenience_insert() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);
    VECTOR_INSERT(vector, 0, 77);

    assert_invariants(vector);
    assert(vector_size(vector) == 4);
    assert(*(int *)vector_get(vector, 0) == 77);
    for (int i = 0; i < 3; ++i) {
        assert(*(int *)vector_get(vector, i + 1) == values[i]);
    }

    vector_destroy(vector);
}

static void test_erase() {
    const int values[] = { 42, 23, 7 };
    vector_t *vector = vector_create_with_values(sizeof(int), 3, values);
    vector_erase(vector, 1);

    assert_invariants(vector);
    assert(vector_size(vector) == 2);
    assert(*(int *)vector_get(vector, 0) == 42);
    assert(*(int *)vector_get(vector, 1) == 7);

    vector_destroy(vector);
}

static void test_erase_to_empty() {
    const int value = 42;
    vector_t *vector = vector_create_with_values(sizeof(int), 1, &value);
    vector_erase(vector, 0);

    assert_invariants(vector);
    assert(vector_empty(vector));

    vector_destroy(vector);
}

static void test_swap() {
    const int value1 = 23;
    const int value2 = 42;
    const size_t size1 = 1;
    const size_t size2 = 3;
    vector_t *vector1 = vector_create_with_value(sizeof(int), size1, &value1);
    vector_t *vector2 = vector_create_with_value(sizeof(int), size2, &value2);
    vector_swap(vector1, vector2);

    assert_invariants(vector1);
    assert(vector_size(vector1) == size2);
    for (int i = 0; i < size2; ++i) {
        assert(*(int *)vector_get(vector1, i) == value2);
    }
    
    assert_invariants(vector2);
    assert(vector_size(vector2) == size1);
    for (int i = 0; i < size1; ++i) {
        assert(*(int *)vector_get(vector2, i) == value1);
    }

    vector_destroy(vector1);
    vector_destroy(vector2);
}

static void test_swap_with_empty() {
    const int value = 23;
    const size_t size = 1;
    vector_t *vector1 = vector_create_with_value(sizeof(int), size, &value);
    vector_t *vector2 = vector_create(sizeof(int));
    vector_swap(vector1, vector2);

    assert_invariants(vector1);
    assert(vector_size(vector1) == 0);
    
    assert_invariants(vector2);
    assert(vector_size(vector2) == size);
    for (int i = 0; i < size; ++i) {
        assert(*(int *)vector_get(vector2, i) == value);
    }

    vector_destroy(vector1);
    vector_destroy(vector2);
}

struct test_info_t {
    const char *name;
    test_func_t func;
};

typedef struct test_info_t test_info_t;

#define TEST_INFO_CREATE(test_func) { #test_func, test_func }

int main(int argc, char *argv[]) {
    test_info_t tests[] = {
        TEST_INFO_CREATE(test_create),
        TEST_INFO_CREATE(test_create_with_size),
        TEST_INFO_CREATE(test_create_with_value),
        TEST_INFO_CREATE(test_convenience_create_with_value),
        TEST_INFO_CREATE(test_create_with_values),
        TEST_INFO_CREATE(test_reserve),
        TEST_INFO_CREATE(test_clear),
        TEST_INFO_CREATE(test_resize_up),
        TEST_INFO_CREATE(test_resize_down),
        TEST_INFO_CREATE(test_size_to_fit),
        TEST_INFO_CREATE(test_set),
        TEST_INFO_CREATE(test_convenience_get),
        TEST_INFO_CREATE(test_convenience_set),
        TEST_INFO_CREATE(test_front),
        TEST_INFO_CREATE(test_convenience_front),
        TEST_INFO_CREATE(test_back),
        TEST_INFO_CREATE(test_convenience_back),
        TEST_INFO_CREATE(test_data),
        TEST_INFO_CREATE(test_push_back_empty),
        TEST_INFO_CREATE(test_push_back),
        TEST_INFO_CREATE(test_pop_back),
        TEST_INFO_CREATE(test_pop_back_to_empty),
        TEST_INFO_CREATE(test_convenience_push_back),
        TEST_INFO_CREATE(test_insert_empty),
        TEST_INFO_CREATE(test_insert),
        TEST_INFO_CREATE(test_convenience_insert),
        TEST_INFO_CREATE(test_erase),
        TEST_INFO_CREATE(test_erase_to_empty),
        TEST_INFO_CREATE(test_swap),
        TEST_INFO_CREATE(test_swap_with_empty),
    };

    const size_t num_tests = sizeof(tests) / sizeof(test_info_t);
    for (size_t i = 0; i < num_tests; ++i) {
        printf("%s\n", tests[i].name);
        tests[i].func();
    }

    printf("%i tests pass.\n", (int)num_tests);

    return 0;
}
