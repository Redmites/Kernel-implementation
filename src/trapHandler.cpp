
#include "../h/trapHandler.hpp"
#include "../h/MemAlloc.hpp"
#include "../h/riscv.hpp"
#include "../h/syscall_c.hpp"
#include "../h/KernelClassThread.hpp"
#include "../h/KernelClassSemaphore.hpp"
#include "../lib/console.h"



void trapHandler::handleSupervisorTrap() {



    size_t scause;
    //__asm__ volatile ("mv %[code], a0" : [code] "=r" (codeOfOperation));
    scause = Riscv::r_scause();

    if(scause == (1ul<<63 | 1)){
        asm volatile ("csrc sip, 0b10");
        return;
    }


    if(scause == (1ul<<63 | 9)){

        console_handler();

        return;
    }

    /*if (scause == 2 || scause == 5 ||scause == 7){
        putc('k');
    }*/


    size_t codeOfOperation;
    __asm__ volatile ("mv %[code], a0" : [code] "=r" (codeOfOperation));

    uint64 first;
    uint64 second;
    uint64 third;

    __asm__ volatile ("mv %[arg1], a1" : [arg1] "=r" (first):);
    __asm__ volatile ("mv %[arg2], a2" : [arg2] "=r" (second):);
    __asm__ volatile ("mv %[arg3], a3" : [arg3] "=r" (third):);


    if (codeOfOperation == 0x01){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();

        size_t param = (size_t) first;
        void* retV;

        retV = MemAlloc::MemoryAllocFun(param);

        __asm__ volatile ("mv a0, %[retV]" : : [retV] "r" (retV));
        __asm__ volatile ("sd a0, 0x50(s0)");

        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);

    }

    else if (codeOfOperation == 0x02){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();

        void* param = (void*) first;
        int retV;

        retV = MemAlloc::MemoryFreeFun(param);

        __asm__ volatile ("mv a0, %[retV]" : : [retV] "r" (retV));
        __asm__ volatile ("sd a0, 0x50(s0)");

        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);

    }

    else if (codeOfOperation == 0x11){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();

        void (*start_routine2)(void*) = (void(*)(void*))(second);
        void* arg2 = (void*) third;
        int retV;
        void* stackPointer;

        __asm__ volatile ("ld a4, 0x70(s0)");
        __asm__ volatile ("mv %[arg4], a4" : [arg4] "=r" (stackPointer):);

        retV = KernelClassThread::createThread((thread_t*)first,start_routine2,arg2,stackPointer);

        __asm__ volatile ("mv a0, %[retV]" : : [retV] "r" (retV));

        __asm__ volatile ("sd a0, 0x50(s0)");


        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);


    }

    else if (codeOfOperation == 0x12){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();

        int retV;

        retV = KernelClassThread::threadExit();

        __asm__ volatile ("mv a0, %[retV]" : : [retV] "r" (retV));
        __asm__ volatile ("sd a0, 0x50(s0)");

        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);


    }

    else if (codeOfOperation == 0x13){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();


        KernelClassThread::dispatch();

        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);

    }

    else if (codeOfOperation == 0x14){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();

        void (*start_routine2)(void*) = (void(*)(void*))(second);
        void* arg2 = (void*) third;
        int retV;
        void* stackPointer;

        __asm__ volatile ("ld a4, 0x70(s0)");
        __asm__ volatile ("mv %[arg4], a4" : [arg4] "=r" (stackPointer):);

        retV = KernelClassThread::createThreadNoStart((thread_t*)first,start_routine2,arg2,stackPointer);

        __asm__ volatile ("mv a0, %[retV]" : : [retV] "r" (retV));

        __asm__ volatile ("sd a0, 0x50(s0)");


        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);


    }

    else if (codeOfOperation == 0x15){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();

        Scheduler::put((KernelClassThread*)first);

        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);

    }

    else if (codeOfOperation == 0x41){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();

        char retV;

        retV = __getc();

        __asm__ volatile ("mv a0, %[retV]" : : [retV] "r" (retV));
        __asm__ volatile ("sd a0, 0x50(s0)");



        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);

    }

    else if (codeOfOperation == 0x42){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();

        char param = (char) first;

        __putc(param);

        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);

    }

    else if (codeOfOperation == 0x21){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();

        int retV;

        retV = KernelClassSemaphore::open((sem_t*)first, (unsigned)second);

        __asm__ volatile ("mv a0, %[retV]" : : [retV] "r" (retV));
        __asm__ volatile ("sd a0, 0x50(s0)");

        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);

    }

    else if (codeOfOperation == 0x22){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();

        int retV;

        retV = KernelClassSemaphore::close((sem_t)first);


        __asm__ volatile ("mv a0, %[retV]" : : [retV] "r" (retV));
        __asm__ volatile ("sd a0, 0x50(s0)");

        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);

    }

    else if (codeOfOperation == 0x23){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();

        int retV;

        retV = KernelClassSemaphore::wait((sem_t)first);

        __asm__ volatile ("mv a0, %[retV]" : : [retV] "r" (retV));
        __asm__ volatile ("sd a0, 0x50(s0)");

        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);

    }

    else if (codeOfOperation == 0x24){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();

        int retV;

        retV = KernelClassSemaphore::signal((sem_t)first);

        __asm__ volatile ("mv a0, %[retV]" : : [retV] "r" (retV));
        __asm__ volatile ("sd a0, 0x50(s0)");

        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);

    }

    else if (codeOfOperation == 0x43){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();


        Riscv::mc_sstatus(Riscv::SSTATUS_SPP);

        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);

    }

    else if (codeOfOperation == 0x44){

        uint64 sepc = Riscv::r_sepc() + 4;
        uint64 sstatus = Riscv::r_sstatus();


        Riscv::ms_sstatus(Riscv::SSTATUS_SPP);

        Riscv::w_sstatus(sstatus);
        Riscv::w_sepc(sepc);

    }





}
