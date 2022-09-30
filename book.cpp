#include "util.h"
#include "book.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) : 
	Product(category, name, price, qty),
    isbn_(isbn),
    author_(author)
{

}

Book::~Book()
{

}
/**
* Returns the appropriate keywords that this particular product should be associated with
*/
std::set<std::string> Book::keywords() const{
	//add all of the words in the author's name, all of the words in the name/title, the isbn as a whole
	//make copies of data members so don't modify original
	std::string temp_name = name_;
	std::string temp_author = author_;
	//change all data members to lowercase so in common case
	temp_name = convToLower(temp_name);
	temp_author = convToLower(temp_author);

	//create sets to contain all keywords, name keywords, and author keywords
	std::set<std::string> all_keywords;
	std::set<std::string> name_words;
	std::set<std::string> auth_words;
	//seperate name and author into individual words
	name_words = parseStringToWords(temp_name);
	auth_words = parseStringToWords(temp_author);

	//add found keywords into the set to be returned
	all_keywords.insert(isbn_);
	all_keywords.insert(name_words.begin(), name_words.end());
	all_keywords.insert(auth_words.begin(), auth_words.end());
	
	return all_keywords;
}

/**
* Returns a string to display the product info for hits of the search
*/
std::string Book::displayString() const{
	//format:
	/*<name>
	Author: <author> ISBN: <isbn>
	<price> <quantity> left.*/
	double rounded_price = ((double)((int)(price_ * 100 + .5)))/100;

  std::string price_string = std::to_string(rounded_price);
  std::string final_price = price_string.substr(0, price_string.find(".")+3);

	std::string display;
	display = name_ + '\n' + "Author: " + author_;
	display += " ISBN: " + isbn_ + '\n' + final_price + " ";
	display += std::to_string(qty_) + " left.";

	return display;

}

/**
* Outputs the product info in the database format
*/
void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

std::string Book::getIsbn() const
{
    return isbn_;
}

std::string Book::getAuthor() const
{
    return author_;
}
