#include <iostream>

using namespace std;
class Rectangle {
public:
Rectangle(int width, int height){
    this->width = width;
    this->height = height;
}
Rectangle(){
    this->width = 0;
    this->height = 0;
}

Rectangle operator+(const Rectangle& other) const { 
    Rectangle resultat = *this;
    resultat.width += other.width;
    resultat.height += other.height;
    return resultat;
}

Rectangle operator+(int other) const {
Rectangle resultat = *this;
resultat.width += other;
resultat.height+=other;
return resultat;
}

Rectangle& operator=(const Rectangle& other){
    if (this != &other){
    this->width = other.width;
    this->height = other.height;
    }
    return *this;
}

Rectangle& operator+= (const Rectangle& other){
return *this = *this + other;
}

Rectangle& operator+= (int other){
return *this = *this + other;
}


const Rectangle& operator++(){
return *this += 1;
}

Rectangle operator++(int){
Rectangle temp = *this;
*this += 1;
    return temp;
}

bool operator==(const Rectangle& other) const{
return (this->width == other.width) && (this->height == other.height);
}

friend ostream& operator<<(ostream& o, const Rectangle& rect);
double area() const { return width*height; }
private:
 double height;
 double width;
};

ostream& operator<<(ostream& o, const Rectangle& rect){
o << "w: " << rect.width << ", h: " << rect.height << ", area: " << rect.area();
return o;
}

int main (){

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

