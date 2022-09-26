#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	//return a set with only things that appear in both sets
	std::set<T> intersection_;

	//add items that are in both set 1 and 2 into to intersection set
	for(typename std::set<T>::iterator it1=s1.begin(); it1 != s1.end(); ++it1)
	{
		//check if item in s1 is also in set2. if so, add to set
		if(s2.find(*it1) != s2.end()){
			intersection_.insert(*it1);
		}
	}

	return intersection_;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	//return a set with things that appear either set
	std::set<T> union_;

	//add items from set1 to union
	for(typename std::set<T>::iterator it1=s1.begin(); it1 != s1.end(); ++it1)
	{
		union_.insert(*it1);
	}

	//add items from set2 that aren't already in set1 to union
	for(typename std::set<T>::iterator it2=s2.begin(); it2 != s2.end(); ++it2)
	{
		//check if item in set2 is in set1 (aka already added). if not, add to union
  	if(s1.find(*it2) == s1.end()){
			union_.insert(*it2);
		}
	}

	return union_;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
