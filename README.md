# uMalloc
The [User-level Memory-mapped I/O (uMMAP-IO)](https://github.com/sergiorg-kth/ummap-io) provides scientific applications with a high-performance implementation to access storage devices using simple memory operations.

While the interface for uMMAP-IO includes a novel set of features (e.g., evict policies), the current specification can be considered low-level to application developers. Thus, this repository provides a "malloc-like" interface, **uMalloc**, to simplify the configuration and use of the library.

## How to compile and use the library
Compiling **uMalloc** is rather simple. First and foremost, after you clone the repository, ensure that the uMMAP-IO submodule is loaded:

```
git clone https://github.com/sergiorg-kth/umalloc.git
cd umalloc/
git submodule update --init
```

After this, access the `src` folder and type the following to compile the library and a simple source code example:

```
cd src/
make rebuild
```

If the compilation is successful, you will now observe inside `umalloc/` a new `build/` folder that contains the following structure:

- `umalloc/build/bin`: The executable of the source code example is located here.

The source code example can be executed directly. By default, a 1GB file will be created. You can observe whether the output was correct or not by typing the following:

```
hexdump example.data

```

That is all!

## Known Limitations
Given the release stage of uMMAP-IO, the following limitations must be considered before using the library:

- Multi-threaded or shared compute node (i.e., two users running different jobs) are not supported.
- The file size will always be multiple of the segment size.

## Disclaimer
The library is considered an Alpha release, meaning that it cannot be guaranteed a bug-free implementation. Nonetheless, we kindly ask you to report any issues that you encounter while using it.
