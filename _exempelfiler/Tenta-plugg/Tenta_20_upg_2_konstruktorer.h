#ifndef BOOKH
#define BOOKH
#include <string>
class Book {
public:
 Book(const std::string& the_title,
 const std::string& the_author);
 void addInfo(std::string new_info);
 std::string getInfo(int index);
 std::string getTitle() const;
 std::string getAuthor() const;
 
Book (const Book& other);
~Book();
const Book& operator=(const Book& other);

private:
 std::string title;
 std::string author;
 std::string* info;
 int counter;
};
#endif
