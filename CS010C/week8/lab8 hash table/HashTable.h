#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class HashTable
{
private:
	list<WordEntry> *hashTable;
	int size;

public:
	HashTable(int);
	~HashTable();
	bool contains(const string &) const;
	double getAverage(const string &) const;
	void put(const string &, int);

private:
	HashTable(const HashTable &);
	HashTable operator=(const HashTable &);
	int computeHash(const string &) const;
};

#endif
