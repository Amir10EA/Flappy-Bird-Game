#include "Tenta_20_upg_2_konstruktorer.h"
#include <iostream>
Book::Book(const std::string& the_title,
 const std::string&the_author):
 title(the_title),
 author(the_author)
{
 info = new std::string[100];
 counter = 0;
}

Book::Book (const Book& other) : title(other.title), author(other.author), counter(other.counter){
    info = new std::string[100];
    for (int i = 0; i < 100; ++i){
        info[i] = other.info[i];
    }
}

Book::~Book(){
    delete[] info;
}

const Book& Book::operator=(const Book& other){
if (this != &other){
    delete[] info;
    title = other.title;
    author = other.author;
    counter = other.counter;
    info = new std::string[100];
    for (int i = 0; i<100; ++i){
        info[i] = other.info[i];
    }
}
return *this;
}

void Book::addInfo(std::string new_info){
 info[counter++] = new_info;
}
std::string Book::getInfo(int index) {
 return info[index];
}
std::string Book::getTitle() const {
 return title;
}
std::string Book::getAuthor() const {
 return author;
}