//
// Created by os on 9/15/22.
//

#ifndef PROJECT_BASE_V1_1_KERNELCLASSSEMAPHORE_HPP
#define PROJECT_BASE_V1_1_KERNELCLASSSEMAPHORE_HPP
#include "../h/KernelClassThread.hpp"



class KernelClassSemaphore {
    public:

    void *operator new(size_t n){
        size_t k = (n+sizeof (NumOfBlocks))/MEM_BLOCK_SIZE + 1;
        return MemAlloc::MemoryAllocFun(k);
    }

    void operator delete(void *p) {
        MemAlloc::MemoryFreeFun(p);
    }




        KernelClassSemaphore (unsigned short init);
        static int wait (KernelClassSemaphore* s);
        static int signal (KernelClassSemaphore* s);
        static int open(sem_t* handle, int i);
        static int close(sem_t id);

        void setSemClosed(){semClosed = true;}
        void resetSemClosed(){semClosed = false;}


        int value () const { return val; }
        KernelClassThread* semQueueBeg;
        KernelClassThread* semQueueEnd;


    protected:
        void block ();
        void unblock ();
    private:
        int val;
        bool semClosed;

    };


#endif //PROJECT_BASE_V1_1_KERNELCLASSSEMAPHORE_HPP
