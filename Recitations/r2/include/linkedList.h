#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>

/* @dalsuna20
Student Name: Berat Dalsuna
Student ID : 150200002
Date: 26/10/2021*/

using namespace std;

class Node{
    public:
        char letter;
        Node* next;
};


class LinkedList{


    public:
        Node* head; //changed that it was private!
       
        void reorderList();
        void removeDublicates();
        void reverseList();
        void printList();
};

#endif
