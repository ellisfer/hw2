#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include "util.h"
#include "mydatastore.h"

using namespace std;
// --gtest_filter=MyTest.TestOne  -- (first arg, second)
MyDataStore::~MyDataStore(){
  for(size_t i = 0; i < products_.size(); i++){
    //cout << products_[i] << " " << products_[i]->getName() << endl;
    if(products_[i] != nullptr){
      delete products_[i];
    }
    
  }

  for(size_t i = 0; i < users_.size(); i++){
    if(users_[i] != nullptr){
      delete users_[i];
    }
    
  }
}


void MyDataStore::addProduct(Product* p){
  //cout << "productsize " << products_.size();
  if(p == nullptr){
    return;
  }
  // cout << p->getName() << endl;
  // cout << p->getPrice() << endl;
  // cout << p->getQty() << endl;
  // cout << p->displayString() << endl;
  
  if(find(products_.begin(), products_.end(), p) == products_.end()){
    products_.push_back(p);
    set<string> keys = p->keywords();
    set<string>::iterator it;

    for(it = keys.begin(); it != keys.end(); ++it){
      //cout << "mydatastore 49 keymap insert " << *it << endl;
      keymap_[convToLower(*it)].insert(p);
    }

  }
  else{
    p->subtractQty(-1);
  }

  
}

void MyDataStore::addUser(User* u){
  users_.push_back(u);
  usermap_[u->getName()] = u;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
  // 0 is and, 1 is or 
  int startterm = 0;
  vector<Product*> returnresults={};
  while(startterm < terms.size() && keymap_.find(terms[startterm]) == keymap_.end()){
    startterm++;
    // cout << "increment " << startterm << endl;
    // cout << "size " << terms.size() << endl;
  }
  if(startterm >= terms.size()){
    //cout << "returning results "<< endl;
    return returnresults;
  }
  
  // cout << "mydatastore.cpp 79, printing keywords: " << endl;
  // for(int i = 0; i < terms.size(); i++){
  //   cout << terms[i] << " ";
  // }
  // cout << endl;


  set<Product*> searchresults = keymap_[terms[startterm]];
  for(int i = startterm + 1; i < terms.size(); i++){
    if(keymap_.find(terms[i]) != keymap_.end()){
      if(type == 0){
      searchresults = setIntersection(keymap_[terms[i]], searchresults);
      // // printing results
      // cout << "results of keymap" << endl;
      // set<Product*>::iterator it3;
      // for(it3 = keymap_[term].begin(); it3!= keymap_[term].end(); ++it3){
      //   cout << (*it3)->getName() << endl;
      // }
      // cout << "ending results" << endl << endl;
    }
    else if(type == 1){
      searchresults = setUnion(keymap_[terms[i]], searchresults);
    }
    }
    
  }
  set<Product*>::iterator it;
  for(it = searchresults.begin(); it != searchresults.end(); ++it){
    returnresults.push_back(*it);
  }
  return returnresults;
}

void MyDataStore::dump(std::ostream& ofile){
  // cout << "in dump" << endl;
  // cout << " size " << products_.size();
  ofile<< "<products>" << endl;
  // run through products
  for(size_t i = 0; i < products_.size(); i++){
    //cout << " i = " << endl;
    if(products_[i] != nullptr){
      // cout << "Name! " << endl;
      // cout << products_[i]->getName() << endl;
      products_[i]->dump(ofile);
    }
    else{
      cout << "PRODUCT NULLPTR ALERT" << endl;
    }
    
  }
  ofile << "</products>" << endl;

  // users_
  ofile << "<users>" << endl;
  for(size_t i = 0; i < users_.size(); i++){
    if(users_[i] != nullptr){
      users_[i]->dump(ofile);
    }
    else{
      cout << "USER NULLPTR ALERT" << endl;
    }
    
  }
  ofile << "</users>" << endl;
}

void MyDataStore::addCart(string username, int hit, vector<Product*>& hits){
  // if username and hit valid:
  // took out cart search
  // took out , vector<Product*>& hits
  if(usermap_.find(username) == usermap_.end()){
    cout <<"Invalid request" << endl;
    return;
  }
  if(hit >= hits.size() && hit <= 0){
   cout << "hit size: " << hits.size(); 
    cout <<"Invalid request" << endl;
    return;
  }
  
  Product* p = hits[hit-1];
  cart_[username].push_back(p);
}

void MyDataStore::viewCart(string username){
  if(usermap_.find(username) == usermap_.end()){
    cout <<"Invalid username" << endl;
    return;
  }

  for(size_t i = 0; i < cart_[username].size(); i++){
    cout << endl<<  "Item " << i+1 << endl << cart_[username][i]->displayString() << endl;
  }

}

void MyDataStore::buyCart(string username){ // ISSUE HERE
  vector<Product*> remain; 
  Product* curr;
  if(cart_.find(username) == cart_.end()){
    cout << "Invalid username"; 
    return;
  }
  for(size_t i = 0; i < cart_[username].size(); i++){
    // do the checks
    curr = cart_[username][i];
    // if item in stock and user has enough money, remove from cart, 
    // deduct quantity, reduce user credit
    // else: leave in cart;
    // if doesn't work, add to remaining

    if(!(usermap_[username]->getBalance() >= curr->getPrice() 
    && curr->getQty() > 0)){
      remain.push_back(curr);
    }
    else{
      usermap_[username]->deductAmount(curr->getPrice());
      curr->subtractQty(1);
    }
  }
  cart_[username] = remain;
}
