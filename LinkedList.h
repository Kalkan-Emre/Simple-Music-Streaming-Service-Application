#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
    /* TODO */
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    /* TODO */
    head = NULL;
    *this = obj;
}

template<class T>
LinkedList<T>::~LinkedList() {
    /* TODO */
    removeAllNodes();
    
    delete head;
}

template<class T>
int LinkedList<T>::getSize() const {
    /* TODO */
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    /* TODO */
    return (head==NULL);
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    /* TODO */
    Node<T> *current = head;
    if(!isEmpty())
    {
        if(head == node)  // Special check for one element list.
            return true;

        while(current->next != head)  // Traverse all list to check whether the node is in the list.
        {
            if(current==node)
                return true;

            current = current->next;
        }
        if(current==node)   // Check last node.
            return true;
    }
    return false; // Return false if list is empty or node is not in list.
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    /* TODO */
    if(isEmpty())
        return NULL;

    else{
        return head;
    }
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    /* TODO */
    if(isEmpty())
        return NULL;

    else{
        return head->prev;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    /* TODO */
    Node<T> *current = head;

    if(isEmpty())
        return NULL;

    else{
        if(head->data == data)      // Special check for one element list.
            return head;

        while(current->next != head)    // Traverse all list to check whether the node is in the list.
        {
            if(current->data == data)
            {
                return current;
            }
            current = current->next;
        }

        if(current->data == data)   // Check last node.
            return current;


        return NULL;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    /* TODO */
    Node<T> *current = head;

    if((index>=size)||(index<0))  // Check whether the index is out of the bounds.
        return NULL;

    for(int i=0; i!=index; i++)
    {
        current = current->next;
    }

    return current;
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    /* TODO */
    if(isEmpty())
    {
        Node<T> * newNode = new Node<T>(data);

        head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    else{
        Node<T> * newNode = new Node<T>(data, head->prev, head);
        Node<T> * oldHead = head;
        Node<T> * last = head->prev;

        head = newNode;
        oldHead->prev = newNode;
        last->next = newNode;
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    /* TODO */
    if(isEmpty())
    {
        Node<T> * newNode = new Node<T>(data);

        head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    else{
        Node<T> * newNode = new Node<T>(data, head->prev, head);
        Node<T> * currentHead = head;
        Node<T> * last = head->prev;

        last->next = newNode;
        currentHead->prev = newNode;

    }
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    /* TODO */
    if(contains(node))  //Check if the node is in the list.
    {
        Node<T> *current = head;
        while(current!= node)
        {
            current = current->next;
        }
        Node<T> * newNode = new Node<T>(data, current, current->next);

        current->next->prev = newNode;
        current->next = newNode;

        size++;
    }
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    /* TODO */
    int i = -1;
    int total_size = size;

    if(k<2||k>size+1)
    {
        return;
    }
    while(i<total_size)
    {
        i+=(k-1);
        insertAfterNode(data,getNodeAtIndex(i));
        i++;
        total_size++;
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    /* TODO */
    if(contains(node))  //Check if the node is in the list.
    {
        Node<T> *current = head;
        
        if(node == head)   //If the node is the head then make head the second element of the list.
        {
            head = head->next;
        }
        
        
        if((head->next == head)&&(head->prev == head)&&(node==head))  
        {
            Node<T>* tmp = head;
            head = NULL;
            current = NULL;
            node = NULL;
            size = 0;
            delete tmp;
            return;
        }
        
        while(current!= node)
        {
            current = current->next;
        }
        
        current->next->prev = current->prev;
        current->prev->next = current->next;
        
        current = NULL;
        delete node;

        size--;
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    /* TODO */
    while(getNode(data))
    {
        removeNode(getNode(data));
    }
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    /* TODO */
    while(!isEmpty())
    {
        removeNode(head);
    }
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    /* TODO */
    int i = 0;
    int total_size = size;

    if(k<2||k>size)
    {
        return;
    }
    while(i<total_size)
    {
        i+=(k-1);
        removeNode(getNodeAtIndex(i));
        total_size--;
    }
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    /* TODO */
    
    if(contains(node2)&&contains(node1)&&(node1!=node2))
    {
        Node<T>* node1_n;
        Node<T>* node1_p;
        
        if(node1==head)
            head=node2;
        else if(node2==head)
            head=node1;
        
        if((node1->next==node2)&&(node2->next==node1))
        {
            return;
        }
        else if(node2->next==node1)
        {
            node2->prev->next = node1;
            node1->next->prev = node2;
            node2->next = node1->next;
            node1->prev = node2->prev;
            node1->next = node2;
            node2->prev = node1;
        }
        else if((node1->next==node2))
        {
            node1->prev->next = node2;
            node2->next->prev = node1;
            node1->next = node2->next;
            node2->prev = node1->prev;
            node2->next = node1;
            node1->prev = node2;
        }
        else
        {
            node1->prev->next = node2;
            node1->next->prev = node2;
            
            node2->prev->next = node1;
            node2->next->prev = node1;
            
            node1_n = node1->next;
            node1->next = node2->next;
            
            node1_p = node1->prev;
            node1->prev = node2->prev;
            
            node2->next = node1_n;
        
            node2->prev = node1_p;
        }
    }
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
    /* TODO */
    for(int i=0; i<size ; i++)
    {
        swap(getNodeAtIndex(i),getNodeAtIndex((i*i+seed)%size));
    }
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    /* TODO */
    if(this != &rhs)
    {
        removeAllNodes();
        
        if(rhs.head)
        {
            Node<T> * r = rhs.head;
            insertAtTheFront(r->data);
        
            r = r->next;
        
            while(r != rhs.head)
            {
                insertAtTheEnd(r->data);
                r = r->next;
            }
        }
    }
    return *this;
}

#endif //LINKEDLIST_H
