#include "util.h"
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string brand, const std::string size) :
	Product(category, name, price, qty),
    brand_(brand),
    size_(size)
{

}

Clothing::~Clothing()
{

}
/**
* Returns the appropriate keywords that this particular product should be associated with
*/
std::set<std::string> Clothing::keywords() const{
	//add all of the words in the brand's name and all of the words in the name/title

	//make copies of data members so don't modify original
	std::string temp_name = name_;
	std::string temp_brand = brand_;
	//change all data members to lowercase so common case
	temp_name = convToLower(temp_name);
	temp_brand = convToLower(temp_brand);

	//create sets to contain all keywords, name keywords, and brand keywords
	std::set<std::string> all_keywords;
	std::set<std::string> name_words;
	std::set<std::string> brand_words;
	//seperate name and brand into individual words
	name_words = parseStringToWords(temp_name);
	brand_words = parseStringToWords(temp_brand);

	//add found keywords into the set to be returned
	all_keywords.insert(name_words.begin(), name_words.end());
	all_keywords.insert(brand_words.begin(), brand_words.end());
	
	return all_keywords;
}

/**
* Returns a string to display the product info for hits of the search
*/
std::string Clothing::displayString() const{
	//format:
	/* <name>
		 Size: <size> Brand: <brand>
		 <price> <quantity> left.*/
	double rounded_price = ((double)((int)(price_ * 100 + .5)))/100;

  std::string price_string = std::to_string(rounded_price);
  std::string final_price = price_string.substr(0, price_string.find(".")+3);
	std::string display;
	display = name_ + '\n' + "Size: " + size_;
	display += " Brand: " + brand_ + '\n' + final_price + " ";
	display += std::to_string(qty_) + " left.";

	return display;

}

/**
* Outputs the product info in the database format
*/
void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

std::string Clothing::getBrand() const
{
    return brand_;
}

std::string Clothing::getSize() const
{
    return size_;
}
