/*
Program Name: Shunting Yard
Date: 11/28/2022
Author: Ji Min Yoon
Module Purpose: Designed to incorporate Arithmetic Algebraic Expressions, the different expression notations like Prefix, Postfix
and Infix, the evaluation order of the expressions (precedence), and how to convert an expression from one notation to another.

*/
// ShuntingYardTemplateSol.cpp : Defines the entry point for the console application.


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <stack>

using namespace std;

string inputFileNameStr = "expressions.txt";                  // Default location in solution folder

class OperatorMapClass {

private:
    typedef map<char, int>    OperatorPrecedenceMapType;
    OperatorPrecedenceMapType operatorMapObj;

public:

    OperatorMapClass() {
        operatorMapObj.insert(OperatorPrecedenceMapType::value_type('+', 1));
        operatorMapObj.insert(OperatorPrecedenceMapType::value_type('-', 2));
        operatorMapObj.insert(OperatorPrecedenceMapType::value_type('*', 3));
        operatorMapObj.insert(OperatorPrecedenceMapType::value_type('/', 4));
        // xxx insert code here to insert * and / in the map object
    }//OperatorMapClass ()

    bool isStackOperatorHigherPrecedence(char operatorChar, char operatorStackChar) {
        return((operatorMapObj.count(operatorStackChar))
            &&
            (operatorMapObj.at(operatorStackChar) >= operatorMapObj.at(operatorChar)));
    }//isStackOperatorHigherPrecedence()

    bool  isOperator(char token) {
        if (operatorMapObj.count(token))
            return (true);
        else
            return (false);

    }//isOperator()

};//OperatorMapClass

OperatorMapClass  operatorMapObj;

class ShuntingYardClass {

public:

    string createPostFixFrom(string infixString) {

        string       outputString;
        stack <char> operatorStackObj;

        for (char token : infixString) {
            switch (token) {
            case '/': case '*': case '+': case '-':
                while ((!operatorStackObj.empty()) && (operatorStackObj.top() != '(') && (operatorMapObj.isStackOperatorHigherPrecedence(token, operatorStackObj.top())))
                {
                    outputString.push_back(operatorStackObj.top());
                    operatorStackObj.pop();
                }//while

                operatorStackObj.push(token);
                break;

            case '(':
                operatorStackObj.push(token);
                break;

            case ')':
                while ((operatorStackObj.top()) != '(') {
                    outputString.push_back(operatorStackObj.top());
                    operatorStackObj.pop();
                }
                operatorStackObj.pop();
                break;

            default:
                outputString.push_back(token);
                break;

            }//switch
        }//for

        while (!operatorStackObj.empty())
        {
            outputString.push_back(operatorStackObj.top());
            operatorStackObj.pop();
        }

        return(outputString);

    }//postfix()	

};//ShuntingYardClass

class TreeNodeClass {
public:
    TreeNodeClass* left;
    char    value;
    TreeNodeClass* right;
};//TreeNodeClass

TreeNodeClass* BuildNewNodeObjPtrMethod(char value) {

    TreeNodeClass* newNodePtr = new TreeNodeClass;

    newNodePtr->value = value;
    newNodePtr->left = newNodePtr->right = NULL;
    return newNodePtr;
};

TreeNodeClass* ConstructBET(string postFixStr) {
    stack<TreeNodeClass*>  parseStack;
    TreeNodeClass* newNodePtr;
    OperatorMapClass    OperatorMapObj;

    // Process each character of the post-fix expression
    for (char token : postFixStr) {
        //Form a new node pointer
        newNodePtr = BuildNewNodeObjPtrMethod(token);

        if (OperatorMapObj.isOperator(token)) {
            // Operator, Put/Pop top 2 parse stack nodes into a new subtree as a
            newNodePtr->right = parseStack.top();
            parseStack.pop();
            newNodePtr->left = parseStack.top();
            parseStack.pop();

            parseStack.push(newNodePtr);
        }
        else {
            // operand, push node onto stack
            parseStack.push(newNodePtr);
        }

    }

    newNodePtr = parseStack.top();
    parseStack.pop();
    return newNodePtr;
};

string buildString;

void preorder(TreeNodeClass* treeNode) {
    if (treeNode)
    {
        buildString += treeNode->value;
        preorder(treeNode->left);
        preorder(treeNode->right);
    }
}

bool areParensRequired(TreeNodeClass* treeNode, char value) {
    OperatorMapClass operatorMapObj;
    if (operatorMapObj.isOperator(value) &&
        operatorMapObj.isOperator(treeNode->value) &&
        operatorMapObj.isStackOperatorHigherPrecedence(treeNode->value, value)) {
        buildString += '(';
        return true;
    }
    return false;
}

void inorder(TreeNodeClass* treeNode) {
    bool parensRequired = false;
    if (treeNode) {
        parensRequired = areParensRequired(treeNode->left, treeNode->value);
        inorder(treeNode->left);
        if (parensRequired)
            buildString += ')';
        buildString += treeNode->value;
        parensRequired = areParensRequired(treeNode->right, treeNode->value);
        inorder(treeNode->right);
        if (parensRequired)
            buildString += ')';
    }//if
}

void postorder(TreeNodeClass* treeNode) {
    if (treeNode)
    {
        postorder(treeNode->left);
        postorder(treeNode->right);
        buildString += treeNode->value;
    }

}

int main() {

    ifstream  inputFileStreamObj(inputFileNameStr);

    if (inputFileStreamObj.fail()) {
        cout << "File could not be opened !" << endl;

        return (EXIT_FAILURE);
    }//if

    string  infixExpressionStr,
        postfixExpressionStr;

    ShuntingYardClass shuntingYardObj;

    while (inputFileStreamObj >> infixExpressionStr) {

        cout << "InFix   Expression : " << infixExpressionStr << endl;
        postfixExpressionStr = shuntingYardObj.createPostFixFrom(infixExpressionStr);
        cout << "PostFix Expression : " << postfixExpressionStr << endl << endl;

        TreeNodeClass* expressionTreeRootPtr = ConstructBET(postfixExpressionStr);

        buildString = "";  preorder(expressionTreeRootPtr);
        cout << "Tree  pre-order expression is " << endl << buildString << endl << endl;

        buildString = "";  inorder(expressionTreeRootPtr);
        cout << "Tree  in-order expression is " << endl << buildString << endl << endl;

        buildString = "";  postorder(expressionTreeRootPtr);
        cout << "Tree  post-order expression is " << endl << buildString << endl << endl;

        cout << endl << endl;

    };//while

    inputFileStreamObj.close();

    cout << "Press the enter key once or twice to end." << endl;

    return EXIT_SUCCESS;

}//main()

