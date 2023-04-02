#include <iostream>
#include <string>

using namespace std;


void flipString(string &s);

int main() {
   string line;
   cout << "Enter a sentence:" << endl;
   getline(cin, line);
   cout << endl;
   cout << line << endl;
   flipString(line);
   cout << line << endl;

   return 0;
}

void flipString(string &s) {
   //base case: size is 1; since nothing else happens in this case, we only need to check != 0
   if (s.size() != 0) {
      //cuts off the last character and saves it, appending it after the base case is reached
      char lastLetter = s.back();
      s.pop_back();
      flipString(s);
      //basically pre-pending the last character to string after it becomes empty
      s = lastLetter + s;
   }
}

