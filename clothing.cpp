#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "clothing.h"
#include "product.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand)
  : Product("clothing", name, price, qty), size_(size), brand_(brand)
  {


  }

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> keys = parseStringToWords(name_);
    keys.insert(convToLower(this->size_));
    keys.insert(convToLower(this->brand_));
    return keys;
}

std::string Clothing::displayString() const{
  std::ostringstream oss;
    oss << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n"
        << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Clothing::dump(std::ostream& os) const{
  //cout << "dumping clothing " << endl;
  os << "clothing" << endl << name_ << endl << price_ << endl << qty_ << endl << size_ << endl << brand_ << endl;
}
