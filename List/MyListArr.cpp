#include <bits/stdc++.h>

using namespace std;

template <class T>

class ArrayList
{

    T *arr;

    int capacity, len, curr;

    void rightShift()
    {

        for (int i = len - 1; i >= curr; i--)
        {
            arr[i + 1] = arr[i];
        }
    }

    void copy(T *arr1, T *arr2, int l)
    {

        for (int i = 0; i < l; i++)
        {
            arr1[i] = arr2[i];
        }
    }

    void expand()
    {
        // 2 times increment of capacity

        int newcapacity = 2 * capacity;

        T *newarr = new T[newcapacity];

        copy(newarr, arr, len);

        if (len > 0)
        {
            delete[] arr;
        }

        arr = newarr;
        capacity = newcapacity;
    }

    void shrink()
    {
        //try yourself 
        // make the capacity 1/2 whenever the len = capacity/2
    }

public:
    ArrayList(int c)
    {
        capacity = c;
        arr = new T[capacity];

        len = 0;
        curr = 0;
    }

    void pushBack(T item)//O(n)
    {

        if (len == capacity)
        {   //return ;
            expand(); //O(n)
        }

        arr[len] = item;
        len++;
    }

     void setToBegin()//O(1)
    {
        curr = 0;
    }

    void setToEnd()//O(1)
    {
        curr = len - 1;
    }

    void prev()//O(1)
    {

        if (curr == 0)
            return;

        curr--;
    }

    void next()//O(1)
    {

        if (curr == len - 1)
            return;

        curr++;
    }

    T getValue()//O(1)
    {

        if (len == 0)
        {
            T dummy;
            return dummy;
        }

        return arr[curr];
    }

    void push(T item)//O(n)
    {

        // < 1 2 | 3 4 >
        // push(5)
        // < 1 2 | 5 3 4 >


        if (len == capacity)
            return;

        rightShift();//O(n)
        // < 1 2 |   3 4 >

        arr[curr] = item;

        len++;
    }


    int currPos(){ //O(1)
        return curr ;
    }



    void setToPos(int pos)//O(1)
    {

        if (pos < 0 || pos >= capacity)
            return;

        curr = pos;
    }

    T erase()//O(n)
    {

        if (len == 0)
        {
            T dummy;
            return dummy;
        }

        T ret = arr[curr];

        //< | 1 > <  1 | 2 >

        if (len != 1 && curr == len - 1)
        {
            curr--;
        }
        else
        {
            for (int i = curr; i < len - 1; i++)
            {

                arr[i] = arr[i + 1];
            } //O(n)
        } // < 1 2 3 4 5> 

        len--;

        return ret;
    }

    
    int find(T item) //O(n)
    {

        int found = -1;

        for (int i = 0; i < len; i++)
        {
            if (arr[i] == item)
            {
                found = i;
                break;
            }
        } //O(n)

        return found;
    }

    void clear()//O(n)
    {

        if (arr)
            delete[] arr; //O(n)

        arr = new T[1];
        len = 0;
        capacity = 1;
        curr = 0;
    }

     void print()//O(n)
    {

        // < 1 2 | 3 4 >

        cout << "< ";

        for (int i = 0; i < curr; i++)
        {
            cout << arr[i] << " ";
        }

        cout << "| ";

        for (int i = curr; i < len; i++)
        {
            cout << arr[i] << " ";
        }

        cout << " >\n";
    }
};