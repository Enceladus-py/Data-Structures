#include <iostream>
#include <stdio.h>
#include <string.h>

/* @Berat Dalsuna
Student Name: Berat Dalsuna
Student ID : 150200002
Date: 31/09/2021 */

#include "linkedList.h"

using namespace std;

bool materialNode::checkWeight(int w){ // checks if a material weight + given weight < 2000 
    if ((w + weight) > 2000){
        return false;
    }
    else{
        return true;
    }
}

bool wagonNode::contains_Material(wagonNode* wptr,char material){ // checks if a wagon contains the given material by its letter
    materialNode* mptr = wptr->material;
    while(mptr!=NULL){
        if(mptr->id == material){
            return true;
        }
        else{
            mptr = mptr->next;
        }
    } 
    return false;
}

void Train::create(){
    head = NULL;
}; 


Train::~Train() { // deletes wagon for no memory leak
    wagonNode* wptr = head;
    wagonNode* current_wptr = NULL;
    materialNode* mptr = NULL;
    materialNode* current_mptr = NULL;

    while(wptr){ // deletes current wagon and passes to next one
        mptr = wptr->material;
        while(mptr){ // deletes current material and passes to next one
            current_mptr = mptr->next; 
            delete mptr;
            mptr = current_mptr;
        }
        current_wptr = wptr->next;
        delete wptr;
        wptr = current_wptr;
    }
}


wagonNode* Train::addWagon(){ // adds wagon to current train and returns last wagons pointer
    int id = 1;
    wagonNode* wptr = head;
    if(wptr==NULL){
        wptr = new wagonNode;
        wptr->wagonId = id;
        head = wptr;
        return wptr;
    }

    while(wptr!=NULL){
        if(wptr->next!=NULL){
            wptr = wptr->next;
        }
        else{
            wptr->next = new wagonNode;
            wptr = wptr->next;
            id++;
            break;
        }
        id++;
    }
    wptr->wagonId = id;    
    return wptr;
}

void Train::addMaterial(char material, int weight){ // adds the given material to the train according to given rules
        
    wagonNode* wptr = head; //starts from first wagon
    materialNode* mptr = NULL;

    while(wptr!=NULL){
        mptr = wptr->material; // current wagons first material

        while(mptr->id != material){ 

            if(mptr->next){ // passes to next material
                mptr = mptr->next;
            }
            else{ // if there is not a next material, creates one and sets its material to given material
                mptr->next = new materialNode;
                mptr->next->id = material;
                mptr = mptr->next;
            }
        }

        if(mptr->checkWeight(weight)){ // if given weight can be added to current material, adds it
            mptr->weight += weight;
            materialNode* curr = wptr->material;
            materialNode* prev = NULL;
            while(curr->next!=NULL){ // checks whether its in order or not
                if(curr->next->id < curr->id){ 
                // CHANGING DATAS INSTEAD OF LINKS !!!
                    
                    char tmp = curr->id;
                    int w = curr->weight;
                    curr->id = curr->next->id;
                    curr->weight = curr->next->weight;
                    curr->next->weight = w;
                    curr->next->id =tmp;
                    curr = wptr->material; 

                    /*
                    if (prev){
                        prev->next = curr->next;
                        prev->next->next = curr;
                    }
                    else{
                        materialNode* tmp = curr;
                        materialNode* tmp1 = curr->next;
                        curr = curr->next;
                        curr->next = tmp;
                    }      
                    */     
                }
                else{
                    prev = curr;
                    curr = curr->next;
                }
            }
            break; // exits the while loop, because weight is added
        }
        else{ // if current materials weight + given weight passes 2000
            weight = (weight + mptr->weight) - 2000;
            mptr->weight = 2000;
            materialNode* curr = wptr->material;
            while(curr->next!=NULL){
                if(curr->next->id < curr->id){ 
                // CHANGING DATAS INSTEAD OF LINKS !!!
                    char tmp = curr->id;
                    int w = curr->weight;
                    curr->id = curr->next->id;
                    curr->weight = curr->next->weight;
                    curr->next->weight = w;
                    curr->next->id =tmp;
                    curr = wptr->material; 
                
                }
                else{
                    curr = curr->next;
                }
            }
        }
        if(wptr->next){ //passes to next wagon
            wptr = wptr->next;
        }
        else{ // if there is not, adds a new wagon and set new value to lastly added wagon
            wptr = addWagon();
            wptr->material = new materialNode;
            wptr->material->id = material;
        }
    }
    
    if(head==NULL){ //creating first wagon
        wptr = addWagon();
        mptr = new materialNode;
        mptr->id = material;
        if(mptr->checkWeight(weight)){
            mptr->weight += weight;
            wptr->material = mptr;
        }
        else{
            mptr->weight = 2000;
            wptr->material = mptr;
            wptr = addWagon();
            wptr->material = new materialNode;
            wptr->material->id = material;
            addMaterial(material,weight-2000);
        }
    }
    
}; 


