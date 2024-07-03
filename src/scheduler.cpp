
#include "../h/scheduler.hpp"

KernelClassThread *Scheduler::get()
{
    return KernelClassThread::removeFirst();
}

void Scheduler::put(KernelClassThread *KCT)
{
    KernelClassThread::addLast(KCT);
}