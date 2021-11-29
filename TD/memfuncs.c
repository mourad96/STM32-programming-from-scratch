#include <stdint.h>
#include "memfuncs.h"

void* memset(const void* start, int32_t val, uint32_t len) {
	uint8_t* dest = (uint8_t*) start;

	while(len--)
		*dest++ = val;

	return (void*) start;
}

void* memcpy(const void* source, void* dest, uint32_t len) {
	
	uint8_t* dst = dest;
	const uint8_t* src = (const uint8_t*) source;

	while(len--)
		*dst++ = *src++;

	return dest;
}

int8_t memcmp(const void* src1, const void* src2, uint32_t len) {
	const uint8_t* s1 = (const uint8_t*) src1;
	const uint8_t* s2 = (const uint8_t*) src2;

	while(len--) {
		if(*s1++ != *s2++)
			return s1[-1] < s2[-1] ? -1 : 1;
	}

	return 0;
}

void* memmove(const void* source, void* dest, uint32_t len) {
	const uint8_t* s = (const uint8_t*) source;
	uint8_t* d = (uint8_t*) dest;

		if(d < s) {
			memcpy(s,d,len);
		} else {
			uint8_t *lasts = (uint8_t*)s + len - 1;
			uint8_t *lastd = (uint8_t*)d + len - 1;

			while(len--)
				*lastd++ = *lasts++;

		}

	return dest;
}


