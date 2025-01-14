#include <iostream>
#include <string>
#include "Book.h"
using namespace std;
namespace books{
 
 Book::Book(string t, int i):title(t), isbn(i){}
 string Book::getTitle() const { return title; }
 int Book::getISBN() const { return isbn; }

 void showBook(Book* b){
 cout << b->getTitle()<< ": "<<b->getISBN()<<endl;
 }
}