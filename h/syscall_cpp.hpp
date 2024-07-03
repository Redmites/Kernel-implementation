
#ifndef PROJECT_BASE_V1_1_SYSCALL_CPP_HPP
#define PROJECT_BASE_V1_1_SYSCALL_CPP_HPP
#include "syscall_c.hpp"


class Thread {
public:

    void *operator new(size_t n){
        void* beg = mem_alloc(n);
        return beg;
    }

    void operator delete(void *p) {

        mem_free(p);
    }

    static void callingRun(Thread* param){param->run();}

    Thread (void (*body)(void*), void* arg);
    virtual ~Thread (){}
    int start ();
    static void dispatch ();
    //static int sleep (time_t);
protected:
    Thread ();
    virtual void run () {}
private:
    thread_t myHandle;
};





class Semaphore {
public:

    void *operator new(size_t n){
        return mem_alloc(n);
    }

    void operator delete(void *p) {
        mem_free(p);
    }







    Semaphore (unsigned init = 1);
    virtual ~Semaphore ();
    int wait ();
    int signal ();

protected:



private:
    sem_t myHandle;
};



class Console {
public:
    static char getc ();
    static void putc (char c);
};




#endif //PROJECT_BASE_V1_1_SYSCALL_CPP_HPP
