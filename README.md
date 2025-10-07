# xshm
`xshm` is a lightweight C library designed to simplify Inter-Process Communication (IPC) using POSIX Shared Memory. It provides concise wrappers that abstract the complexities of shm_open, ftruncate, and mmap into single-function calls, allowing applications to map and access shared memory segments just like standard C pointers allocated with malloc.

For example, enabling communication between two or more processes that do not share a parent process can be complicated. With `xshm`, processes only need to know the name of the shared memory segment; once mapped, they can read and write to it directly as if it were normal memory, making IPC straightforward and efficient.

Currently, the library does not include synchronization methodologies, this must be applied by the user to ensure no racing conditions.

---

## Installation

### Prebuilt binaries

Available platforms:
- `x86_64-linux-gnu` (Intel/AMD)
- `arm-linux-gnueabihf` (e.g. Raspberry Pi 32-bit CPU)
- `aarch64-linux-gnu` (e.g. Raspberry Pi 64-bit CPU)

```bash
# Download and extract pre-compiled library
wget https://github.com/FDanielPacheco/xshm/releases/download/alpha/libxshm-<platform>.zip
unzip libxshm-<platform>.zip

# Install using the provided script
chmod u+x install.sh
./install.sh 
```

### Build from source

Build Requirements:
- clang: Compiler frontend and Linker
- opt: Optimizer
- llc: Compiler backend
- llvm-ar: Build static library 
- C Standard Library (lc)

```bash
sudo apt install build-essential llvm clang 
```

Clone the repository:
```bash
git clone https://github.com/FDanielPacheco/xshm.git
cd xshm
```

Build the dynamic library for the host platform:
```bash
make
```

Build the dynamic library for all platforms listed above:
```bash
make all
```

Build for a specific target and type independent on the host platform (require the dynamic/static libraries for that platform):
```bash
make release TARGET_ARCH_LLC=<arch> TARGET_ARCH_CC=<triplet> TYPE=<so|a> CF=-fPIC LF="-relocation-model=pic"
```

`<arch,triplet>` examples:
- `arm`, `arm-linux-gnueabihf`
- `x86-64`, `x86_64-linux-gnu`
- `aarch64`, `aarch64-linux-gnu`
 
`<TYPE>`: Dynamic: so | Static: a

---
## Usage Example 

```c
#include <xshm.h>
#include <sys/mman.h> // Required for O_CREAT, O_RDWR, etc.
#include <errno.h>
#include <string.h>

int
main( void ){
  const char * path = "/my_shared_int"; // Must start with a slash
  const size_t size = sizeof(int);
  
  // 1. Create and map the shared memory segment
  // O_CREAT: create if it doesn't exist
  // 0666: Read/Write permissions for all
  int * shared_int = (int *)shm_open2(
    path, 
    size, 
    O_CREAT | O_RDWR, 
    0666
  );
  
  if( !shared_int ){
    fprintf(stderr, "Error opening shared memory: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  
  printf("Shared memory created. Initializing to 42.\n");
  *shared_int = 42;
  
  // 2. Unmap and Unlink the shared memory
  // Passing the path as non-NULL unlinks the segment from the filesystem
  int ret = shm_close2(
    path, 
    shared_int, 
    size
  );

  if( -1 == ret ){
    fprintf(stderr, "Error closing shared memory: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  
  printf("Shared memory unmapped and unlinked successfully.\n");
  return 0;
}
```

### Included example

```bash
make example

./build/example
```
Follow the instructions provided to validate the shared memory between processes using `hexdump`.

## Documentation

API documentation generation (from xshm directory):
```bash
make documentation
```
Manual pages: `man docs/man/man3/xshm.c.3` or `man docs/man/man3/xshm.h.3` \
HTML docs: `firefox docs/html/index.html`

Additional:
- [Shared Memory Linux Library](https://man7.org/linux/man-pages/man3/shm_open.3.html)

---
## Author

Fábio D. Pacheco \
Email: fabio.d.pacheco@inesctec.pt

## License

[The 2-Clause BSD License](https://opensource.org/license/bsd-2-clause) 