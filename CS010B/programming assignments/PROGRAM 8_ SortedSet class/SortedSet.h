#pragma once
#include "IntList.h"

class SortedSet : public IntList {

    public:
        SortedSet();
        SortedSet(const SortedSet &);
        SortedSet(const IntList &);
        ~SortedSet();

        //accessors
        bool in(int value) const;
        SortedSet operator|(const SortedSet &rhs) const;
        SortedSet operator&(const SortedSet &rhs) const;

        //mutators
        void add(int value);
        void push_front(int value);
        void push_back(int value);
        void insert_ordered(int value);
        SortedSet operator|=(const SortedSet &rhs);
        SortedSet operator&=(const SortedSet &rhs);
};