#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/wait.h>

int _nproc = 0;
int *_count;
sem_t *_barrier, *_mutex;
int _shmid, _shmid2;

void init_barrier(int numproc)
{
  _nproc = numproc;

  // Create shared memory for semaphores and count
  _shmid = shmget(IPC_PRIVATE, 2 * sizeof(sem_t), IPC_CREAT | 0600);
  _shmid2 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);

  // Attach to the shared memory
  _barrier = (sem_t *)shmat(_shmid, NULL, 0);
  _mutex = (sem_t *)(_barrier + 1); // Pointer arithmetic to next sem_t
  _count = (int *)shmat(_shmid2, NULL, 0);

  // Initialize shared variables
  _count[0] = 0;

  // Initialize semaphores
  sem_init(_barrier, 1, 0); // Barrier semaphore, starts at 0
  sem_init(_mutex, 1, 1);   // Mutex semaphore, starts at 1 (for mutual exclusion)
}

void reach_barrier()
{
  // Lock the mutex to update count
  sem_wait(_mutex);
  _count[0]++;

  if (_count[0] >= _nproc)
  {
    // Last process to arrive releases the barrier
    sem_post(_barrier);
  }
  sem_post(_mutex); // Unlock the mutex

  // Wait at the barrier if not the last process
  sem_wait(_barrier);

  // Once woken up, let the next process through
  sem_post(_barrier);
}

void destroy_barrier(int my_pid)
{
  if (my_pid != 0)
  {
    // Parent process: destroy semaphores and free shared memory
    sem_destroy(_barrier);
    sem_destroy(_mutex);
    shmdt(_barrier);
    shmdt(_count);
    shmctl(_shmid, IPC_RMID, NULL);
    shmctl(_shmid2, IPC_RMID, NULL);
  }
}
