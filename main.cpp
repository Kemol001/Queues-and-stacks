#include <iostream>
#include <string>
#include <cmath>
#include "StackSLL.h" 
#include "QueueSLL.h"
using namespace std;

//Mostafa Hesham Allam 20206126 S1
//Karim Amr Hamdy Mohamed 20206138 S1

//used to get the rank of the operation (priority)
int getRank(char _operator){
    if(_operator=='^')
        return 2;
    else if(_operator=='*'||_operator=='/')
        return 1;
    else if(_operator=='+'||_operator=='-')
        return 0;
    return -1;
}

//checks if the expression got balanced brackets or not.
bool chkBalanced(string expression){
    StackSLL<char> s;
    for(int i=0 ; i<expression.length() ; i++){
        switch (expression[i]){
        case '{':
            s.push('}');
            break;
        case '[':
            s.push(']');
            break;
        case '<':
            s.push('>');
            break;
        case '(':
            s.push(')');
            break;
        
        case '}': case ']' : case '>' : case ')' :
            if(expression[i]==s.top())
                s.pop();
            else
                return false;
            break;
        }
    }
    return s.isEmpty();
};

//Converts a number to binary using stack 
string convertToBinary(int number){
    StackSLL<char> s;
    string binary="";
    int remainder=number;
    while(remainder>0){
        if(remainder%2){
            s.push('1');
            remainder=(remainder-1)/2;
        }
        else{
            s.push('0');
            remainder=remainder/2;
        }
    }
    while(!(s.isEmpty()))
        binary+=(s.pop());
    
    return binary;
};

//converts infix expression to postfix using a stack
string convertInfixToPostfix(string expression){
    StackSLL<char> s;
    string result="";
    int rank1,rank2;

    for(int i=0 ; i<expression.length() ; i++){
        if(expression[i]==' ') continue;

        if(expression[i]==')'){
            while(s.top()!='('){
                result+=s.pop();
            }
            s.pop();
        }

        else if(expression[i]=='('){
            s.push(expression[i]);
        }

        else if(!isdigit(expression[i])){
            if(!(s.isEmpty()))
                if(getRank(s.top())>=getRank(expression[i]))
                    result+=s.pop();
            s.push(expression[i]);
        }

        else{
            result+=expression[i];
        }
    }
    while(!(s.isEmpty()))
        result+=s.pop();
    
    return result;
};

//Evaluates the result of a postfix expression
int evaluatePostfix(string expression){
    StackSLL<int> s;
    int result=0,temp1,temp2;
    for(int i=0 ; i<expression.length() ; i++){
        if(expression[i]==' ') continue;
        if(isdigit(expression[i]))
            s.push((int)(expression[i])-48);
        else{
            switch (expression[i]){
            case '^':
                temp2=s.pop();
                temp1=s.pop();
                s.push(pow(temp1,temp2));
                break;
            case '*':
                temp2=s.pop();
                temp1=s.pop();
                s.push(temp1*temp2);
                break;
            case '/':
                temp2=s.pop();
                temp1=s.pop();
                s.push(temp1/temp2);
                break;
            case '+':
                temp2=s.pop();
                temp1=s.pop();
                s.push(temp1+temp2);
                break;
            case '-':
                temp2=s.pop();
                temp1=s.pop();
                s.push(temp1-temp2);
                break;
            }
        }
    }
    return s.pop();
};

//Moves an element in the nth place to the first index in the queue
//returns true if done , false if the nth element doesn't exist
template<class T>
bool moveNthElem(QueueSLL<T> &queue,int n){
    QueueSLL<T> temp;
    bool isFound=false;
    T elem;
    for(int i=1 ; !(queue.isEmpty()) ; i++){
        if(i==n){
            elem=queue.dequeue();
            isFound=true;
        }
        temp.enqueue(queue.dequeue());
    }
    if(isFound)
        queue.enqueue(elem);

    while(!(temp.isEmpty()))
        queue.enqueue(temp.dequeue());

    return isFound;
}

//reverses a queue using a stack
template<class T>
void reverseQueue(QueueSLL<T>& queue){
    StackSLL<T> s;
    while(!(queue.isEmpty()))
        s.push(queue.dequeue());
    while (!(s.isEmpty()))
        queue.enqueue(s.pop());
}


int main(){
    char choice;
    string sTemp;
    int nTemp;
    while(true){
    cout<<"======================================\n"<<
        "1- Check for balanced brackets.\n"<<
        "2- Convert to binary.\n"<<
        "3- Convert infix to postfix expression and evaluate.\n"<<
        "4- Move Nth element to front in a queue of strings.\n"<<
        "5- Reverse elements of a queue of doubles.\n"<<
        "6- Exit.\n"<<
        "======================================\n"<<
        "Choice : ";
    cin>>choice;
        switch (choice){
            case '1':
                cout<<"Enter expression : ";
                cin>>sTemp;
                if(chkBalanced(sTemp))
                    cout<<"Expression balanced.\n";
                else
                    cout<<"Expression not balanced.\n";
                break;

            case '2':
                cout<<"Enter decimal number : ";
                cin>>nTemp;
                cout<<convertToBinary(nTemp)<<endl;
                break;

            case '3':
                cout<<"Enter expression : ";
                cin>>sTemp;
                if(chkBalanced(sTemp)){
                    sTemp=convertInfixToPostfix(sTemp);
                    cout<<"Postfix expression : "<<sTemp<<endl;
                    cout<<"Expression evaluation : "<<evaluatePostfix(sTemp)<<endl;
                }
                else
                    cout<<"Error ,Expression not balanced.\n";
                break;
            
            case '4':
                {QueueSLL<string> sQueue;
                cout<<"Enter strings with (Stop.) to stop :- \n";
                for(int i=1 ; true ; i++){
                    cout<<"Element "<<i<<" : ";
                    cin>>sTemp;
                    if(sTemp=="Stop.")
                        break;
                    sQueue.enqueue(sTemp);
                }
                cout<<"Enter nth element to move : ";
                cin>>nTemp;
                if(moveNthElem(sQueue,nTemp)){
                    while(!(sQueue.isEmpty()))
                        cout<<sQueue.dequeue()<<" ";
                }
                else
                    cout<<"Element "<<nTemp<<" out of bounds";
                }
                cout<<endl;
                break;

            case '5':
                {QueueSLL<double> dQueue;
                cout<<"Enter doubles with (Stop.) to stop :- \n";
                for(int i=1 ; true ; i++){
                    cout<<"Element "<<i<<" : ";
                    cin>>sTemp;
                    if(sTemp=="Stop.")
                        break;
                    dQueue.enqueue(stod(sTemp));
                }
                reverseQueue(dQueue);
                while(!(dQueue.isEmpty()))
                        cout<<dQueue.dequeue()<<" ";
                }
                cout<<endl;
                break;

            case '6':
                cout<<"======================================";
                return 0;

            default:
                cout<<"Invalid , try again. \n";
                break;
        }
    }
}