
#include "../h/print.hpp"
#include "../h/trapHandler.hpp"
#include "../h/MemAlloc.hpp"
#include "../h/KernelClassThread.hpp"

extern int userMain();

void callingUserMain(void* args){
    userMain();
}

thread_t t2;
thread_t t;


void main()
{

    MemAlloc::setHead();


    __asm__ volatile ("csrw stvec, %[vector]" : : [vector] "r" (&trapHandler::supervisorTrap));



    KernelClassThread::createThreadNoStart(&t2, nullptr, nullptr, nullptr);
    KernelClassThread::running = t2;


    thread_create(&t, callingUserMain, nullptr);

    while(!t->isFinished()) {

        thread_dispatch();

    }


}