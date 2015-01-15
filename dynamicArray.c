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
 * This is kinda like a vector in c++, i hope.
 * @TODO This can't understand if it's as long as unsingned long.
 * @TODO Add a shrink to size function!
 */

#include "dynamicArray.h"

dynArray dynA_init() {
    int size = 256;
    struct dynamicArray *a = malloc(sizeof(struct dynamicArray));
    if(a == NULL)
        return NULL;
    a->currSize = 0;
    a->arrSize = size;
    a->array = malloc(sizeof(void*)*size);
    if(a->array == NULL) {
        free(a);
        return NULL;
    }
    dynArray ret = malloc(sizeof(struct dynamicArray*));
    (*ret) = a;
    return ret;
}

void dynA_setFreeFunc(dynArray a, void (*freeFunc)(void*)) {
    (*a)->clearFunc = freeFunc;
}

int dynA_append(dynArray a, void* val) {
    if(dynA_reachedLimit(a) < 0)
        return -1;
    (*a)->array[(*a)->currSize] = val;
    (*a)->currSize++;
    return 0;
}

// @TODO This funtion could be a bit more dynamic
int dynA_reachedLimit(dynArray a) {
    if((*a)->currSize+10 >= (*a)->arrSize) {
        if((*a)->arrSize *2 > (*a)->arrSize)
            return dynA_extend(a, (*a)->arrSize*2);
    }
    return 0;
}

int dynA_extend(dynArray a, unsigned long newSize) {
    void** newArr = realloc((*a)->array, sizeof(void*) * newSize);
    if(newArr == NULL)
        return -1;
    (*a)->array = newArr;
    (*a)->arrSize = newSize;
    return 0;
}

unsigned long dynA_size(dynArray a) {
    return (*a)->currSize;
}

int dynA_isEmpty(dynArray a) {
    return (a && (*a)->currSize == 0);
}

int dynA_remove(dynArray a, unsigned long index) {
    unsigned long i = index;
    unsigned long size = (*a)->currSize-1;
    for(; i < size; i++) {
        if((*a)->clearFunc != NULL)
            (*a)->clearFunc((*a)->array[i]);
        (*a)->array[i] = (*a)->array[i+1];
    }
    (*a)->currSize--;
    return 0;
}

int dynA_insert(dynArray a, unsigned long index, void* val) {
    if(dynA_reachedLimit(a) < 0)
        return -1;
    unsigned long i = (*a)->currSize;
    unsigned long place = index;
    for(; i > place ; i--){
        (*a)->array[i] = (*a)->array[i-1];
    }
    (*a)->array[index] = val;
    (*a)->currSize++;
    return 0;
}

void* dynA_get(dynArray a, unsigned long index) {
    if(index >= (*a)->currSize)
        return NULL;
    return (*a)->array[index];
}

int dynA_set(dynArray a, unsigned long index, void* val) {
    if(index >= (*a)->currSize)
        return -1;
    if((*a)->clearFunc != NULL)
        (*a)->clearFunc((*a)->array[index]);
    (*a)->array[index] = val;
    return 0;
}

int dynA_clear(dynArray a) {
    if((*a) == NULL)
        return -1;
    if((*a)->clearFunc != NULL && !dynA_isEmpty(a)) {
        unsigned long i = 0;
        for(; i < (*a)->currSize; i++)
            (*a)->clearFunc((*a)->array[i]);
    }
    free((*a)->array);
    free(*a);
    free(a);
    return 0;
}

void **dynA_getCArray(dynArray a) {
    return(*a)->array;
}




















