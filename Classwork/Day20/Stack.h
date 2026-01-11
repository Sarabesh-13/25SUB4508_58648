#pragma once

#include<iostream>
#include<cstdlib>

template <typename T>
class Stack
{
    private:
        T *arr;
        int top;
        int size;
    
    public:
       Stack(int s);
       void push(T val);
       void pop();

       T peek();

       bool isFull();

       bool isEmpty();
       
       void display();

       ~Stack();  
};

#include "Stack.tpp"