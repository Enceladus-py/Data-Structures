#include <iostream> 
#include <fstream> 
#include <stdlib.h>

#include "linkedList.h"

using namespace std;

/* @dalsuna20
Student Name: Berat Dalsuna
Student ID : 150200002
Date: 26/10/2021*/

int main(int argc, char* argv[]) {
	system("clear");// make this line as comment if you are compiling on Linux or Mac
	//system("cls"); // make this line as comment if you are compiling on Windows
    LinkedList newLinkedList;

    FILE* inputFile = fopen(argv[1], "r");
    char c = getc(inputFile);
    Node* n1 = new Node;
    n1->letter = c;
    n1->next = NULL;
    newLinkedList.head = n1;
    getc(inputFile);

    while (!feof(inputFile)) {  //reading chars from file and assigning it to linked list.
        c = getc(inputFile);    
        Node* ptr = newLinkedList.head; 
        Node* n2 = new Node;          
        while(ptr->next!=NULL){
            ptr = ptr->next;
        }        
        n2->letter = c;
        n2->next = NULL;
        ptr->next = n2;
        getc(inputFile);
    }
    fclose(inputFile);

    cout<<"Readed letters in linked list: ";
    newLinkedList.printList();

    newLinkedList.reorderList();
    cout<<"After reordering: ";
    newLinkedList.printList();

    newLinkedList.removeDublicates();
    cout<<"After removing dublicates: ";
    newLinkedList.printList();
    
    newLinkedList.reverseList();
    cout<<"Reversed list: ";
    newLinkedList.printList();


    return EXIT_SUCCESS;
}