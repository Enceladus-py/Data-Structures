#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include "huffman.h"

using namespace std;

/* @Author
Student Name: Berat Dalsuna
Student ID : 150200002
Date: 14/12/2021 */

int Huffman::findindex(Token *arr,string elem){
	// YOU HAVE TO COMPLETE THIS PART
	// THIS FUNCTION RETURNS THE INDEX OF STRING ON TOKEN ARRAY, IF STRING IS NOT IN TOKEN ARRAY, RETURNS -1
    int i;
    for(i = 0;i<ARRAY_SIZE;i++){
        if(arr[i].symbol == elem) 
            return i;
    }

    return -1;
}

void Huffman::find_frequencies()
{
    int index = -1;
    ifstream file_obj; //object to read file
    file_obj.open("../input.txt",ifstream::in);
    char symbol = 0;
    if (!file_obj.is_open()) {
        file_obj.open("input.txt",ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }
    while (file_obj.get(symbol)) 
    {
        string s;
        s.push_back(symbol);
        // YOU HAVE TO COMPLETE THIS PART
        if(priority_queue.contains(s)){ // if queue contains the string s, finds the token and increases the count
            Node* t = priority_queue.head;
            while(true){
                if (t->token.symbol == s){
                    t->token.count++;
                    int i = findindex(token_array,s);
                    token_array[i].count++;
                    break;
                }
                t = t->next;
            }
        }
        else{ // if queue doesn't contain the string s, creates new node and pushes it to queue and token_array 
            Node* n = new Node;
            n->token.symbol = s;
            n->token.count = 1; 
            priority_queue.push(n);
            token_array[++index] = n->token;
        }
    }
    file_obj.close();
}

PriorityQueue::PriorityQueue()
{
    head = NULL;
    token_count = 0;
}

bool PriorityQueue::contains(string s){

    Node* t = head;
    while(t != NULL){
        if(t->token.symbol == s) // if symbol is found, returns true
            return true;
        else t = t->next;
    }
    return false;
}

void PriorityQueue::push(Node *newnode) //push node to queue
{
	// YOU HAVE TO COMPLETE THIS PART
    Node* t = head;
    Node* prev = NULL;

    if(head==NULL){ // if head doesnt exist, head is equal to newnode
        head = newnode;
    }

    else{
        while(t){ // while current node is not NULL
            if(newnode->token.count < t->token.count){ // if newnodes count is smaller than current nodes count adds it before the token
                if(prev != NULL){
                    prev->next = newnode;
                    newnode->next = t;
                }
                else{
                    Node* tmp = head;
                    head = newnode;
                    newnode->next = tmp;
                }
                break;
            }

            prev = t;
            t = t->next;
        }
        if(t == NULL){ // last node is newnode now
            prev->next = newnode;
        }
    }
    token_count++;
    changing_tokens++;
}

Node* PriorityQueue::pop()
{
    // YOU HAVE TO COMPLETE THIS PART
    Node* t = head;
    head = head->next; // pops from front, head becomes the node after head 
    changing_tokens--;
    return t;
}

void PriorityQueue::swap_nodes(Node** n1, Node** n2){ // swaps the data of nodes

    int tmp = (*n1)->token.count;
    string s = (*n1)->token.symbol;
    (*n1)->token.count = (*n2)->token.count;
    (*n1)->token.symbol = (*n2)->token.symbol;
    (*n2)->token.count = tmp;
    (*n2)->token.symbol = s;
}

void Huffman::get_priority_queue() // sorts the queue with increasing priority
{
    // YOU HAVE TO COMPLETE THIS PART
    Node* current = priority_queue.head;
    while(current && current->next){
        if(current->token.count > current->next->token.count){
            priority_queue.swap_nodes(&current,&(current->next)); //swaps the nodes and executes the same function until this condition never happens
            get_priority_queue();
        }
        else{
            current = current->next;
        }
    }
}

HuffmanBinaryTree::HuffmanBinaryTree()
{
    root = NULL;
}

Node * HuffmanBinaryTree::merge(Node *node1, Node *node2) //merges two nodes with their datas
{
    // YOU HAVE TO COMPLETE THIS PART
    string s = node1->token.symbol + node2->token.symbol;
    int c = node1->token.count + node2->token.count;
    Node* merged_node = new Node;
    merged_node->token.count = c; 
    merged_node->token.symbol = s;
    merged_node->left = node1;
    merged_node->right = node2;
    return merged_node; 
}

void HuffmanBinaryTree::delete_postorder_traversal(Node *traversal)
{
    if(traversal!=NULL) 
    {
        delete_postorder_traversal(traversal->left);
        delete_postorder_traversal(traversal->right);
        delete traversal;
    }
}

HuffmanBinaryTree::~HuffmanBinaryTree()
{
    delete_postorder_traversal(root);
    cout<<"Code with no memory leak ;)"<<endl;
    root = NULL;
}

void Huffman::get_huffman_tree()
{
    // YOU HAVE TO COMPLETE THIS PART 
    if(priority_queue.changing_tokens != 1){ //pops two elements with lowest frequencies from queue
        Node* n1 = priority_queue.pop();     //merges two nodes, adds the new merged node to queue and set the new root as merged
        Node* n2 = priority_queue.pop();     //and then calls function again until 1 token is remained
        Node* merged = huffman_binary_tree.merge(n1,n2);
        priority_queue.push(merged);
        huffman_binary_tree.root = merged;
        get_huffman_tree();
    }
  
}

void Huffman::get_codes(Node *traversal,string codepart)
{    
    // YOU HAVE TO COMPLETE THIS PART
    // A RECURSIVE FUNCTION APPENDS CODEPART STRING 1 OR 0 ACCORDING TO THE HUFFMAN BINARY TREE
    Node* left = traversal->left;
    Node* right = traversal->right;
    if(!left && !right){ //node with no childs, appends the final code and adds it to array.
        traversal->token.code = codepart;
        int i = findindex(token_array,traversal->token.symbol);
        token_array[i].code = codepart;
        return;
    }
    
    get_codes(left,codepart + "0"); // adds '0' to codepart and calls function
    get_codes(right,codepart + "1"); // adds '1' to codepart and calls function
    
}

string Huffman::return_code(string target)
{
    int index = findindex(token_array,target);
    return token_array[index].code;
}

double Huffman::calculate_compression_ratio()
{
    double bit_required_before = 0;
    token_count = priority_queue.token_count;
    for(int i=0;i<token_count;i++)
        bit_required_before += token_array[i].count * 8;
    double bit_required_after = 0;
    for(int i=0;i<token_count;i++)
        bit_required_after += token_array[i].count * token_array[i].code.length();
    return bit_required_before / bit_required_after;
}
