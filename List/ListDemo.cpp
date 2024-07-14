#include<iostream>
#include "MyListArr.cpp"
#include "MyLinkedList.cpp"

using namespace std;


int main(){

  ArrayList<int> l(1) ; //initial capacity = 1 

  int len = 8 ;   // but we are inserting 8 elements

  for(int i=0;i<len;i++){
    l.pushBack(i) ;
  }

    l.print();

    //output : < | 0 1 2 3 4 5 6 7  >

    //hence the task is to increase the capacity two times 
    //whenever the number of elements exceeds the capacity
}