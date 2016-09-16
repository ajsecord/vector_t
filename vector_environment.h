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

#ifndef VECTOR_ENVIRONMENT_H
#define VECTOR_ENVIRONMENT_H

/**
 @file vector_environment.h
 
 Definitions for the compilation environment.
 */

/** Declares an object as extern in both C++ and C compilation. */
#ifdef __cplusplus
#   define VECTOR_EXTERN extern "C"
#else
#   define VECTOR_EXTERN extern
#endif

#endif
