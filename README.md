Simple to use dynamic array.
============================

## Example
``` c
#include <stdio.h>
#include "dynamicArray.h"

int main() {
    char *str1 = "hello";
    char *str2 = ", wor";
    char *str3 = "ld!\n";
    
    dynArray array = dynA_init();

    dynA_append(array, str1);
    dynA_append(array, str2);
    dynA_append(array, str3);

    unsigned long i = 0;
    for(; i < dynA_size(array); i++) {
        printf(dynA_get(array, i));
    }
    return 0;
}
```
