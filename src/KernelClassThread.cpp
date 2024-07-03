
#include "../h/KernelClassThread.hpp"
#include "../h/riscv.hpp"

KernelClassThread *KernelClassThread::running = nullptr;
KernelClassThread *KernelClassThread::headThread = nullptr;
KernelClassThread *KernelClassThread::tailThread = nullptr;

int KernelClassThread::createThread(thread_t *handle ,Body body,void* arg, void* stackSpace )
{
    *handle  = new KernelClassThread(body, arg,stackSpace);
    (*handle)->resetSemBlocked();
    //addLast(*handle);
    Scheduler::put(*handle);
    return 0;
}

void KernelClassThread::yield()
{
    Riscv::pushRegisters();

    KernelClassThread::dispatch();

    Riscv::popRegisters();
}

void KernelClassThread::dispatch()
{
    KernelClassThread *old = running;
    if (!old->isFinished() && !old->semBlocked) { Scheduler::put(old); }
    running = Scheduler::get();
    KernelClassThread::contextSwitch(&old->context, &running->context);
}

void KernelClassThread::threadWrapper() {

    Riscv::popSppSpie();
    running->body(running->arguments);
    running->setFinished(true);
    thread_dispatch();

}

int KernelClassThread::threadExit() {

    running->setFinished(true);
    delete (running);
    thread_dispatch();

    return 0;
}

void KernelClassThread::addLast(KernelClassThread* k) {
    if (tailThread)
    {
        tailThread->nextThread = k;
        tailThread = k;
    } else
    {
        headThread = tailThread = k;
    }

    tailThread->nextThread = nullptr;
}

KernelClassThread *KernelClassThread::removeFirst() {
    if (!headThread) { return 0; }

    KernelClassThread *k = headThread;
    headThread = headThread->nextThread;
    if (!headThread) { tailThread = 0; }

    k->nextThread = nullptr;

    return k;
}

int KernelClassThread::createThreadNoStart(thread_t *handle, KernelClassThread::Body body, void *arg, void *stackSpace) {
    *handle  = new KernelClassThread(body, arg,stackSpace);
    (*handle)->resetSemBlocked();
    return 0;
}



