#include "MeM.h"
#include "stm32f10x.h"
typedef struct MeM_BlockHead {
    struct MeM_BlockHead *next;
    unsigned int available;   //该块是否被占用
    size_t size;              //实际大小，包含块头数据
    uint32_t placeHolder;

} MeM_BlockHead;

//1. KeilC
/** Macros for handling packed structs. */
//#define STRINGIZE(X) #X
//#define SL_PACK_START(X) _Pragma(STRINGIZE(pack(X)))
//#define SL_PACK_END()    _Pragma("pack()")
//#define SL_ATTRIBUTE_PACKED

/** MDK-ARM compiler: Macros for handling aligned structs. */
//#define SL_ALIGN(X) __align(X)
//2. IAR

/** Macros for handling packed structs. */
#define STRINGIZE(X) #X
//#define SL_PACK_START(X) _Pragma(STRINGIZE(pack(X)))
//#define SL_PACK_END()    _Pragma("pack()")
//#define SL_ATTRIBUTE_PACKED

/** IAR Embedded Workbench: Macros for handling aligned structs. */
#define SL_ALIGN(X) _pragma(STRINGIZE(data_alignment=X))
//3. Simplicity Studio

/** GCC style macro for handling packed structs. */
//#define SL_ATTRIBUTE_PACKED __attribute__ ((packed))
/** GCC style macro for aligning a variable. */
//#define SL_ATTRIBUTE_ALIGN(X) __attribute__ ((aligned(X)))

#pragma data_alignment = 32
volatile static u32 MeM_MemoryPool[MEMORY_MANAGE_POOL_SIZE/sizeof(u32)] ;

void MeM_Tidy(void){
    MeM_BlockHead *curBlock = (MeM_BlockHead *)MeM_MemoryPool;
    while (curBlock->next) {
        if (!curBlock->available) { //块被占用，找下一块
            curBlock = curBlock->next;
            continue;
        } else {                                                        //当前块可用
            if (curBlock->next->available) {                            //下一块也可用，则合并两块
                curBlock->size = curBlock->size + curBlock->next->size; //两块大小一加
                curBlock->next = curBlock->next->next;                  //指针指向下下块，下一块应该就消失了
                continue;
            } else { //下一块不可用
                curBlock = curBlock->next;
                continue;
            }
        }
    }
}

void *MeM_Request_Base(size_t size) {
    MeM_BlockHead *curBlock = (MeM_BlockHead *)MeM_MemoryPool;
    void *rtnAddr = NULL; //返回可用的地址

#ifdef MEMORY_MANAGE_MEMORY_REQUEST_STRATEGY_FAST_SPEED
    while (curBlock) {
        if (curBlock->available == false || curBlock->size < size) {
            curBlock = curBlock->next;
        } else { //找到符合要求的块
            break;
        }
    }
#endif

#ifdef MEMORY_MAMAGE_MEMORY_REQUEST_STRATEGY_LESS_FRAGMENTATION
    MeM_BlockHead *bestBlock = NULL;
    size_t bestBlockSize = MEMORY_MANAGE_POOL_SIZE;
    while (curBlock) {
        if (curBlock->available == true && curBlock->size >= size) { //找到一块可用
            if(curBlock.size==size){//刚刚好！就是它了
                bestBlock = curBlock;
                bestBlockSize = curBlock->size;
                break;
            }
            if (curBlock->size < bestBlockSize) {
                bestBlock = curBlock;
                bestBlockSize = curBlock->size;
            }
        }
        curBlock = curBlock->next;
    }
    curBlock = bestBlock;

#endif

    if (!curBlock) { //没找到合适的
        return NULL;
    }
    //切割当前块
    curBlock->available = false; //标记为占用
    //将当前块切割成两块，前者被占用，后者为未被占用的空闲空间
    MeM_BlockHead *newBlock = (MeM_BlockHead *)((unsigned int)curBlock + size);
    if (newBlock != curBlock->next) { //此块大小不是刚刚好的，才需要分块，不然可能产生神奇的闭环
        newBlock->available = true;
        newBlock->size = curBlock->size - size;
        newBlock->next = curBlock->next;
        curBlock->size = size;
        curBlock->next = newBlock;
    }
    rtnAddr = (void *)((unsigned int)curBlock + sizeof(MeM_BlockHead));
    return rtnAddr;
}
void MeM_Release(void *addr){
    addr = (void *)((unsigned int)addr - sizeof(MeM_BlockHead));
    ((MeM_BlockHead *)addr)->available = true;
}
void *MeM_Request(unsigned int size){
       //实际需要申请的空间大小，包含块头数据，申请的内存大小实际是块大小的整数倍,下面一行就是对齐整数倍用的...不需要太理解，反正最后结果是最接近但不小于实际值的块大小整数倍就是了
    size_t actSize = ((size + sizeof(MeM_BlockHead)) / MEMORY_MANAGE_BLOCK_SIZE + MEMORY_MANAGE_MEMORY_REQUEST_TAIL + (((size + sizeof(MeM_BlockHead)) % MEMORY_MANAGE_BLOCK_SIZE == 0) ? 0 : 1)) * MEMORY_MANAGE_BLOCK_SIZE;
    void *rtnAddr = NULL; //返回可用的地址
    rtnAddr = MeM_Request_Base(actSize);
    if (rtnAddr == NULL) {                   //没找到可用的块
        MeM_Tidy();                          //整理一次试试
        rtnAddr = MeM_Request_Base(actSize); //再申请一次，还是没有就摆烂了
    }
    return rtnAddr;
}

void MeM_Init(void){
    MeM_BlockHead initHead;
    initHead.available = true;
    initHead.next = NULL;
    initHead.size = MEMORY_MANAGE_POOL_SIZE;
    MeM_BlockHead *poolHead = (MeM_BlockHead *)&MeM_MemoryPool[0];
    *poolHead = initHead; //"开个好头"
}
