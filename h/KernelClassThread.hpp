
#ifndef PROJECT_BASE_V1_1_KERNELCLASSTHREAD_HPP
#define PROJECT_BASE_V1_1_KERNELCLASSTHREAD_HPP

#include "../lib/hw.h"
#include "../h/scheduler.hpp"
#include "../h/syscall_c.hpp"
#include "../h/MemAlloc.hpp"



class KernelClassThread {

public:

    void *operator new(size_t n){
        size_t k = (n+sizeof (NumOfBlocks))/MEM_BLOCK_SIZE + 1;
        return MemAlloc::MemoryAllocFun(k);
    }

    void operator delete(void *p) {
        MemAlloc::MemoryFreeFun(p);
    }


    ~KernelClassThread() { MemAlloc::MemoryFreeFun(stack); }

    bool isFinished() const { return finished; }

    void setFinished(bool value) { finished = value; }

    void setSemBlocked(){semBlocked = true;}
    void resetSemBlocked(){semBlocked = false;}

    using Body = void (*)(void*);

    static int createThread(thread_t *handle ,Body body,void* arg, void* stackSpace );
    static int createThreadNoStart(thread_t *handle ,Body body,void* arg, void* stackSpace );

    static int threadExit();

    static void dispatch();

    static void threadWrapper();

    static void yield();

    static KernelClassThread *running;


    static KernelClassThread *headThread;
    static KernelClassThread *tailThread;


    static void addLast(KernelClassThread* k);

    static KernelClassThread* removeFirst();

    KernelClassThread* nextThread;



private:



    static uint64 constexpr STACK_SIZE = 4096;

    explicit KernelClassThread(Body body, void* arg, void* stackSpace ) :
            body(body), stack(body != nullptr ? (uint64*)stackSpace  : nullptr),
            context({(uint64) &threadWrapper,
                     stack != nullptr ? (uint64) stackSpace + DEFAULT_STACK_SIZE : 0}),
                     arguments(arg),
            finished(false){ if (body != nullptr) { }}


    struct Context
    {
        uint64 ra;
        uint64 sp;
    };

    Body body;
    uint64 *stack;
    Context context;
    void* arguments;
    bool finished;
    bool semBlocked;

    static void contextSwitch(Context *oldContext, Context *runningContext);



};


#endif //PROJECT_BASE_V1_1_KERNELCLASSTHREAD_HPP
