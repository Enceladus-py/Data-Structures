#include <iostream>
#include <stdlib.h>
#include "tree.h"

using namespace std;

/* @Author
Student Name: Berat Dalsuna
Student ID: 150200002
E-mail: dalsuna20@itu.edu.tr
Date: 24/12/2021
*/

Tree::Tree(){
    root = NULL;
}

Tree::~Tree(){
    if(root != NULL)
        postorder_destruct(root);
    root = NULL;
}

void Tree::postorder_destruct(Node* r){
    if(r != NULL){
        postorder_destruct(r->get_left());
        postorder_destruct(r->get_right());
        delete r;
    }
}

Node* Tree::get_root(){
    return root;
}

void Tree::set_root(Node* r){
    root = r;
}

Node* Tree::find_node(Node* r,int l){ // finds the node in recursive way according to given label (l)

    if(r==NULL)
        return NULL;

    if(r->get_label() == l)
        return r;

    else{
        if(find_node(r->get_left(),l))
            return find_node(r->get_left(),l);
        else if(find_node(r->get_right(),l))
            return find_node(r->get_right(),l);
        else
            return NULL;
    }
   
}

void Tree::find_cost(Node* r, int l, int c){  

// finds the cost with increasing c in function call, if a smaller or greater cost found, remove_link function is called

    if((r->get_label() == l)){
        if(r->get_cost() == 0)
            r->set_cost(c);
        else{
            if(r->get_cost() >= c){
                remove_link(root,l,c,0);
                r->set_cost(c);
            }
            else
                remove_link(root,l,r->get_cost(),0);
        }
    }

    else{

        if(find_node(r->get_left(),l))
            find_cost(r->get_left(),l,c + r->get_left_data());
        
        if(find_node(r->get_right(),l))
            find_cost(r->get_right(),l,c + r->get_right_data());
    }

    return;
}

void Tree::remove_link(Node* r, int l,int cost, int sum){ 

// sum finds the cost for node and deletes properly the links in other words it helps pruning the tree
    if(r->get_left()==NULL && r->get_right() == NULL)
        return;

    else if(r->get_left() && r->get_left()->get_label() == l){
        if( (sum + r->get_left_data() > cost)){
            r->set_left(NULL);
            r->set_left_data(0);
        }
    }

    else if(r->get_right() && r->get_right()->get_label() == l){
        if( (sum + r->get_right_data() > cost)){
            r->set_right(NULL);
            r->set_right_data(0);
        }
    }

    else{
        if(find_node(r->get_left(),l))
            remove_link(r->get_left(),l,cost, sum + r->get_left_data());
        if(find_node(r->get_right(),l))
            remove_link(r->get_right(),l,cost, sum + r->get_right_data());
        else
            return;
    }
}

void Tree::find_all_costs(Node* r){ // finds all costs for every node in the pruned tree
    if(r!=NULL){
        find_cost(root,r->get_label(), 0);
        find_all_costs(r->get_left());
        find_all_costs(r->get_right());
    }
}


void Tree::print_tree(Node* r){
    if(r!=NULL){
        cout << "CITY" << r->get_label() << " ";
        print_tree(r->get_left());
        print_tree(r->get_right());
    }    
}
