
#ifndef PROJECT_BASE_V1_1_SCHEDULER_HPP
#define PROJECT_BASE_V1_1_SCHEDULER_HPP

#include "../h/KernelClassThread.hpp"
#include "../h/MemAlloc.hpp"


class KernelClassThread;

class Scheduler
{

    void *operator new(size_t n){
        size_t k = (n+sizeof (NumOfBlocks))/64 + 1;
        void* beg = MemAlloc::MemoryAllocFun(k);
        return beg;
    }

    void operator delete(void *p) {

        MemAlloc::MemoryFreeFun(p);
    }

public:
    static KernelClassThread *get();

    static void put(KernelClassThread *KCT);

};


#endif //PROJECT_BASE_V1_1_SCHEDULER_HPP
