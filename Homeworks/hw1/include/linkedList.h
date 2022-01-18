#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>

/* @Berat Dalsuna
Student Name: Berat Dalsuna
Student ID : 150200002
Date: 31/09/2021 */

using namespace std;

class materialNode{
    public:
        char id;
        int weight = 0;
        materialNode* next = NULL;
        bool checkWeight(int); //added after by Berat
};

class wagonNode{
    public:
        int wagonId = 0;
        materialNode* material = NULL;
        wagonNode* next = NULL;
        bool contains_Material(wagonNode*,char); //added after by Berat

};

class Train{  

    wagonNode* head = NULL;
    
    public:
        void create();
        ~Train();
        void addMaterial(char,int);
        void deleteFromWagon(char, int); 
        void printWagon(); //Prints wagon info
        wagonNode* addWagon(); //added after by Berat
};

#endif