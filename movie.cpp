#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include "movie.h"

using namespace std;

Movie::Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating)
  : Product("movie", name, price, qty), genre_(genre), rating_(rating)
  {

  }

std::set<std::string> Movie::keywords() const{
  std::set<std::string> keys = parseStringToWords(name_);
  keys.insert(this->genre_);
  keys.insert(this->rating_);
  // cout << "movie.cpp 20 printing keywords: " << endl;
  // set<string>::iterator it;
  // for(it = keys.begin(); it!= keys.end(); ++it){
  //   cout << *it << endl;
  // }
  return keys;
}

std::string Movie::displayString() const{
  std::ostringstream oss;
    oss << name_ << "\n" << "Genre: "<< genre_ << " Rating: " << rating_ << "\n"
        << price_ << " "<< qty_ << " left.";
    return oss.str();
}

void Movie::dump(std::ostream& os) const{
  //cout << "dumping movie " << endl;
  os << "movie" << endl << name_ << endl << price_ << endl << qty_ << endl << genre_ << endl << rating_ << endl;
}
