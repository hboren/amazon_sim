#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <set>
#include <map>
#include <vector>
#include <queue>

#include <iostream>
#include "util.h"
#include "datastore.h"

class MyDataStore: public DataStore{
public:
	MyDataStore();
	~MyDataStore();
	/**
	* Adds a product to the data store
	*/
	void addProduct(Product* p);

	/**
	* Adds a user to the data store
	*/
	void addUser(User* u);

	/**
		* Performs a search of products whose keywords match the given "terms"
		*  type 0 = AND search (intersection of results for each term) while
		*  type 1 = OR search (union of results for each term)
		*/
	std::vector<Product*> search(std::vector<std::string>& terms, int type);

	/**
		* Reproduce the database file from the current Products and User values
		*/
	void dump(std::ostream& ofile);

	/**
	* Add specified product from previous search to the specificied user's cart
	*/
	void add_to_cart(std::string username, int hit_number, std::vector<Product*> hits);

	/**
	* Outputs the specified user's cart in the displayString() format
	*/
	void view_cart(std::string username);
	
	/**
	* Iterates through the cart in the order items were added, if item in stock and user can afford
	it, remove from cart, subtract balance, subtract qty, otherwise just leave in cart
	*/
	void buy_cart(std::string username);



private:
	//add data member that is a map of usernames (keys) to carts (values)
	std::map<std::string, std::queue<Product*>> user_to_carts;
	//add another data member that is a map of keywords (keys) to set of products (values)
	std::map<std::string, std::set<Product*>> keyword_to_products;
	//vector that stores all of our products
	std::vector<Product*> all_products;
	//vector that stores all of our users
	std::vector<User*> all_users;
	//map that stores all usernames (keys) and associated users (values)
	std::map<std::string, User*> username_to_users;
};
#endif