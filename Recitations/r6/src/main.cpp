#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iomanip>

/* @Author
Student Name: Berat DALSUNA
Student ID : 150200002
Date: 10/01/2022 */

using namespace std;

string file_path;


bool perform_operation(char);
void print_menu();
void listProducts();
void listDay();



int main(int argc, char* argv[])
{
    bool end = false;
    char choice;
    ifstream inFile;
    cout << fixed << setprecision(2);

    file_path = argv[1];

    inFile.open(file_path,ios::in);
    if (!inFile.is_open()) 
    {
        cerr << "File cannot be opened";
        return EXIT_FAILURE;
    }

    while (!end)
    {
        print_menu();
        cin >> choice;
        end = perform_operation(choice);
    }
    
    inFile.close();
    return EXIT_SUCCESS;


}


void print_menu()
{
    cout << "Choose an operation" << endl;
    cout << "L: List 5 products with the highest revenue for total" << endl;
    cout << "D: List 5 products with the highest revenue for each day" << endl;
    cout << "E: Exit" << endl;
    cout << "Enter a choice {L, D, E}: ";
}

bool perform_operation(char choice)
{
    bool terminate = false;
    string strday;

    switch (choice)
    {
    case 'L':
    case 'l':
        listProducts();
        break;
    case 'D':
    case 'd':
        listDay();
        break;
    case 'E':
    case 'e':
            terminate = true;
        break;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        cin >> choice;
        terminate = perform_operation(choice);
        break;
    }
    return terminate;
}

void listProducts()
{
// *********************Fill this method 
    ifstream inFile;
    string str;
    map<string,double> productMap;

    inFile.open(file_path,ios::in);
    getline(inFile, str);
    while (getline(inFile, str)){
        string product = "";
        string price = "";
        string quantity = "";
        int order = 0; // order chooses which variable to change
        for(auto c: str){

            if (c != ' '){
                if (order == 0)
                    product += c;
                else if (order == 1)
                    price += c;
                else if (order == 2)
                    quantity += c;

            }

            else if (c == ' ') // order changes after space
                order++;
            
        }

        order = 0; // set order to zero for the new line
        
        if (productMap.count(product) == 1) // if map contains the product, increases old value
            productMap[product] += stod(price) * stod(quantity);
        
        else // if not contains, sets new value for the map
            productMap[product] = stod(price) * stod(quantity);
        
    }

    // Declare a multimap
    multimap<double, string> MM;
  
    // Insert every (key-value) pairs from productMap to MM as (value-key) pairs
    for (auto& it : productMap) {
        MM.insert({ it.second, it.first });
    }
  
    // Print the multimap
    cout << "5 products with the highest revenue for total are:" << endl; 
    int c = 0;
    for (auto it = MM.rbegin(); it != MM.rend(); it++) {
        cout << it->second << ' ' << it->first << endl;
        if (++c == 5) break;
    }

    inFile.close();
}



void listDay()
{
// *********************Fill this method 
ifstream inFile;
    string str;
    map<string,double> productMap;

    inFile.open(file_path,ios::in);
    getline(inFile, str);
    while (getline(inFile, str)){
        string product = "";
        string price = "";
        string day = "";
        string quantity = "";
        int order = 0;
        for(auto c: str){

            if (c != ' '){
                if (order == 0)
                    product += c;
                else if (order == 1)
                    price += c;
                else if (order == 2)
                    quantity += c;
                else if (order == 3)
                    day += c;
            }

            else if (c == ' ')
                order++;
            
            else order = 0;
        }
        
        if (productMap.count(product + "-" + day) == 1)
            productMap[product + "-" + day] += stod(price) * stod(quantity);
        
        else 
            productMap[product + "-" + day] = stod(price) * stod(quantity);
        
    }

    // Declare a multimap
    multimap<double, string> MM;
  
    // Insert every (key-value) pairs from productMap to MM as (value-key) pairs
    for (auto& it : productMap) {
        MM.insert({ it.second, it.first });
    }
  
    // Print the multimap
    char arr[7][10] = {"Monday","Sunday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}; 
    for(int i=0;i<7;i++){
    cout << "5 products with the highest revenue for " << arr[i] << " are:" << endl; 
    int c = 0;
    for (auto it = MM.rbegin(); it != MM.rend(); it++) {
        int pos = (it->second.find(arr[i]));
        if (pos != -1){
            cout << (it->second).erase(pos-1) << ' ' << it->first << endl;
            c++;
        }
        if (c == 5) break;

        }
    }

    inFile.close();
    
}