#include <string>
#include <stack>
#include <sstream>
#include <fstream>
using namespace std;

#include "arithmeticExpression.h"

arithmeticExpression::arithmeticExpression(const string &infixExpression)
    : infixExpression(infixExpression),
      root(nullptr)
{
}

arithmeticExpression::~arithmeticExpression()
{
    burnTree(root);
    root = nullptr;
}

//helper for destructor, recursively deletes all nodes
void arithmeticExpression::burnTree(TreeNode *currNode)
{
    if (currNode == nullptr) return;
    burnTree(currNode->left);
    burnTree(currNode->right);
    delete currNode;
    currNode = nullptr;
}

//creates the expression tree
void arithmeticExpression::buildTree()
{
    string postfixExpression = infix_to_postfix();
    stack<TreeNode*> nodes;
    for (char c : postfixExpression)
    {
        bool isOperator = c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
        if (isOperator)
        {
            root = new TreeNode(c, c); // the operator will be the new root
            // connect parent to top two nodes and pop them
            root->right = nodes.top();
            nodes.pop();
            root->left = nodes.top();
            nodes.pop();
            nodes.push(root); // push the whole subtree back onto the stack
        }
        // otherwise push characters onto stack
        else
        {
            nodes.push(new TreeNode(c, c));
        }
    }
}

// prints tree in order
void arithmeticExpression::infix()
{
    infix(root);
}

// go left, print node, then go right
void arithmeticExpression::infix(TreeNode *currNode)
{
    if (currNode == nullptr) return;
    bool isLeaf = currNode->left == nullptr && currNode->right == nullptr;
    if (!isLeaf)  cout << '('; //wrap parentheses around non-leaf nodes so that individual letters do not have parentheses around them
    infix(currNode->left);
    cout << currNode->data;
    infix(currNode->right);
    if (!isLeaf) cout << ')';
}

// print tree in pre-order
void arithmeticExpression::prefix()
{
    prefix(root);
}

// print node, then go left, then right
void arithmeticExpression::prefix(TreeNode *currNode)
{
    if (currNode == nullptr) return;
    cout << currNode->data;
    prefix(currNode->left);
    prefix(currNode->right);
}

// print tree in post-order
void arithmeticExpression::postfix()
{
    postfix(root);
}

// go left, right, and print node
void arithmeticExpression::postfix(TreeNode *currNode)
{
    if (currNode == nullptr) return;
    postfix(currNode->left);
    postfix(currNode->right);
    cout << currNode->data;
}

void arithmeticExpression::visualizeTree(ofstream &out, TreeNode *T)
{
    if (T->left == nullptr || T->right == nullptr) return;
    out << "\t\"" << T->data << "\"" << " -> " << "\"" << T->left->data << "\"" << ';' << endl;
    out << "\t\"" << T->data << "\"" << " -> " << "\"" << T->right->data << "\"" << ';' << endl;
    visualizeTree(out, T->left);
    visualizeTree(out, T->right);

}

int arithmeticExpression::priority(char op)
{
    int priority = 0;
    if (op == '(')
    {
        priority = 3;
    }
    else if (op == '*' || op == '/')
    {
        priority = 2;
    }
    else if (op == '+' || op == '-')
    {
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix()
{
    stack<char> s;
    ostringstream oss;
    char c;
    for (unsigned i = 0; i < infixExpression.size(); ++i)
    {
        c = infixExpression.at(i);
        if (c == ' ')
        {
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
        { // c is an operator
            if (c == '(')
            {
                s.push(c);
            }
            else if (c == ')')
            {
                while (s.top() != '(')
                {
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else
            {
                while (!s.empty() && priority(c) <= priority(s.top()))
                {
                    if (s.top() == '(')
                    {
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else
        { // c is an operand
            oss << c;
        }
    }
    while (!s.empty())
    {
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename)
{
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open())
    {
        cout << "Error opening " << outputFilename << endl;
        return;
    }
    outFS << "digraph G {" << endl;
    visualizeTree(outFS, root);
    outFS << "}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}