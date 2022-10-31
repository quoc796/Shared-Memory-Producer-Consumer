#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#define SHARE_MEMO_NAME "OS"
#define BUF_SIZE 2000
#define MES_SIZE 5
#define BUFFER_SIZE 2
#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                                   } while (0)
struct sharedContent
{
    int in;
    int out;
    sem_t mutex;
    sem_t empty;
    sem_t full;
    char sharedMem[BUFFER_SIZE][MES_SIZE];

};
struct sharedContent *getSharedContent()
{
    /* name of the shared memory object */

	/* shared memory file descriptor */
	int shm_fd;

	/* open the shared memory object */
	shm_fd = shm_open(SHARE_MEMO_NAME, O_CREAT|O_RDWR, 0666);
    ftruncate(shm_fd, BUF_SIZE);
	/* memory map the shared memory object */
	struct sharedContent *shms = mmap(NULL, sizeof(*shms),
                                          PROT_READ | PROT_WRITE,
                                          MAP_SHARED, shm_fd, 0);

   return shms;
}
void initSharedContent()
{
    /* name of the shared memory object */

	/* shared memory file descriptor */
	int shm_fd;

	/* open the shared memory object */
	shm_fd = shm_open(SHARE_MEMO_NAME, O_CREAT|O_RDWR, 0666);
    ftruncate(shm_fd, BUF_SIZE);
	/* memory map the shared memory object */
	struct sharedContent *shms = mmap(NULL, sizeof(*shms),
                                          PROT_READ | PROT_WRITE,
                                          MAP_SHARED, shm_fd, 0);

    shms->in = 0;
    shms->out = 0;
    sem_init(&(shms->mutex), 1, 0);
    sem_init(&(shms->empty), 1, 0);
    sem_init(&(shms->full), 1, BUFFER_SIZE);
}

