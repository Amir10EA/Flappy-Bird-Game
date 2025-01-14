#include <iostream>
using namespace std;

class Rectangle {
public:
 double area() const { return width*height; }
Rectangle (double height, double width);
Rectangle ();
Rectangle operator+ (const Rectangle& other) const;
Rectangle operator+(double d) const;
const Rectangle& operator+=(double d);
const Rectangle& operator+=(const Rectangle& other);
const Rectangle& operator++();
const Rectangle& operator++(int);
bool operator==(const Rectangle& other) const;

private:
 double height;
 double width;

 friend ostream& operator<<(ostream& o, const Rectangle& other);
};
Rectangle::Rectangle (double h, double w) : height(h), width(w){}
Rectangle::Rectangle () : height(0), width(0){}

Rectangle Rectangle::operator+ (const Rectangle& other) const {
Rectangle temp(*this);
temp += other;
return temp;
}

Rectangle Rectangle::operator+(double d) const {
Rectangle temp(*this);
temp += d;
return temp;
}

const Rectangle& Rectangle::operator+=(double d) {
height += d;
width += d;
return *this;
}

const Rectangle& Rectangle::operator+=(const Rectangle& other) {
height += other.height;
width += other.width;
return *this;
}

const Rectangle& Rectangle::operator++() {
    return (*this) +=1;
}

const Rectangle& Rectangle::operator++(int) {
    Rectangle temp (*this);
    (*this) += 1;
    return temp;
}

bool Rectangle::operator==(const Rectangle& other) const {
    return (height == other.height && width == other.width);
}

ostream& operator<<(ostream& o, const Rectangle& other) {
return o << "w: " << other.width << ", h: " << other.height << ", area: " << other.area() << endl;
}

main (){
Rectangle r1(2,4), r2(2,4);
 Rectangle r3(0,0), r4;
 Rectangle r5 = r1 + r2;
 ((r1==r2) ? r4+=0 : r4+=1);
 r2 += r1;
 r2 += 2;
 r3 = r2 + r4 + r5 + 5;
 r3++;
 ++r3;
 std::cout << "r3: " << r3 << '\n';
    return 0;
}