/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MemoryManager.cpp
 * Author: Zafrir
 * 
 * Created on 1 ינואר 2017, 16:18
 */
#include <iostream>
#include <vector>
#include <math.h>
#include "MemoryManager.h"
#include "MyAllocator.h"

MemoryManager::MemoryManager(size_t heapSize) {
    pool = &MemPool::getInstane(heapSize);
}

MemoryManager::~MemoryManager() { 
}


size_t MemoryManager::findBlock(void* ptr) {
    for(int i = 0 ; blocksList.size() ; i++){
        if(blocksList.at(i).getStartPtr()== ptr){
            return i;
        }
    }
    return -1;
}


void* MemoryManager::allocate(size_t size) {
    size_t fixSize = pow(2,ceil(log2(size)));
    if(freeList.empty()){
        void* ptr = this->pool->getNextFreeLocationPtr(fixSize);
        freeblock f(fixSize,ptr);
        f.setAvailable(false);
        if(blocksList.empty()){
            cout<<"blockList is empty"<<endl;
            blocksList.push_back(f);
        }
        else{
              blocksList.push_back(f);
              blocksList.at(blocksList.size()-2).setNext(&f);
        }
        return f.getStartPtr();
    }
    else{
        for(int i = 0 ; i < freeList.size() ; i++){
            if(freeList.at(i).getSize() == fixSize){
                return freeList.at(i).getStartPtr();
            }
            if(freeList.at(i).getSize() > fixSize){
                ////here we need to disassemble chunks ///////
                size_t oldSize = freeList.at(i).getSize();
                size_t newSize = freeList.at(i).getSize() - fixSize;//TODO fix size for newSize
                void* newPtr = (char*)freeList.at(i).getStartPtr() + fixSize; 
                freeblock f1(newSize , newPtr);
                f1.setAvailable(true);
                f1.setNext(freeList.at(i).getNext());
                /////// update blockList//////////
                size_t index = findBlock(freeList.at(i).getStartPtr());
                blocksList.at(index).setSize(fixSize);
                blocksList.at(index).setAvailable(false);
                blocksList.at(index).setNext(&f1);
                blocksList.insert(blocksList.begin()+index , f1);
                ///////// update freeList///////////
                freeList.at(i).setSize(fixSize);
                freeList.at(i).setNext(&f1);
                freeList.push_back(f1);
                freeblock tmp = freeList.at(i);
                freeList.erase(freeList.begin()+i);
                return tmp.getStartPtr();
            }
        }
        void* ptr = this->pool->getNextFreeLocationPtr(fixSize);//allocate object on the heap
        if(ptr!=nullptr){
            freeblock f(fixSize,ptr);
            f.setAvailable(false);
            freeblock f1 = blocksList.at(blocksList.size()-1);
            blocksList.pop_back();
            f.setNext(&f1);
            blocksList.push_back(f1);
            blocksList.push_back(f);            
        }
        else{ /////// if we need, here we need to merge chunks////////
            for(int i = 0 ; i < freeList.size() ; i++){
                freeblock temp=freeList.at(i);
                size_t sumSize=fixSize;
                int countIteration=0;
                while(temp.getNext()->getAvailable()&& sumSize>0){
                    temp=*temp.getNext();
                    sumSize-=temp.getSize();
                    countIteration++;
                }
                if(sumSize<=0){
                    int index=findBlock(freeList.at(i).getStartPtr());
                    blocksList[index].setSize(fixSize);
                    blocksList[index].setAvailable(false);
                    blocksList[index].setNext(blocksList.at(index+countIteration-1).getNext());
                    for(int j=1;j<countIteration;j++){
                        blocksList.erase(blocksList.begin()+index+j);
                    }
                    //blocksList.erase(blocksList.begin()+index+countIteration);
                    for(int j=0;j<countIteration;j++){
                        freeList.erase(freeList.begin()+i+j);
                    }
                    return blocksList[index].getStartPtr();
                }
            }
        }
    }
}

MemoryManager::MemoryManager() {}

void MemoryManager::myfree(void* pointer) {  
    size_t index = findBlock(pointer);
    blocksList[index].setAvailable(true);
    freeList.push_back(blocksList.at(index));
}