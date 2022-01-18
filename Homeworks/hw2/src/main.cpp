#include <fstream>
#include <iostream>
#include "tree.h"

using namespace std;

/* @Author
Student Name: Berat Dalsuna
Student ID: 150200002
E-mail: dalsuna20@itu.edu.tr
Date: 24/12/2021
*/

/*
FRIEND-1: CITY1 CITY2 CITY3 CITY4 CITY9 CITY7 CITY8 CITY5 CITY6 CITY7 
FRIEND-2: CITY8 CITY9 CITY3 CITY2 CITY1 CITY4 CITY7 CITY7 
MEETING POINT: CITY2
TOTAL DURATION COST: 6
*/

void build_cities(Tree* tree, char* filename); // builds the tree-like structure from a cities array
void find_meeting_point(Node* r1, int& min_cost); // finds the meeting point with minimum cost

Tree* tree1 = new Tree; // tree for friend1
Tree* tree2 = new Tree; // tree for friend2
int meeting_point[2]; // stores the city and the cost

int main(int argc, char* argv[]){

    build_cities(tree1, argv[1]);
    build_cities(tree2, argv[2]);
    
    cout << "FRIEND-1: ";
    tree1->find_all_costs(tree1->get_root());
    tree1->print_tree(tree1->get_root());   
    cout << endl;  
    cout << "FRIEND-2: ";
    tree2->find_all_costs(tree2->get_root());
    tree2->print_tree(tree2->get_root());
    cout << endl;
    int min_cost = 0;
    find_meeting_point(tree1->get_root(),min_cost);
    cout << "MEETING POINT: " << "CITY" << meeting_point[0] << endl;
    cout << "TOTAL DURATION COST: " << meeting_point[1] << endl;
    delete tree1;
    delete tree2;
    return 0;
}


void build_cities(Tree* tree, char* filename){

    ifstream file_obj;
    int cities[100][3]; // fixed amount of cities, max = 100
    file_obj.open(filename,ifstream::in);
    char c;
    char nt[2];
    int arr[3];
    int arr_i = 0;
    int cities_i = 0;
    while(file_obj.get(c)){
        if(c<65 && c!=32 && c!=10){
            arr[arr_i] = c - '0';
            char nc;
            file_obj.get(nc);
            if(nc<65 && nc!=32 && nc!=10){ // if the number > 9, reads the file one more time.
                nt[0] = c;
                nt[1] = nc;
                arr[arr_i] = atoi(nt);
            }
            arr_i++;
        }
        if (arr_i==3){ // CITY8 CITY3 2 interpreted as 8 3 2 and stored in the cities array
            cities[cities_i][0] = arr[0];
            cities[cities_i][1] = arr[1];
            cities[cities_i][2] = arr[2];
            cities_i++;
            arr_i = 0;
        }
    }
    file_obj.close();
    
    for(int i=0;i<cities_i;i++){ // creates links according to the cities array.

        if (tree->get_root() == NULL){
            Node* root = new Node(cities[i][2], 0, cities[i][0]); //left data, right data, label
            tree->set_root(root);
            Node* left = new Node(0,0,cities[i][1]); 
            tree->get_root()->set_left(left);
        }

        else{

            Node* node = tree->find_node(tree->get_root(),cities[i][0]); 
            Node* same_node = tree->find_node(tree->get_root(),cities[i][1]); // if the node exists, creates a new pointer to that same node.                                                            // this prevents creating new node with the same label
            if (node != NULL){                                                // this prevents creating another node with the same label.
                if(same_node == NULL){
                    if(node->get_left() != NULL){
                        Node* right = new Node(0,0,cities[i][1]);
                        node->set_right(right);
                        node->set_right_data(cities[i][2]);
                    }
                    else{
                        Node* left = new Node(0,0,cities[i][1]);
                        node->set_left(left);
                        node->set_left_data(cities[i][2]);
                    }
                }
                else{
                    if(node->get_left() != NULL){
                        node->set_right(same_node);
                        node->set_right_data(cities[i][2]);
                    }
                    else{
                        node->set_left(same_node);
                        node->set_left_data(cities[i][2]);
                    }
                }
            }
        }

    }
    return;
}

void find_meeting_point(Node* r1, int& min_cost){ // r1 is from tree1, changes in every function call until becomes NULL
    if(r1){
        Node* r2 = tree2->find_node(tree2->get_root(),r1->get_label());
        if(r2){
            int cost = r1->get_cost() + r2->get_cost();
            if(min_cost == 0 || cost < min_cost){
                min_cost = cost;
                meeting_point[0] = r1->get_label();
                meeting_point[1] = min_cost;
            }
        }
    }
    if(r1->get_left())
        find_meeting_point(r1->get_left(), min_cost);
    if(r1->get_right())
        find_meeting_point(r1->get_right(), min_cost);

}