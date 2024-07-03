
#include "../h/syscall_cpp.hpp"




void Thread::dispatch() {
    thread_dispatch();
}

int Thread::start() {

    thread_start(myHandle);

    return 0;
}

/*int Thread::sleep(time_t) {
    return 0;
}*/

Thread::Thread(void (*body)(void *), void *arg) {
    thread_create_noStart(&myHandle, body, arg);

}

Thread::Thread() {


    void (*start_routine2)(void*) = (void(*)(void*))(callingRun);
    thread_create_noStart(&myHandle, start_routine2, this);


}

Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle, init);
}

int Semaphore::wait() {

    return sem_wait(myHandle);
}

int Semaphore::signal() {
    return sem_signal(myHandle);
}

Semaphore::~Semaphore() {
    sem_close(myHandle);
}

char Console::getc() {
    return ::getc();
}

void Console::putc(char c) {
    ::putc(c);
    return;
}


