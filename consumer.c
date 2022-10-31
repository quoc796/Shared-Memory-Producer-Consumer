// C program for Consumer process illustrating
// POSIX shared-memory API.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include "shareContent.c"

int main()
{
	struct sharedContent* shms = getSharedContent();
	while (true)
    {
        // wait when empty
        sem_wait(&(shms->empty));
        // wait when another process is on the go
        sem_wait(&(shms->mutex));

        //enter crucial
        printf("processed: %s \n", shms->sharedMem[shms->out]);
        shms->out = (shms->out + 1)%2;
        //out crucial
        //processed 1 element of the stack
        sem_post(&(shms->full));
        sem_post(&(shms->mutex));
    }
    

	/* remove the shared memory object */
	shm_unlink(SHARE_MEMO_NAME);
	return 0;
}