void Train::deleteFromWagon(char material, int weight){


    bool finish = false;
    wagonNode* wptr = head;
    wagonNode* prew = NULL; // previous wagon
    materialNode* mptr = NULL;
    materialNode* prev = NULL; // previous material
    int last_id = 1;
    while(wptr->next!=NULL){ // finds last wagons id
        last_id++;
        prew = wptr;
        wptr = wptr->next;
    }

    while(wptr!=NULL && !finish){ // while current wagon exists
        if(wptr->wagonId == last_id && wptr->contains_Material(wptr,material)){ // if it is the last wagon containing the material
            mptr = wptr->material; // mptr = first material in the wagon
            while(mptr!=NULL){ // trying to find material
                if(mptr->id == material){ // found the material
                    if(mptr->weight > weight){
                        mptr->weight -= weight;
                        wptr = wptr->next;
                    }
                    else{
                        if(mptr->weight == weight){ // function will stop
                            finish = true;
                        }
                        else{ // last available wagon will be last-1
                            weight -= mptr->weight;
                            last_id--;
                        }
                        if(prev==NULL){ // if there is not a previous material
                            if(mptr->next==NULL){ // if wagon contains only one material, delete wagon
                                wptr->material = NULL;
                                delete wptr->material;
                                if(prew && wptr->next){ 
                                    prew->next = wptr->next; // prew - wptr - wptr->next now equals to prew - wptr->next
                                    wptr = prew;
                                }
                                else if(prew){
                                    if(prew->wagonId==1){
                                        wptr = head;
                                        head->next = NULL;
                                        prew = NULL;
                                    }
                                    else{
                                        for (wagonNode* tmp=head;tmp!=NULL;tmp=tmp->next){ // finds previous of the previous one
                                            if(tmp->wagonId==((prew->wagonId)-1)){
                                                prew->next = NULL;
                                                wagonNode* ptr1 = prew;
                                                prew = tmp;
                                                wptr = ptr1;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else{                            
                                    wptr = NULL;
                                    head = NULL;
                                }
                            }
                            else{
                                wptr->material = mptr->next; // deletes first material and sets second material as the first material
                                delete mptr;

                            }
                            
                        }
                        else{
                            if(mptr->next){
                                prev->next = mptr->next;
                                delete mptr;
                            }
                            else{
                                prev->next = NULL;
                                wptr = wptr->next;
                            }
                        }
                    }
                    break; // exits the material loop
                }
                else{ // if material cannot founded, continue, prev is the previous material
                    prev = mptr;
                    mptr = mptr->next;
                }
            }
        }      
        else if(wptr->wagonId != last_id){ //finds last wagon
            prew = wptr;   
            wptr = wptr->next;    
        }
        else if(wptr->wagonId == last_id && !(wptr->contains_Material(wptr,material))){
            wptr = head;
            prew = NULL;
            last_id--;
        }
    }

};  


void Train::printWagon(){
    wagonNode* tempWagon = head;

    if(tempWagon == NULL){
            cout<<"Train is empty!!!"<<endl;
            return;
    }

    while(tempWagon != NULL){
        materialNode* tempMat = tempWagon->material;
        cout<<tempWagon->wagonId<<". Wagon:"<<endl; 
        while (tempMat != NULL){
            cout<<tempMat->id<<": "<<tempMat->weight<<"KG, "; 
            tempMat = tempMat->next;  
        }
        cout<<endl; 
        tempWagon = tempWagon->next;
    }
    cout<<endl;
}; 