
#include "../h/syscall_c.hpp"
#include "../h/KernelClassThread.hpp"
#include "../lib/console.h"


void* mem_alloc (size_t size){

    void* retval = nullptr;
    size_t numOfBlocks = (size + sizeof(size_t)) / 64 + 1;

    __asm__ volatile ("mv a1, %[param]" : : [param] "r" (numOfBlocks));
    __asm__ volatile ("mv a0, %[code]": : [code] "r" (0x01));

    __asm__ volatile ("ecall");

    __asm__ volatile ("mv %[ret], a0" : [ret] "=r" (retval));

    return retval;

}

int mem_free (void* pointer){

    int retval = -1;

    __asm__ volatile ("mv a1, %[param]" : : [param] "r" (pointer));
    __asm__ volatile ("mv a0, %[code]": : [code] "r" (0x02));

    __asm__ volatile ("ecall");

    __asm__ volatile ("mv %[ret], a0" : [ret] "=r" (retval));

    return retval;

}


int thread_create (thread_t* handle, void(*start_routine)(void*), void* arg){

    int retval = -1;

    void* stackPointer;

    stackPointer = mem_alloc(DEFAULT_STACK_SIZE);

    __asm__ volatile ("mv a4, %[param4]" : : [param4] "r" (stackPointer));
    __asm__ volatile ("mv a3, %[param3]" : : [param3] "r" (arg));
    __asm__ volatile ("mv a2, %[param2]" : : [param2] "r" (start_routine));
    __asm__ volatile ("mv a1, %[param1]" : : [param1] "r" (handle));


    __asm__ volatile ("mv a0, %[code]": : [code] "r" (0x11));

    __asm__ volatile ("ecall");

    __asm__ volatile ("mv %[ret], a0" : [ret] "=r" (retval));

    return retval;


}


int thread_exit (){

    int retval = -1;

    __asm__ volatile ("mv a0, %[code]": : [code] "r" (0x12));
    __asm__ volatile ("ecall");

    __asm__ volatile ("mv %[ret], a0" : [ret] "=r" (retval));

    return retval;
}



void thread_dispatch (){

    __asm__ volatile ("mv a0, %[code]": : [code] "r" (0x13));
    __asm__ volatile ("ecall");

    return;
}

int thread_create_noStart (thread_t* handle, void(*start_routine)(void*), void* arg){

    int retval = -1;

    void* stackPointer;

    stackPointer = mem_alloc(DEFAULT_STACK_SIZE);

    __asm__ volatile ("mv a4, %[param4]" : : [param4] "r" (stackPointer));
    __asm__ volatile ("mv a3, %[param3]" : : [param3] "r" (arg));
    __asm__ volatile ("mv a2, %[param2]" : : [param2] "r" (start_routine));
    __asm__ volatile ("mv a1, %[param1]" : : [param1] "r" (handle));


    __asm__ volatile ("mv a0, %[code]": : [code] "r" (0x14));

    __asm__ volatile ("ecall");

    __asm__ volatile ("mv %[ret], a0" : [ret] "=r" (retval));

    return retval;





}

void thread_start(KernelClassThread* k){

    __asm__ volatile ("mv a1, %[param1]" : : [param1] "r" (k));

    __asm__ volatile ("mv a0, %[code]": : [code] "r" (0x15));
    __asm__ volatile ("ecall");

    return;

}



char getc(){


    return __getc();

}

void putc(char c){



    return __putc(c);


}


int sem_open (sem_t* handle, unsigned init){

    int retval = -1;


    __asm__ volatile ("mv a2, %[param2]" : : [param2] "r" (init));
    __asm__ volatile ("mv a1, %[param1]" : : [param1] "r" (handle));


    __asm__ volatile ("mv a0, %[code]": : [code] "r" (0x21));

    __asm__ volatile ("ecall");

    __asm__ volatile ("mv %[ret], a0" : [ret] "=r" (retval));

    return retval;
}

int sem_close (sem_t handle){

    int retval = -1;

    __asm__ volatile ("mv a1, %[param]" : : [param] "r" (handle));
    __asm__ volatile ("mv a0, %[code]": : [code] "r" (0x22));

    __asm__ volatile ("ecall");

    __asm__ volatile ("mv %[ret], a0" : [ret] "=r" (retval));

    return retval;

}

int sem_wait (sem_t id){

    int retval = -1;

    __asm__ volatile ("mv a1, %[param]" : : [param] "r" (id));
    __asm__ volatile ("mv a0, %[code]": : [code] "r" (0x23));

    __asm__ volatile ("ecall");

    __asm__ volatile ("mv %[ret], a0" : [ret] "=r" (retval));

    return retval;

}

int sem_signal (sem_t id){

    int retval = -1;

    __asm__ volatile ("mv a1, %[param]" : : [param] "r" (id));
    __asm__ volatile ("mv a0, %[code]": : [code] "r" (0x24));

    __asm__ volatile ("ecall");

    __asm__ volatile ("mv %[ret], a0" : [ret] "=r" (retval));

    return retval;

}


void sys_mode(){

    __asm__ volatile ("mv a0, %[code]": : [code] "r" (0x43));
    __asm__ volatile ("ecall");

    return;

}

void user_mode(){

    __asm__ volatile ("mv a0, %[code]": : [code] "r" (0x44));
    __asm__ volatile ("ecall");

    return;

}















