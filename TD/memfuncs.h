#ifndef MEMFUNCS_H
#define MEMFUNCS_H

#include<stdint.h>

extern void* memset(const void* start, int32_t val, uint32_t len);
extern void* memcpy(const void* source, void* dest, uint32_t len);
extern int8_t memcmp(const void* source, const void* dest, uint32_t len);
extern void* memove(const void* source, void* dest, uint32_t len);

#endif