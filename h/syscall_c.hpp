
#ifndef PROJECT_BASE_V1_1_SYSCALL_C_HPP
#define PROJECT_BASE_V1_1_SYSCALL_C_HPP

#include "../lib/hw.h"




void* mem_alloc (size_t size);

int mem_free (void* pointer);


class KernelClassThread;
typedef KernelClassThread* thread_t;

int thread_create (thread_t* handle, void(*start_routine)(void*), void* arg);
int thread_create_noStart (thread_t* handle, void(*start_routine)(void*), void* arg);

void thread_start(KernelClassThread* k);

int thread_exit ();

void thread_dispatch ();

char getc();

void putc(char c);


//semafori


class KernelClassSemaphore;
typedef KernelClassSemaphore* sem_t;

int sem_open (sem_t* handle, unsigned init);

int sem_close (sem_t handle);

int sem_wait (sem_t id);

int sem_signal (sem_t id);

void sys_mode();

void user_mode();










#endif //PROJECT_BASE_V1_1_SYSCALL_C_HPP
