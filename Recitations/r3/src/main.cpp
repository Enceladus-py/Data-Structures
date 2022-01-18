#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <string>
#include <iomanip>

/* @Author
    Student Name: Berat Dalsuna
    Student ID: 150200002
    Date: 9/11/2021S

*/
using namespace std;

void infix_to_postfix(string,string&);
bool higher_priority(char,char);
double eval_postfix(string);
double evaluate(double,double,char);

int main(){
    string infix;
    string postfix;
    bool is_exit = false;
    while(!is_exit)
    {
        cout<<"Input the expression in infix: ";
        cin>>infix;

        if (infix == "E" || infix == "e") 
            is_exit = true;

        else
        {
            infix_to_postfix(infix, postfix);
            cout<<postfix<<endl;
            cout<<setprecision(2)<<fixed<<eval_postfix(postfix)<<endl;
        }
        
        cin.clear();
        cin.ignore();
        infix.clear();
        postfix.clear();

    }
    return EXIT_SUCCESS;
}

void infix_to_postfix(string infix,string& postfix)
{
    stack<char> s;
    // *********************Fill this method 
    for(unsigned int i=0;i<(infix.length());i++){ // iterating over infix string

        if(isdigit(infix[i])){
            postfix += infix[i];
        }
        else{
            if(s.empty()){
                s.push(infix[i]);
            }
            else{
                if(infix[i] != s.top() && higher_priority(infix[i],s.top())){ // if not equal and have a priority, push to stack
                    s.push(infix[i]);
                    continue;
                }
                while(!(s.empty()) && higher_priority(s.top(),infix[i])){ //while stack is not empty and have a priority, add top to postfix and pop the top
                    postfix += s.top();
                    s.pop();
                }
                s.push(infix[i]); // push the operator to stack
            }
        }
    }
    while(!(s.empty())){ // add the whole stack to postfix 
        postfix += s.top();
        s.pop();
    }
}




bool higher_priority(char first,char second){
    if(first=='/' && second=='*') // added by Berat
        return true;
    else if(second=='+' || second=='-')
        return true;
    else if(first=='*' || first=='/')
        return false;
    else return false;
}

double eval_postfix(string expr){
    stack<double> s;
    double first, second;
    // *********************Fill this method 
    for(unsigned int i=0;i<(expr.length());i++){
        if(isdigit(expr[i])){
            s.push(expr[i] - 48); // converting char to double by extracting 48. (comes from ascii table)
        }
        else{ // evaluates the result with the last two elements in the stack
            first = s.top();
            s.pop();
            second = s.top();
            s.pop();
            s.push(evaluate(second,first,expr[i]));
        }
    }
    return s.top();
}

double evaluate(double first,double second,char c){
    switch(c){
        case '*':
            return first*second;
        case '+':
            return first+second;
        case '-':
            return first-second;
        case '/':
            return first/second;
        default:
            return 0;
    }
}
