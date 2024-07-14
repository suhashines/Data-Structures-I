#include<iostream>
#include "Stack.cpp"
using namespace std;


int main()
{
    // Create a Stack of integers
    Stack<int> stack;

    // Push elements onto the stack
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // Print the top element of the stack
    cout << "Top element of the stack: " << stack.top() << endl; //30

    // Pop an element from the stack
    cout << "Popping element from the stack: " << stack.pop() << endl; //30

    // Print the top element of the stack again
    cout << "Top element of the stack after pop: " << stack.top() << endl; //20

    // Check if the stack is empty
    cout << "Is the stack empty? " << (stack.isEmpty() ? "Yes" : "No") << endl; //No

    // Pop all elements from the stack and print them
    cout << "Popping all elements from the stack: ";
    while (!stack.isEmpty())
    {
        cout << stack.pop() << " ";
    }
    cout << endl;

    // Check the size of the stack
    cout << "Size of the stack: " << stack.size() << endl; //0

    return 0;
}
