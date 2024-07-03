
#include "../h/MemAlloc.hpp"



MemAlloc::FreeMem *MemAlloc::freeMemHead = nullptr;

void *MemAlloc::MemoryAllocFun(size_t size) {

    void* retvNumOfBlocks;
    void* retval = nullptr;
    int* retvInt;

    if (freeMemHead == nullptr){
        retvNumOfBlocks = (void*)HEAP_START_ADDR;
        retvInt = (int*)HEAP_START_ADDR + sizeof (NumOfBlocks);
        retval = (void*)retvInt;

        FreeMem* newf = (FreeMem*)((char*)retval+size*MEM_BLOCK_SIZE);

        newf->prev = nullptr;
        newf->next = nullptr;
        newf->size = ((char*)HEAP_END_ADDR - (char*)HEAP_START_ADDR)/MEM_BLOCK_SIZE - size*MEM_BLOCK_SIZE;

        NumOfBlocks* allocated = (NumOfBlocks*)((char*)retvNumOfBlocks);
        allocated->num = size;

        freeMemHead = newf;

        return retval;
    }
    else {
        for (FreeMem* cur= freeMemHead; cur!=0; cur=cur->next){
            if(cur->size < size) continue;



            else{
                retvNumOfBlocks = cur;
                retvInt = (int*)cur + sizeof (NumOfBlocks);
                retval = (void*)retvInt;

                FreeMem* newf = (FreeMem*)((char*)cur+size*64);
                if (cur->prev) cur->prev->next = newf;
                else freeMemHead = newf;
                if (cur->next) cur->next->prev = newf;
                newf->prev = cur->prev;
                newf->next = cur->next;
                newf->size = cur->size-size;

                NumOfBlocks* allocated = (NumOfBlocks*)((char*)retvNumOfBlocks);
                allocated->num = size;

                return retval;
            }
        }
    }
    return retval;
}

int MemAlloc::MemoryFreeFun(void *addr) {

    FreeMem* cur=0;

    void* addr2;
    addr2 = (uint64*) addr - sizeof (NumOfBlocks);

    if (!freeMemHead || addr2<(char*)freeMemHead) {
        cur = 0;
    }
    else {
        for (cur = freeMemHead; cur->next != 0 && addr2 > (char *) (cur->next); cur = cur->next);
    }


    if (cur && (char*)cur+(cur->size * 64)==addr2) {
        cur->size+=((NumOfBlocks*)addr2)->num;

        if (cur->next && (char*)cur+(cur->size * 64) == (char*)(cur->next)) {
            cur->size += cur->next->size;
            cur->next = cur->next->next;
            if (cur->next) cur->next->prev = cur;
        }
        return 0;
    }
    else {
        FreeMem *nxt = cur ? cur->next : freeMemHead;

        if (nxt && (char *) addr2 + ((NumOfBlocks *) addr2)->num * MEM_BLOCK_SIZE == (char *) nxt) {
            FreeMem *newSeg = (FreeMem *) addr2;
            newSeg->size = nxt->size + ((NumOfBlocks *) addr2)->num;
            newSeg->prev = nxt->prev;
            newSeg->next = nxt->next;
            if (nxt->next) nxt->next->prev = newSeg;
            if (nxt->prev) nxt->prev->next = newSeg;
            else freeMemHead = newSeg;
            return 0;
        }
        else {
            FreeMem *newSeg = (FreeMem *) addr2;

            newSeg->size = ((NumOfBlocks*)addr2)->num;
            newSeg->prev = cur;
            if (cur) newSeg->next = cur->next;
            else newSeg->next = freeMemHead;
            if (newSeg->next) newSeg->next->prev = newSeg;
            if (cur) cur->next = newSeg;
            else freeMemHead = newSeg;
            return 0;
        }
    }
}

void MemAlloc::setHead() {

    freeMemHead = nullptr;

}
