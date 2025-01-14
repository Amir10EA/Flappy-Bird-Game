#ifndef PRICEDBOOK_H
#define PRICEDBOOK_H


#include <iostream>
#include <string>
#include "Book.h"


class PricedBook : public books::Book { 
public:
 PricedBook(std::string t, int i, int p);
private:
 int price;
};
#endif