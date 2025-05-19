#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

size_t strnlen(const char *str, size_t max) {
    const char *result = memchr(str, 0, max);
    return result ? (size_t)(result - str) : max;
}

char *strndup(const char *str, size_t size) {
	char *result;
	size_t len = strlen(str);
	if(size < len) {
    	len = size;
	}
	result = (char *)malloc(len + 1);
	if(!result) {
		return 0;
	}
	result[len] = '\0';
	return (char *)memcpy(result, str, len);
}

