#include <iostream>
#include <stdlib.h>
#include "node.h"

using namespace std;

/* @Author
Student Name: Berat Dalsuna
Student ID: 150200002
E-mail: dalsuna20@itu.edu.tr
Date: 24/12/2021
*/

Node::Node(int left_data, int right_data, int label){
    this->left = NULL;
    this->right = NULL;
    this->left_data = left_data;
    this->right_data = right_data;
    this->label = label;
    cost = 0;
}

Node* Node::get_left(){
    return left;
}

void Node::set_left(Node* l){
    left = l;
}

Node* Node::get_right(){
    return right;
}

void Node::set_right(Node* r){
    right = r;
}

void Node::set_cost(int cost){
    this->cost = cost;
}

int Node::get_cost(){
    return cost;
}

int Node::get_right_data(){
    return right_data;
}

int Node::get_left_data(){
    return left_data;
}

void Node::set_right_data(int data){
    right_data = data;
}

void Node::set_left_data(int data){
    left_data = data;
}


int Node::get_label(){
    return label;
}
