#ifndef CLOTHING_H
#define CLOTHING_H

#include "util.h"
#include "product.h"

class Clothing: public Product{
public:
	Clothing(const std::string category, const std::string name, double price, int qty, const std::string brand, const std::string size);
	~Clothing();

	/**
  * Returns the appropriate keywords that this clothing item should be associated with
  */	
	std::set<std::string> keywords() const;

	/**
  * Returns a string to display the product info for hits of the search
  */	
	std::string displayString() const;

	/**
	* Outputs the clothing info in the database format
	*/	
	void dump(std::ostream& os) const;

	/**
	* Accessors
	*/
	std::string getBrand() const;
	std::string getSize() const;

private:
	std::string brand_;
	std::string size_;
};
#endif