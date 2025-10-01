# xshm
`xshm` is a lightweight C library designed to simplify Inter-Process Communication (IPC) using POSIX Shared Memory. It provides concise wrappers that combine the complexities of shm_open, ftruncate, and mmap into simple, single-function calls, allowing applications to quickly map and access shared memory segments as standard C pointers.

With just a single call you can:
- Create or open a shared memory object
- Resize it to the desired capacity
- Map it into the process address space
- Cleanly unmap and unlink when done

---
## Installation

### Requirements
- C Standard Library (libc)
- POSIX Standard Libraries

In Debian-based Linux:
```bash
sudo apt install build-essential
```

### Build from Source
Since this is a small header-only or very small-source library, a simple make process should suffice.

```
# Clone the repository
git clone https://github.com/FDanielPacheco/xshm
cd xshm

# Build
make 
```

### Installation
If using a dynamic library (libxshm.so), follow standard library installation procedures. If it is a header-only library, just copy the header file.

```
sudo cp xshm.h /usr/local/include/
sudo cp libxshm.so /usr/local/lib/
sudo ldconfig
```
---
## Usage Example

```c
#include <xshm.h>
#include <sys/mman.h> // Required for O_CREAT, O_RDWR, etc.
#include <errno.h>
#include <string.h>

int
main( ){
  const char * path = "/my_shared_int"; // Must start with a slash
  const size_t size = sizeof(int);
  int * shared_int;
  
  // 1. Create and map the shared memory segment
  // O_CREAT: create if it doesn't exist
  // 0666: Read/Write permissions for all
  shared_int = (int *)shm_open2(path, size, O_CREAT | O_RDWR, 0666);
  
  if( !shared_int ){
    fprintf(stderr, "Error opening shared memory: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  
  // Initialize or modify the shared data
  printf("Shared memory created. Initializing to 42.\n");
  *shared_int = 42;
  
  // 2. Unmap and Unlink the shared memory
  // Passing the path as non-NULL unlinks the segment from the filesystem
  if( -1 == shm_close2(path, shared_int, size) ){
    fprintf(stderr, "Error closing shared memory: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  
  printf("Shared memory unmapped and unlinked successfully.\n");
  return 0;
}
```

---
## Author
Fábio D. Pacheco \
Email: fabio.d.pacheco@inesctec.pt

## License

[The 2-Clause BSD License](https://opensource.org/license/bsd-2-clause) 
