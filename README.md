# xshm
A C library providing safe, convenient wrappers around POSIX shared memory (shm_open, mmap, shm_unlink) for easier interprocess communication.

With just a single call you can:
- Create or open a shared memory object
- Resize it to the desired capacity
- Map it into the process address space
- Cleanly unmap and unlink when done

This makes it easier to use shared memory for IPC, without repeatedly writing the same setup/teardown code.
