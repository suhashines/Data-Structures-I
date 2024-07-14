#include<iostream>
#include "MyLinkedList.cpp"

using namespace std;

template <class T>
class Stack
{
private:
    LinkedList<T> list ;

public:
    // Push an element onto the stack

    void push(T item)  // O(1)
    {
        list.pushBack(item);
        //print();
    }

    // Pop an element from the stack
    T pop() // O(1)
    {
        if (list.size() == 0) {
            T dummy;
            return dummy; // Return a default value if the stack is empty
        }
        
        list.setToEnd(); // O(1)
        T poppedItem = list.erase(); // Erase the top element
        return poppedItem;
    }

    // Get the top element of the stack without removing it
    T top()  // O(1)
    {
        if (list.size() == 0) {
            T dummy;
            return dummy; // Return a default value if the stack is empty
        }
       // Move the current pointer to the top element
        list.setToEnd();
        return list.getValue();
    }

    // Check if the stack is empty
    bool isEmpty() // O(1)
    {
        return list.size() == 0;
    }

    // Get the size of the stack
    int size() // O(1)
    {
        return list.size() ;
    }

    void print(){  //O(n) 
        list.setToEnd(); //O(1)
        list.print(); // O(n)
    }
};