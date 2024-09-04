#include "bet.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stack>


BET::BET()
{
    start = nullptr;    //initialize root as null pointer
}

BET::BET(const string& postfix)
{
    start = nullptr;        //initialize root as nullptr
    buildFromPostfix(postfix);  //build tree from given postfix
}

BET::BET(const BET& n)
{
    start = clone(n.start); //deep copy of tree
}

BET::~BET()
{
    makeEmpty(start);   //deletes all nodes from tree
}

bool BET::buildFromPostfix(const string& postfix)
{
    stack<BinaryNode *> stack;  //stack container to hold nodes
    string node;                //string to hold each number of symbol
    istringstream pos(postfix); //read the postfix expression

    while(pos >> node)          //read each symbol from postfix
    {
        if(isalnum(node[0]))    //check if symbol is number or variable
        {
            BinaryNode *t = new BinaryNode(node, nullptr, nullptr); //leaf node
            stack.push(t);                                          //push node onto stack
        }
        else if(node == "+" || node == "-" || node == "*" || node == "/") //check if symbol is operator
        {
            BinaryNode *t = new BinaryNode(node, nullptr, nullptr);     //new node
            t->right = stack.top();                                     //set right node
            stack.pop();                                                //remove top node
            t->left = stack.top();                                      //set left node
            stack.pop();                                                //remove top node
            stack.push(t);                                              //push new tree onto stack
        }
        else                        
        {
            cout << "Cannot build the tree based on postfix\n";     //error message and return false
            return false;
        }
    }

    start = stack.top();                    //set tree root to node on the stack
    stack.pop();                            //clean stack

    return true;                            //return true when new tree is built successfully 
}

const BET & BET::operator=(const BET & n)   
{
    if(this != &n)          //check self assignment 
    {
        makeEmpty(start);       //clear tree
    }
    start = clone(n.start);     //deep copy the tree from n
    return *this;               //return by referance
}

void BET::printInfixExpression()const
{
    printInfixExpression(start);        //start printing from root
    cout << endl;
}

void BET::printPostfixExpression()const
{
    printPostfixExpression(start);      //start printing from root
    cout << endl;
}

size_t BET::size()const
{
    return size(start);             //return number of nodes in tree 
}

size_t BET::leaf_nodes()const
{
    return leaf_nodes(start);         //return number of leaves in tree 
}

bool BET::empty()const
{
    if(start == nullptr)            //if tree is empty return true by checking root
    {
        return true;
    }
    return false;                   //return false otherwise
}

void BET::printInfixExpression(BinaryNode *n)const
{
    if(n == nullptr)                //check if tree is empty
    {
        return;
    }

    if(n->left != nullptr && n->right != nullptr)  //if node has children add parenthesis
    {
        cout << "(";
    }
    printInfixExpression(n->left);              //print left subtree
    cout << n->element << " ";                  //print current element
    printInfixExpression(n->right);             //print right subtree

    if(n->left != nullptr && n->right != nullptr)       //if node has children closes the parenthesis
    {
        cout << ")";
    }

}

void BET::makeEmpty(BinaryNode* &t)
{
    if(t != nullptr)                //check if node is not null
    {
        makeEmpty(t->left);         //deallocate left subtree
        makeEmpty(t->right);        //deallocate right subtree
        delete t;                   //delete current node
    }
}

BET::BinaryNode * BET::clone(BinaryNode *t)const
{
    if(t == nullptr)        //if node is null return null
    {
        return nullptr;
    }
    else                    //clone the node and left and right subtree
    {
        return new BinaryNode(t->element, clone(t->left), clone(t->right));
    }
}

void BET::printPostfixExpression(BinaryNode *n)const
{
    if(n == nullptr)            //if node is null return 
    {
        return; 
    }
    printPostfixExpression(n->left);        //print left subtree
    printPostfixExpression(n->right);       //print right subtree
    cout << n->element << " ";              //print current node
}

size_t BET::size(BinaryNode *t)const
{
    if(t == nullptr)                        //if node is null return 0
    {
        return 0;
    }
    else                                    //count the nodes in the tree by adding 1 for root and the counting left and right subtree
    {
        return 1 + size(t->left) + size(t->right);
    }
}

size_t BET::leaf_nodes(BinaryNode *t)const
{
    if(t == nullptr)                         //if node is null return 0
    {
        return 0;
    }
    if(t->left == nullptr && t->right == nullptr)          //check if current node is leaf or not and return one if so
    {
        return 1;                                           
    }
    else                                                    //count lead nodes in left and right subtree and addd them
    {
        return leaf_nodes(t->left) + leaf_nodes(t->right);
    }
}