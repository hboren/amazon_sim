#include "mydatastore.h"


using namespace std;

MyDataStore::MyDataStore() 
{

}

MyDataStore::~MyDataStore()
{
	//deallocate all of the dynamically allocated users & products
	for(std::vector<User*>::iterator it = all_users.begin(); it != all_users.end(); ++it){
		User* temp = *it;
		delete (temp);
	}
	for(std::vector<Product*>::iterator it = all_products.begin(); it != all_products.end(); ++it){
		Product* temp = *it;
		delete (temp);
	}
}

/**
* Adds a product to the data store
*/
void MyDataStore::addProduct(Product* p){
	//add product to product vector
	all_products.push_back(p);
	//get keywords of product p
	set<std::string> keywords = p->keywords();
	//iterate through keywwords, see if it is already in your map or not
	for(set<std::string>::iterator it=keywords.begin(); it != keywords.end(); ++it)
	{
		//if that keyword is already in the map of keywords to products,
		//add p to that key's product set
		if(keyword_to_products.find(*it) != keyword_to_products.end()) {
  		keyword_to_products[*it].insert(p);
		}
		//else if not already in map, create a new set of products, 
		//add p to that set, and then add a new pair with the keyword
		//and created product set
		else {
			set<Product*> new_prod_set;
			new_prod_set.insert(p);
  		keyword_to_products.insert(std::make_pair(*it, new_prod_set));
		}
	}
}

/**
* Adds a user to the data store
*/
void MyDataStore::addUser(User* u){
	//add user to user database
	all_users.push_back(u);
	std::string username = u->getName();
	//search to see if user is already in the database
	std::map<std::string, User*>::iterator it = username_to_users.find(username);
	if (it == username_to_users.end()) // if not in the database yet
	{
		//add to the username to user database, create a cart for new user
		//add username and cart to the username cart map
		username_to_users.insert(std::make_pair(username, u));
		queue<Product*> cart;
		user_to_carts.insert(std::make_pair(username, cart));
	}
}

/**
	* Performs a search of products whose keywords match the given "terms"
	*  type 0 = AND search (intersection of results for each term) while
	*  type 1 = OR search (union of results for each term)
	*/
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
	std::set<Product*> hits_set;
	std::vector<Product*> hits_vec;
	if(type == 0){
		//do AND search (intersection)
		//iterate over the terms given, for each term, search the keyword to
		//products map to see if given term is in it, if so, call intersection
		
		//first loop to make hits_set the first set that has a keyword so intersection works
		//as intended (won't work properly on an empty set)
		for(std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it){
			std::map<std::string, std::set<Product*>>::iterator it2 = keyword_to_products.find(*it);
			if (it2 != keyword_to_products.end()) // in the database
			{
				hits_set = keyword_to_products[*it];
				break;
			}		
		}
		//then loop over terms and search the keyword to products map to see if keyword is in there
		//then call intersection on hit_set and that set until looped over all terms
		for(std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it){
			std::map<std::string, std::set<Product*>>::iterator it2 = keyword_to_products.find(*it);
			if (it2 != keyword_to_products.end()) // in the database
			{
				hits_set = setIntersection(hits_set, keyword_to_products[*it]);
			}		
		}		
	}
	else if(type == 1){
		//do OR search (union)
		//iterate over the terms given, for each term, search the keyword to 
		//products map to see if given term is in it, call union: union(hits,product set)
		for(std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it){
			std::map<std::string, std::set<Product*>>::iterator it2 = keyword_to_products.find(*it);
			if (it2 != keyword_to_products.end()) // in the database
			{
				hits_set = setUnion(hits_set, keyword_to_products[*it]);
			}		
		}
	}
	//turn set of products into vector of products
	for(std::set<Product*>::iterator it=hits_set.begin(); it != hits_set.end(); ++it)
	{	
  	hits_vec.push_back(*it);
	}		
	
	return hits_vec;
}

/**
	* Reproduce the database file from the current Products and User values
	*/
void MyDataStore::dump(std::ostream& ofile){
	//call existing dump function on all products
	ofile << "<products>" << endl;
	for(std::vector<Product*>::iterator it = all_products.begin(); it != all_products.end(); ++it){
		Product* to_dump = *it;
		to_dump->dump(ofile);
	}
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;
	//call existing dump function on all users
	for(std::vector<User*>::iterator it = all_users.begin(); it != all_users.end(); ++it){
		User* to_dump = *it;
		to_dump->dump(ofile);
	}
	ofile << "</users>" << endl;
}

/**
* Add specified product from previous search to the specificied user's cart
*/
void MyDataStore::add_to_cart(std::string username, int hit_number, std::vector<Product*> hits){
	username = convToLower(username);
	std::map<std::string, User*>::iterator it = username_to_users.find(username);
	//hit number impossible to be in hits, invalid
	if(hit_number > (int)hits.size()){
		cout << "Invalid Request" << endl;
	}
	//username not in database, invalid
	else if (it == username_to_users.end()) // username does not exist
	{
		cout << "Invalid Request";
	}
	//add hit product specified by user to cart queue
	else{
		Product* cart_product = hits[hit_number-1];
		user_to_carts[username].push(cart_product);	
	}
}

/**
* Outputs the specified user's cart in the displayString() format
*/
void MyDataStore::view_cart(std::string username){
	username = convToLower(username);
	//create a temporary cart so don't modify actual
	std::queue<Product*> temp_cart;
	std::map<std::string, std::queue<Product*>>::iterator it = user_to_carts.find(username);
	if (it == user_to_carts.end()) // username does not exist
	{
		cout << "Invalid Request";
	}
	else{
		temp_cart = user_to_carts[username];
	}
	int i = 1;
	while (!temp_cart.empty())//iterate over temp cart, display each item and pop to access next item
    {
        Product* front = temp_cart.front();
				cout << i << endl;
				cout << (front)->displayString() << endl << endl;
        temp_cart.pop();
				i++;
    }
}

/**
* Iterates through the cart in the order items were added, if item in stock and user can afford
it, remove from cart, subtract balance, subtract qty, otherwise just leave in cart
*/
void MyDataStore::buy_cart(std::string username){

	username = convToLower(username);
	std::queue<Product*> temp_cart;
	std::queue<Product*> didnt_buy_cart;
	User* user;
	//find the users cart
	std::map<std::string, std::queue<Product*>>::iterator it = user_to_carts.find(username);
	if (it == user_to_carts.end()) // username does not exist
	{
		cout << "Invalid Request";
	}
	//else if username does exist
	else{
		temp_cart = user_to_carts[username];
		user = username_to_users[username];
		//iterate over the cart
		while(!temp_cart.empty()){
			Product* curr = temp_cart.front();
			//if product is in stock and user can afford it, "buy" aka subtract balance, qty, and remove
			if(curr->getQty()>0 && curr->getPrice() <= user->getBalance()){
				user->deductAmount(curr->getPrice());
				curr->subtractQty(1);
				temp_cart.pop();
			}
			else //if not in stock or cannot afford it, leave item in cart and move to next one
			{
				didnt_buy_cart.push(temp_cart.front());
				temp_cart.pop();
			}
		}
	}
	//reset cart to be the items that couldn't be bought
	user_to_carts[username] = didnt_buy_cart;
}
