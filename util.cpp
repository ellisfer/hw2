#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{ // needs more for breaking punctuation
  set<std::string> snippets;
  rawWords = convToLower(rawWords);
  stringstream s(rawWords);

  std::string word;
  string snip;
  int wordstart = 0;
  int wordlen = 0;
  while(s >> word){
    //cout << " word! " << word << endl;
    wordstart = 0;
    for(size_t i = 0; i < word.size(); i++){
      //cout << "i = " << i << endl;
      if(!ispunct(word[i])){
        wordlen++;
        if(i == word.size()-1 && wordlen >=2){
          //cout << "inside end if " << endl;
          snip = word.substr(wordstart, wordlen);
          trim(snip);
          //cout << "making snippet! " << snip << endl;
          snippets.insert(snip);
          wordlen = 0;
        }
      }
      else{ // punctuation
        snip = word.substr(wordstart, wordlen);
        trim(snip);
        if(snip.size() >= 2){
         // cout << "making snippet! " << snip << endl;
          snippets.insert(snip);
        }
        //cout << "out of if???" << endl;
        wordstart = wordstart+wordlen +1;
        //cout << "wordstart: " << wordstart << endl;
        wordlen = 0;
      }
    }
  }

  return snippets;


}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
