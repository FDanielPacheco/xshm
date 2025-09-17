# xshm
A C library providing convenient wrappers around POSIX shared memory (shm_open, mmap, shm_unlink) for easier IPC.

With just a single call you can:
- Create or open a shared memory object
- Resize it to the desired capacity
- Map it into the process address space
- Cleanly unmap and unlink when done
