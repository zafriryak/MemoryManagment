/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Operators.h
 * Author: Zafrir
 *
 * Created on 7 ינואר 2017, 16:22
 */

#ifndef OPERATORS_H
#define OPERATORS_H
using namespace std;
#include<iostream>
#include"MemoryManager.h"

MemoryManager manager;

void intialManger(size_t size){
	MemoryManager m(size);
	manager = m;
}

void* operator new(size_t size){
    cout<<"in new"<<endl;
    return manager.allocate(size);
}

void* operator new[](size_t size){
    cout<<"in new[]"<<endl;
    return manager.allocate(size);
}

void operator delete(void* toDelete){
    cout<<"delete";
    manager.myfree(toDelete);
//    toDelete= reinterpret_cast<void*>(0x0);
    ::free(toDelete);
    toDelete=nullptr;
}

void operator delete[](void* toDelete){
    cout<<"delete[]";
    manager.myfree(toDelete);
//    toDelete= reinterpret_cast<void*>(0x0);
    ::free(toDelete);
    toDelete=nullptr;
}



#endif /* OPERATORS_H */

