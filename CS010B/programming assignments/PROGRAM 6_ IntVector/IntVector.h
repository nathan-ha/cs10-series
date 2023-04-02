#ifndef INTVECTOR_H
#define INTVECTOR_H

class IntVector {
    private:
        unsigned _size;
        unsigned _capacity;
        int* _data;
        void expand();
        void expand(unsigned amount); //TODO next
    public:
        IntVector(unsigned capacity = 0, int value = 0);
        ~IntVector();
        unsigned size() const;
        unsigned capacity() const;
        bool empty() const;
        const int & at(unsigned index) const;
        const int & front() const;
        const int & back() const;
        int & at(unsigned index);
        int & front();
        int & back();
        void insert(unsigned index, int value); //The insert and erase functions will pass in an unsigned index rather than an iterator.
        void erase(unsigned index);
        void assign(unsigned n, int value);
        void push_back(int value);
        void pop_back();
        void clear();
        void resize(unsigned n, int value = 0);
        void reserve(unsigned n);

};

#endif