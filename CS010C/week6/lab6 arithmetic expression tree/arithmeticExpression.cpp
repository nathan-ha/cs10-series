#include <string>
#include <stack>
#include <sstream>
#include <fstream>
using namespace std;

#include "arithmeticExpression.h"

arithmeticExpression::arithmeticExpression(const string & infixExpression)
  : infixExpression(infixExpression),
    root(nullptr)
{
  cout << "Try to build from: " << infixExpression << endl;
  cout << "In postfix this is: " << infix_to_postfix() << endl;
  throw std::runtime_error("create constructor");
}

void arithmeticExpression::infix() {
  throw std::runtime_error("create infix");
}
void arithmeticExpression::prefix() {
  throw std::runtime_error("create prefix");
}
void arithmeticExpression::postfix() {
  throw std::runtime_error("create postfix");
}
void arithmeticExpression::buildTree() {
  throw std::runtime_error("create buildTree");
}

void arithmeticExpression::visualizeTree(ofstream & out, TreeNode *T) {
  throw std::runtime_error("create infix");
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