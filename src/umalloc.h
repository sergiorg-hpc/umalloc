#ifndef _UMALLOC_H
#define _UMALLOC_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Establishes and configures a file-backed allocation, based on uMMAP-IO. 
 */
void* umalloc(const char *filename, size_t size);

/**
 * Performs a selective synchronization of the dirty segments, if needed.
 */
int usync(void *addr);

/**
 * Releases an existing file-backed allocation, based on uMMAP-IO.
 */
int ufree(void *addr);

#ifdef __cplusplus
}
#endif

#endif

