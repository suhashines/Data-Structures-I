#include<bits/stdc++.h>
#include "Stack.cpp"

using namespace std;

#define inf 1000000

template<class T>
class QueueC{
    int front,rear,capacity;
    T*arr;

    void expand() //O(n)
    {
        int newcapacity;
        if(capacity==0)
        {
            newcapacity = 1;
        }
        else
        {
            newcapacity = 2*capacity;
        }
        T*newarr = new T[newcapacity];

        for(int i=0;i<newcapacity;i++){
            newarr[i] = -inf ;
        }
        int j = 0; // put the elements in the new array
        int i; // lift the elements from the old array

        // r = 1 , f = 8
        // 8 , 9 , 0 , 1 // length = 4


        for(i=front;i<front+length();i++)
        {    j++;
        
            newarr[j] = arr[i%capacity];
           
        } //O(n)
        
        rear = j;
        front = 1;
        capacity = newcapacity;
        if(arr)
            delete arr;
        arr = newarr;
    }
    
public:
    QueueC(int c = 10)
    {
        capacity = c+1;
        arr = new T[capacity];
        front = 1;
        rear = 0;
        for(int i=0;i<capacity;i++)
            arr[i] = -inf;
    }
    void enqueue(T item)//O(1)
    {
        if(length()==capacity-1)
        {
            cout<<"Queue is full\n";
            expand();
            //return;
        }
        rear = (rear+1)%capacity; //r = 9 
        arr[rear] = item;
    }
    T dequeue()//O(1)
    {
        if(length()==0)
        {
            cout<<"Queue is empty\n";
            return -1;
        }
        T ret = arr[front];
        arr[front] = -inf;
        front = (front+1)%capacity;
        return ret;
    }
    T frontVal()//O(1)
    {
        return arr[front];
    }
    T rearVal()//O(1)
    {
        return arr[rear];
    }
    int length()//O(1)
    {
        return (rear-front+1+capacity)%capacity;
    }
    void printArray()//O(n)
    {
        cout<<"[ ";
        for(int i=0;i<capacity-1;i++)
        {
            if(arr[i]==-inf)
            {
                cout<<"_";
            }
            else
            {
                cout<<arr[i];
            }
            cout<<" | ";
        }
        if(arr[capacity-1]==-inf)
        {
            cout<<"_";
        }
        else
        {
            cout<<arr[capacity-1];
        }
        cout<<" ]"<<endl;
    }

    void reverseQueue(int k){

        Stack<T> st ;

        for(int i=front;i<front+k;i++){

            // k > length , k = 10 , length = 5

            if(arr[i%capacity] == -inf){
                break;
            }

            st.push(arr[i%capacity]) ;

            arr[i%capacity]=-inf ;
        }

        int size = st.size();

        for(int i=front;i<front+size;i++){

            arr[i%capacity] = st.pop();
        }

        
    }
};

int main()
{
    int cap;
    cout<<"Enter capacity of queue: ";
    cin>>cap;
    QueueC<int> Q(cap);
    string choice;
    while(1)
    {
        cin>>choice;
        transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        if(choice=="enq")
        {
            int p;
            cin>>p;
            Q.enqueue(p);
        }
        if(choice=="deq")
        {
            cout<<Q.dequeue()<<endl;
        }
        if(choice=="len")
        {
            cout<<Q.length()<<endl;
        }
        if(choice=="front")
        {
            cout<<Q.frontVal()<<endl;
        }
        if(choice=="rear")
        {
            cout<<Q.rearVal()<<endl;
        }

        if(choice == "rev"){
            int k ;
            cin>>k ;
            Q.reverseQueue(k);
        }
        cout<<endl;
        Q.printArray();
        cout<<endl;
    }
}
