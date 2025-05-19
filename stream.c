#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

ssize_t getdelim(char **bufptr, size_t *n, int delim, FILE *fp) {
	char *buf;
	char *ptr;
	size_t newsize, numbytes;
	int pos;
	int ch;
	int cont;
	if(fp == NULL || bufptr == NULL || n == NULL) {
    	errno = EINVAL;
    	return -1;
	}
  	buf = *bufptr;
  	if(buf == NULL || *n < 4) {
    	buf = (char *)realloc (*bufptr, 128);
    	if(buf == NULL) {
	  		return -1;
        }
      	*bufptr = buf;
      	*n = 128;
    }
  	numbytes = *n;
  	ptr = buf;
 	cont = 1;
  	while(cont) {
      	while(--numbytes > 0) {
          	if((ch = getc_unlocked (fp)) == EOF) {
	      		cont = 0;
              	break;
            }
	  		else {
              	*ptr++ = ch;
              	if(ch == delim) {
                  	cont = 0;
                  	break;
                }
            }
        }
      	if(cont) {
          	pos = ptr - buf;
          	newsize = (*n << 1);
          	buf = realloc(buf, newsize);
          	if(buf == NULL) {
              	cont = 0;
              	break;
            }
          	*bufptr = buf;
          	*n = newsize;
          	ptr = buf + pos;
          	numbytes = newsize - pos;
        }
    }
  	if(ptr == buf) {
    	return -1;
    }
  	*ptr = '\0';
  	return (ssize_t)(ptr - buf);
}

ssize_t getline(char **lptr, size_t *n, FILE *fp) {
  	return getdelim(lptr, n, '\n', fp);
}