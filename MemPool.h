/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MemPool.h
 * Author: Zafrir
 *
 * Created on 1 ינואר 2017, 16:13
 */
using namespace std;
#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <cstdio>
#include <map>
#include <list>

class MemPool {
public:
    static MemPool& getInstane(size_t heapSize) {
        static MemPool instance(heapSize);
        return instance;
    }

    //the class are singleton - the copy ctr and operator=, not need to be used
    MemPool(MemPool const&) = delete;
    void operator=(MemPool const&) = delete;

    void* getNextFreeLocationPtr(size_t size){
        if(this->availableSize < size){
            return nullptr;
        }
        availableSize = availableSize - size;
        this->currentFreeLocation_ptr = this->currentFreeLocation_ptr +size;//this->nextFreeLocation_ptr;
        return (void*)(&myHeap[this->currentFreeLocation_ptr-size]);
    }
        

private:
    MemPool() {}
    int currentFreeLocation_ptr;
    size_t availableSize ;
    char* myHeap;
    MemPool(size_t heapSize) {
        myHeap = (char*)malloc(heapSize);
        availableSize = heapSize;
        this->currentFreeLocation_ptr = 0;
    }

};

#endif /* MEMPOOL_H */

