#include <xshm.h>
#include <fcntl.h> // Required for O_CREAT, O_RDWR, etc.
#include <stdlib.h>  // Required for EXIT_FAILURE
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

  printf(
    "On other terminal do the command below, and you should see 42:\n"
    "$hexdump -v -e '1/4 \"%%d\\n\"' /dev/shm/my_shared_int\n\n"
    "Press enter to unlink the shared memory."
  );
  getchar( );
  
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
