#include "PricedBook.cpp"
#include <iostream>
#include <string> 
using namespace std;
#include "Book.cpp"
using namespace books;
int main(){
 Book* theBooks[3];
 theBooks[0] = new Book("Telefonkatalogen", 245005746);
 theBooks[1] = new PricedBook("C++ direkt", 914401463, 407);
 theBooks[2] = new PricedBook("Ondskan", 916420051, 39);
 for(int i = 0; i < 3; ++i)
 showBook(theBooks[i]);
 return 0;
}