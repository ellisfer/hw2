#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include "book.h"

using namespace std;

Book::Book(const std::string name, double price, int qty, const std::string isbn, const std::string author)
  : Product("book", name, price, qty), isbn_(isbn), author_(author)
  {

  }

std::set<std::string> Book::keywords() const{
  std::set<std::string> keys = parseStringToWords(name_);
  set<string> authkey = parseStringToWords(author_);
  
  keys = setUnion(keys, authkey);
  keys.insert(this->isbn_);
  return keys;
}

std::string Book::displayString() const{
  std::ostringstream oss;
    oss << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
        << price_ << " " <<  qty_ << " left.";
    return oss.str();
}

void Book::dump(std::ostream& os) const{
  //cout << "dumping book" << endl;
  os << "book" << endl << name_ << endl << price_ << endl << qty_ << endl << isbn_ << endl << author_ << endl;
}
