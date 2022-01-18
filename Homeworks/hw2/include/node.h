/* @Author
Student Name: Berat Dalsuna
Student ID: 150200002
E-mail: dalsuna20@itu.edu.tr
Date: 24/12/2021
*/

class Node{
    private:
        Node* left;
        Node* right;
        int left_data; // stores the cost for left node
        int right_data; // stores the cost for right node
        int label; // city name
        int cost; // cost for reaching the node

    public:
        Node(int, int, int); // left_data, right_data, label
        Node* get_left();
        void set_left(Node*);
        Node* get_right();
        void set_right(Node*);
        void set_cost(int);
        int get_cost();
        int get_left_data();
        int get_right_data();
        void set_left_data(int);
        void set_right_data(int);
        int get_label();
};