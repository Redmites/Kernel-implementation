
#ifndef PROJECT_BASE_V1_1_MEMALLOC_HPP
#define PROJECT_BASE_V1_1_MEMALLOC_HPP
#include "../lib/hw.h"

struct NumOfBlocks {
    size_t num;
};


class MemAlloc {

private:

    struct FreeMem {
        FreeMem *next;
        FreeMem *prev;
        size_t size;
    };

    static FreeMem *freeMemHead;



public:

    MemAlloc() = delete;

    static void setHead();

    static void* MemoryAllocFun (size_t size);
    static int MemoryFreeFun(void* beg);
    

};


#endif //PROJECT_BASE_V1_1_MEMALLOC_HPP
