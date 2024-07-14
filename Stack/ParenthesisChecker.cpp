#include<iostream>
#include<bits/stdc++.h>
#include "Stack.cpp"

using namespace std;


string solve(const string &str){
    Stack<char> stack ;

    if(str.length() == 0) return "balanced" ;

    stack.push(str[0]);

    for(int i=1 ; i<str.length() ; i++){

        if(stack.top() == '(' && str[i]==')' || 
        stack.top() == '{' && str[i]=='}' || 
        stack.top() == '[' && str[i]==']' ){
            stack.pop();
        }else{
            stack.push(str[i]);
        }
    }

    if(stack.isEmpty()) return "balanced" ;

    return "unbalanced" ;
}

int main(){
    string str ;

    int T ;
    cin>>T ;

    for(int i=0;i<T;i++){

        cin>>str ;
        cout<<solve(str)<<endl;
    }
}