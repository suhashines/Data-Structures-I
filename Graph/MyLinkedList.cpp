#include <bits/stdc++.h>
#include "Node.cpp"

using namespace std;

template <class T>
class LinkedList
{

    Node<T> *head, *tail, *curr;
    int len;


    void initHeadTail(T item){

        Node<T>* node = new Node<T>(item) ;

        head = tail = curr = node ;
    }

public:
    LinkedList()
    {
        head = tail = curr = NULL;
        len = 0;
    }

    // pushback
    // < 1 2 3>
    // <1 2 3 4>

    void pushBack(T item){ //O(1)

        if(len == 0){
            initHeadTail(item) ;
        }else{

            Node<T>* node = new Node<T>(item,tail,NULL) ;
            tail->right = node ;
            tail = node ;
        }

        len ++ ;
    }

    void setToBegin(){//O(1)
        curr = head ;
    }

    void setToEnd(){//O(1)
        curr = tail ;
    }

    void prev(){//O(1)

        if(len>0 && curr!=head){
            curr = curr->left ;
        }
    }
    
    void next(){//O(1)

        if(len>0){
            curr = curr->right ;
        }
    }

    T getValue(){//O(1)

        if(len==0){
            T dummy ;
            return dummy ;
        }

        return curr->value ;
    }

    void push(T item){//O(1)

        if(len==0){
            initHeadTail(item);
        }else if(curr==head){

            Node<T>* node = new Node<T>(item,NULL,curr);
            head->left = node ;

            head = node ;
            curr = node ;
        }else{

            Node<T>* node = new Node<T>(item,curr->left,curr);
            curr->left->right = node ;
            curr->left = node ;
            curr = node ;
        }

        len ++ ;
    }

    int currPos(){ //O(n)

        Node<T>* node = head ;

        int i=0 ;

        while(node!=curr){
            node = node->right ;
            i++ ;
        } // O(n)

        return i ;
    }

    void setToPos(int pos){//O(n)

        if(pos>=0 && pos<len){
            
            Node<T>* node = head ;

            for(int i=0;i<pos;i++){
                node = node->right ;
            }//O(n)

            curr = node ;

        }else{
            cout<<"invalid position"<<endl;
        }
    }


    int length(){
        return len ;
    }


    T erase(){//O(1)

        if(len==0){
            T dummy ;
            return dummy ;
        }

        T ret = curr->value ;

        if(len==1){
            delete head ;
            head = tail = curr = NULL ;
        }else if(curr==head){
            Node<T>* node = head ;
            head->right->left = NULL ;
            head = head->right ;
            curr = head ;
            delete node ;
        }else if(curr==tail){
            Node<T>* node = tail ;
            tail->left->right = NULL ;
            tail = tail->left ;
            curr = tail;
            delete node ;
        }else{

            Node<T>*node = curr ;
            curr->left->right = curr->right ;
            curr->right->left = curr->left ;
            curr = curr->right ;
            delete node ;
        }

        len -- ;
        return ret;
    }

    void clear(){//O(n)

        setToEnd();
        while(len>0){
            erase();
        }//O(n)
        head = tail = curr = NULL ;
    }

    void print(){//O(n)


        if(len==0){
            cout<<"<>\n";
            return ;
        }

        cout<<"<";

        Node<T>* node = head ;

        while(node!=curr){
            cout<<node->value<<" " ;
            node = node->right ;
        }

        cout<<"| " ;

        while(node!=tail){
            cout<<node->value<<" " ;
            node = node->right ;
        }

        cout<<tail->value<<">\n" ;
    }





    void reverse(){

        Node<T>* curr1 = head ;
        Node<T>* curr2 = head->right;

        while(1){

            if(curr2 == NULL){
                tail = head ;
                head = curr1 ;
                head->left = NULL ;
                break;
            }

            curr1->left = curr2 ;
            Node<T>* temp = curr2->right ;
            curr2->right = curr1 ;
            curr1 = curr2 ;
            curr2 = temp ;

        }
    }

    void rotate(int k){

        // create circular reference

        int currPos = len - k ;

        setToPos(currPos);

        head->left = tail ;
        tail ->right = head ;

        // remove the link

        tail = curr->left ;
        curr->left->right = NULL ;
        curr->left = NULL ;
        head = curr ;


    }

    void bubbleSort(T* a,int l){

        for(int i=0;i<l;i++){

        for(int j=i+1;j<l;j++){

            if(a[i]>a[j]){
                T temp = a[i];
                a[i] = a[j];
                a[j] = temp ;
            }
        }
       }

    }

    void sort(){

       T* a = new T[len];

        Node<T>* m = head ;

       for(int i=0;i<len;i++){
            a[i] = m->value ;
            m = m->right ;
       }

       bubbleSort(a,len);

       m = head ;

       for(int i=0;i<len;i++){
         m->value = a[i];
         m = m->right ;
       }
    }

    
};
