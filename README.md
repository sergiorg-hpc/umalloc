# uMalloc: A simple wrapper of uMMAP-IO
The [User-level Memory-mapped I/O (uMMAP-IO)](https://github.com/sergiorg-kth/ummap-io) provides scientific applications with a high-performance implementation to access storage devices using simple memory operations.

While the interface for uMMAP-IO includes a novel set of features (e.g., evict policies), the current specification can be considered very low-level to application developers. As a consequence, this repository provides a "malloc-like" interface, **uMalloc**, to simplify the configuration and use of the library.

## Programming Interface
As with uMMAP-IO, accessing files on storage is possible by performing simple `load` / `store` operations. By default, **uMalloc** will configure the mapping with the most common settings for uMMAP-IO, such as using a segment size of 1MB (or equivalently matching the page size if huge-pages is configured). The interface for **uMalloc** is listed below:

```
void* umalloc(const char *filename, size_t size);
int usync(void *addr);
int ufree(void *addr);
```

Requesting a file-backed allocation is very simple. The interface is almost identical to [`malloc`](http://man7.org/linux/man-pages/man3/malloc.3.html), except that here a `filename` is accepted to specify the path of the target file to be mapped. Moreover, if the file exists, **uMalloc** will configure the mapping to read the content when accessed (e.g., to restore a checkpoint).

The synchronization with storage is performed automatically when going out-of-core, or can be requested manually by calling `usync()` at any time. Finally, releasing the allocation is as simple as calling `ufree()`.

Note that these two latter functions will return `-1` and set `errno` when an error is encountered. The allocator will return a `NULL` pointer instead.


## How to compile and use the library
In order to compile **uMalloc**, you must ensure that the uMMAP-IO submodule is loaded after cloning the repository or when pulling new changes:

```
git clone https://github.com/sergiorg-kth/umalloc.git
cd umalloc/
git submodule update --init
```

The `src` folder contains the source code and all the necessary elements to compile. Type the following to compile both the library and a simple example application:

```
cd src/
make rebuild
```

If the compilation is successful, you will now observe inside `umalloc/` a new `build/` folder that contains the following structure:

- `umalloc/build/bin`: The executable of the source code example is located here.
- `umalloc/build/lib`: Static library for **uMalloc**, named `libumalloc.a`. It can be utilized to compile with your code by including `-lumalloc`. Optionally, some compilers might require `-pthread -lrt` as well.
- `umalloc/build/inc`: A header file, named `umalloc.h`, is provided with the definition of the API.
- `umalloc/build/...`: Other temporary folders might be created (ignore).

The source code example can be executed directly. By default, a 1GB file will be created. You can observe whether the output was correct or not by typing the following:

```
> hexdump example.data
0000000 1515 1515 1515 1515 1515 1515 1515 1515
*
40000000
```

That is all!

## Known Limitations
Given the release stage of uMMAP-IO, the following limitations must be considered before using the library:

- Multi-threaded or shared compute node (i.e., two users running different jobs) are not supported.
- The file size will always be multiple of the segment size.

## Disclaimer
The library is considered an Alpha release, meaning that it cannot be guaranteed a bug-free implementation. Nonetheless, we kindly ask you to report any issues that you encounter while using it.
