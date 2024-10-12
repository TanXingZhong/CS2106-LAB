#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/shm.h>

int *count;
int nproc = 0;
int shmid, shmid2;
sem_t *sem;
sem_t *mutex;
sem_t *barrier;

void init_barrier(int numproc) {
  nproc = numproc;
  shmid = shmget(IPC_PRIVATE, 2 * sizeof(sem_t), IPC_CREAT | 0600);
  shmid2 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);

  sem = (sem_t *) shmat(shmid, NULL, 0);
  count = (int *) shmat(shmid2, NULL, 0);

  count[0] = 0;
  mutex = &sem[0];
  barrier = &sem[1];

  sem_init(mutex, 1, 1);
  sem_init(barrier, 1, 0);
}

void reach_barrier() {
  sem_wait(mutex);
    count[0] = count[0] + 1;
  sem_post(mutex);

  if(count[0] == nproc) {
    sem_post(barrier);
  } else {
    sem_wait(barrier);
    sem_post(barrier);
  }
}

void destroy_barrier(int my_pid) {
    if(my_pid != 0) {
        // Destroy the semaphores and detach
        // and free any shared memory. Notice
        // that we explicity check that it is
        // the parent doing it.
        sem_destroy(barrier);
        sem_destroy(mutex);
        shmdt(count);
        shmdt(sem);
        shmctl(shmid, IPC_RMID, 0);
        shmctl(shmid2, IPC_RMID, 0);
    }
}


