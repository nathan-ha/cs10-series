#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
 *  input s is the size of the array
 *  set s to be size
 *  initialize array of lists of WordEntry
 */
HashTable::HashTable(int s)
    : hashTable(new list<WordEntry>[s]),
      size(s)
{
}

HashTable::~HashTable()
{
    delete[] hashTable;
    hashTable = nullptr;
}

/* computeHash
 *  return an integer based on the input string
 *  used for index into the array in hash table
 *  be sure to use the size of the array to
 *  ensure array index doesn't go out of bounds
 */
int HashTable::computeHash(const string &s) const
{
    //TODO how the fuck do hash a string??

    //takes sum of chars and hash that
    int sum = 0;
    for (auto c : s)
    {
        sum += c;
    }
    return sum % size;
}

/* put
 *  input: string word and int score to be inserted
 *  First, look to see if word already exists in hash table
 *   if so, addNewAppearence with the score to the WordEntry
 *   if not, create a new Entry and push it on the list at the
 *   appropriate array index
 */
void HashTable::put(const string &s, int score)
{
    //im guessing we're using chaining
    int targetIndex = computeHash(s);
    auto &targetList = hashTable[targetIndex];  //found array where data should be
    //search list for word
    for (auto &entry : targetList)
    {
        if (entry.getWord() == s)
        {
            entry.addNewAppearance(score);
            return;
        }
    }
    //if word wasn't found, add it to the list
    targetList.push_back(WordEntry(s, score));
}

/* getAverage
 *  input: string word
 *  output: the result of a call to getAverage()
 *          from the WordEntry
 *  Must first find the WordEntry in the hash table
 *  then return the average
 *  If not found, return the value 2.0 (neutral result)
 */
double HashTable::getAverage(const string &s) const
{
    int targetIndex = computeHash(s);
    auto &targetList = hashTable[targetIndex];
    //search list for word
    for (const auto &entry : targetList)
    {
        if (entry.getWord() == s) return entry.getAverage();
    }
    return 2.0;
}

/* contains
 * input: string word
 * output: true if word is in the hash table
 *         false if word is not in the hash table
 */
bool HashTable::contains(const string &s) const
{
    int targetIndex = computeHash(s);
    auto &targetList = hashTable[targetIndex];
    //search list for word
    for (const auto &entry : targetList)
    {
        if (entry.getWord() == s) return true;
    }
    return false;
}
