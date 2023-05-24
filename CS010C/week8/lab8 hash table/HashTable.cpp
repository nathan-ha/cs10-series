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
    int sum = 0;
	int position = 1;
	//sum all characters in a string
    for (auto ch : s)
    {
		//multiplying char by its position so that we get a different hash for strings with the same chars in different order
        sum += static_cast<int>(ch) * position;
		position++;
    }
	//squaring the sum so that the whole range of the (probably very large) array is accounted for
    return (sum * sum) % size;
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
    //search for location of list containing string
    int targetIndex = computeHash(s);
    auto &targetList = hashTable[targetIndex];  //found array where data should be
    //search list for word
    for (auto &entry : targetList)
    {
        if (entry.getWord() == s)
        {
            //in case the word is already in the list
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
    //search for location of list containing string
    int targetIndex = computeHash(s);
    auto &targetList = hashTable[targetIndex];
    //search list for word
    for (const auto &entry : targetList)
    {
        //found the word
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
    //search for location of list containing string
    int targetIndex = computeHash(s);
    auto &targetList = hashTable[targetIndex];
    //search list for word
    for (const auto &entry : targetList)
    {
        //found word
        if (entry.getWord() == s) return true;
    }
    return false;
}

//putting main here because zybooks doesn't let me submit a main.cpp
int main()
{
	// declare a few needed variables for inputing the data
	string line;
	int score;
	string message = " ";

	// open input file
	ifstream myfile("movieReviews.txt");
	if (myfile.fail())
	{
		cout << "could not open file" << endl;
		exit(1);
	}

	// create hash table
	HashTable table(20071);

	while (!myfile.eof())
	{
		myfile >> score; // get score
		myfile.get();	 // get blank space
		getline(myfile, line);
		int len = line.size();
		while (len > 0)
		{ // identify all individual strings
			string sub;
			len = line.find(" ");
			if (len > 0)
			{
				sub = line.substr(0, len);
				line = line.substr(len + 1, line.size());
			}
			else
			{
				sub = line.substr(0, line.size() - 1);
			}
			table.put(sub, score); // insert string with the score
		}
	}

	// after data is entered in hash function
	// prompt user for a new movie review
	while (message.length() > 0)
	{
		cout << "enter a review -- Press return to exit: " << endl;
		getline(cin, message);

		// used for calculating the average
		double sum = 0;
		int count = 0;

		double sentiment = 0.0;

		size_t len = message.size();
		// get each individual word from the input
		while (len != string::npos)
		{
			string sub;
			len = message.find(" ");
			if (len != string::npos)
			{
				sub = message.substr(0, len);
				message = message.substr(len + 1, message.size());
			}
			else
			{
				sub = message;
			}
			// calculate the score of each word
			sum += table.getAverage(sub);
			++count;
		}

		if (message.size() > 0)
		{
			sentiment = sum / count;
			cout << "The review has an average value of " << sentiment << endl;
			if (sentiment >= 3.0)
			{
				cout << "Positive Sentiment" << endl;
			}
			else if (sentiment >= 2.0)
			{
				cout << "Somewhat Positive Sentiment" << endl;
			}
			else if (sentiment >= 1.0)
			{
				cout << "Somewhat Negative Sentiment" << endl;
			}
			else
			{
				cout << "Negative Sentiment" << endl;
			}
			cout << endl;
		}
	}
	return 0;
}

