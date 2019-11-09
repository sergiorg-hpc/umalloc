
#include "common.h"
#include "ummap.h"
#include "umalloc.h"

///////////////////////////////////
// PRIVATE DEFINITIONS & METHODS //
///////////////////////////////////

#define PROT_FULL    (PROT_READ | PROT_WRITE)
#define FILE_FLAGS   (O_CREAT   | O_RDWR)
#define FILE_MODE    (S_IRUSR   | S_IWUSR)
#define SEG_SIZE     1048576
#define EVICT_POLICY 5 // WIRO-L


//////////////////////////////////
// PUBLIC DEFINITIONS & METHODS //
//////////////////////////////////

void* umalloc(const char *filename, size_t size) __CHK_FN__
{
    const size_t page_size = sysconf(_SC_PAGESIZE);
    const size_t seg_size  = (SEG_SIZE < page_size) ? page_size : SEG_SIZE;
    const size_t num_seg   = (size + (seg_size - 1)) / seg_size;
    const int    read_file = !access(filename, F_OK);
    int          fd        = -1;
    void         *addr     = NULL;
    
    // Open the file descriptor for the mapping
    fd = open(filename, FILE_FLAGS, FILE_MODE);
    CHKB((fd < 0), errno);
    
    // Update the size to be a multiple of the segment size
    size = seg_size * num_seg;
    
    // Ensure that the file has the proper space
    CHK(ftruncate(fd, size));

    // Create the memory-mapping with uMMAP-IO
    CHK(ummap(size, seg_size, PROT_FULL, fd, 0, -1, read_file, EVICT_POLICY,
              &addr));

    // Finally, close the file descriptor
    CHK(close(fd));
    
    return CHK_VALUE(addr, {
                               // If an error is encountered, delete the file
                               if (fd >= 0) close(fd);
                               if (!read_file) unlink(filename);
                           });
}

int usync(void *addr)
{
    return umsync(addr, FALSE);
}

int ufree(void *addr)
{
    return umunmap(addr, FALSE);
}

