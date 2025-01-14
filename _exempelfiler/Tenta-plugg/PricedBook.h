#ifndef PricedBook.h
#define PricedBook.h
#include "Book.h"


class PricedBook : public Book::Book{
public:
 PricedBook(string t, int i, int p) : Book(t, i), price(p){}
private:
 int price;
};

#endif

