/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Zafrir
 *
 * Created on 1 ינואר 2017, 16:13
 */
using namespace std;

#include <cstdlib>
#include <iostream>
#include<vector>
#include "MemPool.h"
#include"Operators.h"
#include "MemoryManager.h"
int main(int argc,char** argv) {
    char* s = new char[2];
//    char* s1 = new char[2];
 
//    char* s2 = new char[4];
    s[0] = 'c';
    s[1] = 'a';
    cout<<s[0]<<" , "<<s[1]<<endl;
    delete[] s;
    //cout<<s[0]<<" , "<<s[1]<<endl;
    char* n = new char[2];
    n[0] = 'b';
    n[1] = 'd';
    cout<<s[0]<<" , "<<s[1]<<endl;

}