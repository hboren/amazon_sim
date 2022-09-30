#include "util.h"
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
	Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

Movie::~Movie()
{

}
/**
* Returns the appropriate keywords that this particular product should be associated with
*/
std::set<std::string> Movie::keywords() const{
	//add the genre and all of the words in the name/title

	//make copies of data members so don't modify orig
	std::string temp_name = name_;
	std::string temp_genre = genre_;
	//change all data members to lowercase so in common case
	temp_name = convToLower(temp_name);
	temp_genre = convToLower(temp_genre);

	//create sets to contain all keywords and name keywords
	std::set<std::string> all_keywords;
	std::set<std::string> name_words;
	//seperate name into individual words
	name_words = parseStringToWords(temp_name);

	//add found keywords into the set to be returned
	all_keywords.insert(name_words.begin(), name_words.end());
	all_keywords.insert(temp_genre);
	
	return all_keywords;
}

/**
* Returns a string to display the product info for hits of the search
*/
std::string Movie::displayString() const{
	//format:
	/*<name>
	Genre: <genre> Rating: <rating>
	<price> <quantity> left.*/
	double rounded_price = ((double)((int)(price_ * 100 + .5)))/100;
  std::string price_string = std::to_string(rounded_price);
  std::string final_price = price_string.substr(0, price_string.find(".")+3);

	std::string display;
	display = name_ + '\n' + "Genre: " + genre_;
	display += " Rating: " + rating_ + '\n' + final_price + " ";
	display += std::to_string(qty_) + " left.";

	return display;

}

/**
* Outputs the product info in the database format
*/
void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

std::string Movie::getGenre() const
{
    return genre_;
}

std::string Movie::getRating() const
{
    return rating_;
}
