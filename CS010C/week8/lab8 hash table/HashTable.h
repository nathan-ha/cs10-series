#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <iostream>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#include "WordEntry.h"

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
