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
{
	//make the word lowercase
	rawWords = convToLower(rawWords);
	set<string> keywords;
	int curr = 0;
	int start = 0;
	//while we haven't reached the end of the string
	while(rawWords[curr]){
		//if a punctuation or a space is found, make a substring from the start
		//to right before the punctuation, trim spaces, update curr appropriately
		if(ispunct(rawWords[curr]) || isspace(rawWords[curr])){
			string str1 = rawWords.substr(start, curr-start);
			trim(str1);
			//if substring is at least 2 characters, insert into set and 
			//update start to be right after found punctuation
			if(str1.length() > 1){
				keywords.insert(str1);
			}
			start = curr + 1;
		}
		curr++;
	}
	//create a substring of the remaining string, trim, and if at least 2 chars,
	//insert into keyword set
	string str2 = rawWords.substr(start, rawWords.length()-start);
	trim(str2);
	if(str2.length() > 1){
		keywords.insert(str2);
	}

	return keywords;
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
