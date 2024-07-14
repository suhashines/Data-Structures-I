#include<iostream>
#include<bits/stdc++.h>
#include "Stack.cpp"

using namespace std;


void insert_at_bottom(Stack<int>&st,int x){

    if(st.isEmpty()){
        st.push(x);
        return;
    }

    int elem = st.pop();

    insert_at_bottom(st,x);

    st.push(elem);
}


void reverse(Stack<int>& st){

    if(st.size() == 1){
        return;
    }

    int x = st.pop();

    reverse(st);

    insert_at_bottom(st,x);
}


int main(){
    Stack<int> st ;

    for(int i=0;i<4;i++){
        st.push(i+1);
    }

    st.print();

    reverse(st);

    st.print();
}