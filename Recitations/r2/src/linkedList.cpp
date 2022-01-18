#include <iostream>
#include <stdio.h>

#include "linkedList.h"

using namespace std;

/* @dalsuna20
Student Name: Berat Dalsuna
Student ID : 150200002
Date: 26/10/2021*/

void LinkedList::reorderList(){
    //FILL THIS FUNCTION ACCORDINGLY    
    for(Node* ptr=head;ptr->next!=NULL;ptr=ptr->next){  //iterating over linked list to the last element
        if((ptr->letter)>(ptr->next->letter)){ 
            swap(ptr->letter,ptr->next->letter); //swapping two pointers
            reorderList();
        }
    }

};

void LinkedList::removeDublicates(){
    //FILL THIS FUNCTION ACCORDINGLY
    Node* ptr = head;
    while(ptr->next != NULL){
        for(Node* ptr2=ptr->next;ptr2->next!=NULL;ptr2=ptr2->next){
            if(ptr->letter == ptr2->letter){
                ptr->next = ptr2->next; // if two letters are same, omit the latter one.
            }
        }
        ptr = ptr->next;
    }

};

void LinkedList::reverseList(){
    //FILL THIS FUNCTION ACCORDINGLY
    Node* ptr = head;
    Node* tmp = NULL;
    Node* prev = NULL;

    while(ptr!=NULL){  //reversing two sequential component.
        tmp = ptr->next;
        ptr->next = prev;
        prev = ptr;
        ptr = tmp; 
    }
    head = prev;
};

void LinkedList::printList(){
    Node* temp = head;
    while(temp != NULL){
        cout<<temp->letter<<" ";
        temp = temp->next;
    }
    cout<<endl;
};