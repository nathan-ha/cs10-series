//meta code--code that writes code
template <typename T, int MAXSIZE=100>
class Stack {
    T arr[MAXSIZE];
public:
    Stack();
};

Stack<int> s;
Stack<double,1000> ds;