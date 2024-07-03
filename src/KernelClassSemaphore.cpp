//
// Created by os on 9/15/22.
//

#include "../h/KernelClassSemaphore.hpp"




void KernelClassSemaphore::block() {

    if (semQueueBeg)
    {
        semQueueEnd->nextThread = KernelClassThread::running;
        semQueueEnd = KernelClassThread::running;
    } else
    {
        semQueueBeg = semQueueEnd = KernelClassThread::running;
    }
    semQueueEnd->nextThread = nullptr;
    KernelClassThread::running->setSemBlocked();

    KernelClassThread::dispatch();


}

void KernelClassSemaphore::unblock() {
    if (!semQueueBeg) { return; }

    KernelClassThread *k = semQueueBeg;
    semQueueBeg = semQueueBeg->nextThread;
    if (!semQueueBeg) { semQueueEnd = 0; }

    k->resetSemBlocked();

    k->nextThread = nullptr;

    Scheduler::put(k);

}

int KernelClassSemaphore::wait(KernelClassSemaphore* s) {

    if (s->semClosed){
       return -1;
    }

    if(--s->val<0) {
        s->block();

    }
    return 0;
}

int KernelClassSemaphore::signal(KernelClassSemaphore* s) {

    if (++s->val<=0) s->unblock();
    return  0;

}

int KernelClassSemaphore::open(sem_t *handle, int i) {
    *handle = new KernelClassSemaphore(i);
    (*handle)->resetSemClosed();
    return 0;
}

int KernelClassSemaphore::close(sem_t id) {
    id->setSemClosed();
    KernelClassThread* temp = id->semQueueBeg;
    if (temp == nullptr) return 0;
    while(temp != id->semQueueEnd){
        temp = temp->nextThread;
        id->unblock();
    }
    id->unblock();


    return 0;
}

KernelClassSemaphore::KernelClassSemaphore(unsigned short init) {
    val = init;
    semQueueBeg = nullptr;
    semQueueEnd = nullptr;
}
