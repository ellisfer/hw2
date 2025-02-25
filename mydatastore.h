#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>

#include <algorithm>

#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore {
  public:

    ~MyDataStore();

    // adds product to data store
    void addProduct(Product* p);

    // adds user to data store
    void addUser(User* u);

    //performs search of products whose keywords match given terms
    // type 0 = AND (intersection)
    // type 1 = OR (union)
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    // reproduce database file from current products and user values
    void dump(std::ostream& ofkeyile);
    void buyCart(std::string username);
    void viewCart(std::string username);
    void addCart(std::string username, int hit, std::vector<Product*>& hits);
    
  private: 
    std::map<std::string, User*> usermap_;
    std::map<std::string, std::set<Product*> > keymap_;
    std::vector<Product*> products_;
    std::vector<User*> users_;
    std::map<std::string, std::vector<Product*> > cart_; 
};

#endif