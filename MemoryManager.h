/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MemoryManager.h
 * Author: Zafrir
 *
 * Created on 1 ינואר 2017, 16:18
 */

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
using namespace std;
#include "MemPool.h"
#include "MyAllocator.h"
#include "Allocator2.h"

class MemPool;



class freeblock{
public:
    freeblock(size_t size , void* ptr){this->size = size , startPtr = ptr;this->next = nullptr;available=false;};
    void setAvailable(bool state){this->available = state;};
    bool getAvailable(){return this->available;};
    size_t getSize(){return this->size;};
    freeblock* getNext(){return this->next;};
    void setNext(freeblock* block){this->next = block;};
    void* getStartPtr(){return this->startPtr;};
    void setSize(size_t size){this->size = size;};
private:
    void* startPtr;
    freeblock* next;
    size_t size;
    bool available;
};

class MemoryManager {
public:
    MemoryManager();
    size_t getHeapSize() const;
    MemoryManager(size_t heapSize);
    virtual ~MemoryManager();
    void* allocate(size_t);
    size_t findBlock(void* ptr);
    void myfree(void*);

private:
    //map<size_t,list<freeblock,JVC::allocator<freeblock>>,less<size_t>,JVC::allocator<pair<size_t,list<freeblock,JVC::allocator<freeblock>>>>> freeLists;
    //std::map<void*,size_t,less<void*> ,JVC::allocator<pair<void* , size_t>>> associativeArray;
    vector<freeblock,JVC::allocator<freeblock>> blocksList;
    vector<freeblock,JVC::allocator<freeblock>> freeList;
//    map<void* , freeblock , less<void*> , JVC::allocator<pair<void*,freeblock>>> findBlocks;
//    map<size_t , size_t , less<size_t> , JVC::allocator<pair<size_t,size_t>>> valgring;
    MemPool *pool ;
    size_t heapSize;
    size_t numOfBlocks;
    size_t numOfBytes;

};


#endif /* MEMORYMANAGER_H */

