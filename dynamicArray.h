/*
 *    Copyright 2015 Dennis Vesterlund
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

/**
 * Things will be here later...
 */

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdio.h>
#include <stdlib.h>

struct dynamicArray {
    void **array;
    unsigned long currSize;
    unsigned long arrSize;
    void (*clearFunc)(void*);
};

typedef struct dynamicArray **dynArray;

dynArray dynA_init();

void dynA_setFreeFunc(dynArray a, void (*freeFunc)(void*));

int dynA_append(dynArray a, void* val);

int dynA_reachedLimit(dynArray a);

int dynA_extend(dynArray a, unsigned long newSize);

unsigned long dynA_size(dynArray a);

int dynA_isEmpty(dynArray a);

int dynA_remove(dynArray a, unsigned long index);

int dynA_insert(dynArray a, unsigned long index, void* val);

void* dynA_get(dynArray a, unsigned long index);

int dynA_set(dynArray a, unsigned long index, void* val);

int dynA_clear(dynArray a);

void **dynA_getCArray(dynArray a);

#endif




















