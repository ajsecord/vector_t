# `vector_t`: A dynamic array for C

[![Build Status](https://travis-ci.org/ajsecord/vector_t.svg?branch=master)](https://travis-ci.org/ajsecord/vector_t) [![Code Coverage](https://codecov.io/gh/ajsecord/vector_t/coverage.svg?branch=master)](https://codecov.io/gh/ajsecord/vector_t?branch=master)

`vector_t` is a dynamic array of fixed-size objects for C, similar to C++'s
[`std::vector`](http://en.cppreference.com/w/cpp/container/vector) class. There are many like
it, but this one is mine.

## Runtime behavior

`vector_t` has the following runtime behavior:

- Element access takes O(1) operations
- Appending N elements to a vector causes amortized O(N) allocations
- Memory usage can be controlled using either `vector_reserve()` or `vector_size_to_fit()`.

## Compilation environment

Except for the optional `vector_convenience_accessors.h` macros, `vector_t` only requires a
[C99](https://en.wikipedia.org/wiki/C99) compiler and has no external dependencies.
[Clang](http://clang.llvm.org/) and [GCC](https://gcc.gnu.org/) are specifically tested.

## Convenience accessors

> Using the macros in `vector_convenience_accessors.h` requires the common C extensions of [typeof()
> operator](https://gcc.gnu.org/onlinedocs/gcc/Typeof.html) and [statement
> expressions](https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html). These extensions are
> well-supported on GCC and clang, at least.
 
`vector_t` does not know anything about the types of objects stored as its elements, only the size
of an element in bytes. Because of this, the library's interface is expressed in terms of `void *`
pointers, which can lead to some cumbersome pointer casting to the correct type when accessing
elements:

```c
int value = *(int *)vector_get(vector, index);
```

Several convenience macros are defined in
[`vector_convenience_accessors.h`](https://github.com/ajsecord/vector_t/blob/master/vector_convenience_accessors.h)
to help reduce the verbosity:

```c
int value = VECTOR_GET(vector, index, int);
```

Similarly, setting the value of an element requires a temporary value on the stack:

```c
int value = 1;
vector_set(vector, index, &value);
```

Using the convenience macros, this is simplified to:
```c
VECTOR_SET(vector, index, 1);
```

## Controlling how the library interacts with the system

As an advanced option, it is possible to control how the library interacts with the system. For
example, the user can replace the memory allocator used by providing their own implementation of
[`realloc()`](https://linux.die.net/man/3/realloc) or how the library should react to catastrophic
problems by providing their own implementation of [`abort()`](https://linux.die.net/man/3/abort).
See [`vector_system.h`](https://github.com/ajsecord/vector_t/blob/master/vector_system.h) for more
information.

