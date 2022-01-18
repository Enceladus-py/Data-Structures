#include "node.h"

/* @Author
Student Name: Berat Dalsuna
Student ID: 150200002
E-mail: dalsuna20@itu.edu.tr
Date: 24/12/2021
*/

class Tree{
    private:
        Node* root;

    public:
        Tree();
        ~Tree();
        void postorder_destruct(Node*); // called in destructor
        Node* get_root();
        void set_root(Node*);
        Node* find_node(Node*, int); // finds node according to given label
        void print_tree(Node*); // prints the tree in preorder traversal
        void find_cost(Node*, int ,int); // finds the minimum cost for a single node 
        void remove_link(Node*,int,int, int); // called in find_cost function in order to remove links with bigger costs
        void find_all_costs(Node*); // finds all costs for tree.
};  