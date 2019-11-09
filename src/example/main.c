#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "umalloc.h"

// Macro to avoid duplicating the error-checking code
#define CHKB(b) \
    if (!(b)) { \
        fprintf(stderr, "Error: %s (errno=%d)\n", strerror(errno), errno); \
        return -1; \
    }

int main(int argc, char **argv)
{
    int    hr   = 0;
    size_t size = 1073741824; // 1GB allocation
    int8_t *ptr = NULL;       // Base pointer

    // Create the file-backed allocation
    ptr = umalloc("./example.data", size);
    CHKB(ptr != NULL);

    // Set some random value on the allocation
    for (off_t i = 0; i < size; i++)
    {
        ptr[i] = 21;
    }

    // Alternative: Use traditional mem. functions
    memset(ptr, 21, size);

    // Synchronize with storage to ensure that the latest changes are flushed
    hr = usync(ptr);
    CHKB(hr == 0);

    // Finally, release the allocation
    hr = ufree(ptr);
    CHKB(hr == 0);
    
    return 0;
}

