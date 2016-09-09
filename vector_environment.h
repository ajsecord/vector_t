#ifndef VECTOR_ENVIRONMENT_H
#define VECTOR_ENVIRONMENT_H

/** Declares a function as extern in both C++ and C compilation. */
#ifdef __cplusplus
#   define VECTOR_EXTERN extern "C"
#else
#   define VECTOR_EXTERN extern
#endif

#endif
