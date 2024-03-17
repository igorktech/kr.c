
// mystrcpy.h

#ifndef MYSTRCPY_H
#define MYSTRCPY_H

// Simple implementation of strcpy using inline
 char* mystrcpy(char* dest, const char* src) {
    char* ret = dest;
    while ((*dest++ = *src++))
        ;
    return ret;
}

#endif // MYSTRCPY_H
