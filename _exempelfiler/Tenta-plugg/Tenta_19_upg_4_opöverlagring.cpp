#include <stdexcept>
#include <iostream>

class Klocka{
public:
 explicit Klocka(int h=0, int m=0);
 const Klocka& operator +=(int n);
 Klocka operator+ (int n) const;
 const Klocka& operator++();
 const Klocka& operator++(int);

private:
 int mem; // Minuter efter midnatt 
 friend std::ostream& operator<<(std::ostream& o, const Klocka& klocka);
};

explicit Klocka::Klocka(int h=0, int m=0):mem(h*60+m){
 if (mem > 60 * 24)
 throw std::out_of_range("Ogilltigt klockslag!");
 }

 const Klocka& Klocka::operator +=(int n){
 if (mem+n > 60 * 24)
 throw std::out_of_range("Ogilltigt klockslag!");
 mem += n;
 return *this;
 } 
 
 Klocka Klocka::operator+(int n) const{
 Klocka temp(*this);
 return (temp += n);
 }

 Klocka operator+(int n, const Klocka& other) {
 return (other + n);
 }

 const Klocka& Klocka::operator++(){
 return (*this += 1);
 }

 const Klocka& Klocka::operator++(int){
 Klocka temp(*this);
 (*this) += 1;
 return temp;
 }

std::ostream& operator<<(std::ostream& o, const Klocka& klocka){
    return o << klocka.mem/60 << ":" << klocka.mem%60;
}