#include <ostream>
using namespace std;

class Klocka {
public:
 Klocka( int tim = 0, int min = 0, int sek = 0 );
 void setTime( int tim, int min, int sek );
 void getTime( int& tim, int& min, int& sek ) const;
 void ticka(); // Tick, Klockan ökar en sek.
 
 bool operator<(const Klocka& other) const;
 bool operator<=(const Klocka& other)const;
 bool operator>(const Klocka& other)const;
 bool operator>=(const Klocka& other)const;
 bool operator==(const Klocka& other)const;
 bool operator!=(const Klocka& other)const;
 const Klocka& operator++();

private:
 int t, m, s; // tim, min, sek
 friend ostream& operator<<(ostream& o, const Klocka other);
};
Klocka::Klocka( int tim, int min, int sek ) {
 setTime( tim, min, sek );
}
void Klocka::ticka() {
 s = ( s+1 ) % 60;
 if ( s==0 ) {
 m = ( m+1 ) % 60;
 if ( m==0 )
 t = ( t+1 ) % 24;
 }
}

bool Klocka::operator<(const Klocka& other) const{
return (
    t < other.t ||
    t < other.t && m < other.m ||
    t < other.t && m < other.m && s < other.s
);
}

bool Klocka::operator<=(const Klocka& other)const{
return (*this == other) || (*this < other);
}

 bool Klocka::operator>(const Klocka& other)const{
    return !(*this<=other);
 }

 bool Klocka::operator>=(const Klocka& other)const{
    return !(*this<other);
 }

bool Klocka::operator==(const Klocka& other) const{
    return (!(*this < other) && !(other < *this));
}

 bool Klocka::operator!=(const Klocka& other)const{
    return !(*this == other);
 }

 const Klocka& Klocka::operator++(){
    s = ( s+1 ) % 60;
 if ( s==0 ) {
 m = ( m+1 ) % 60;
 if ( m==0 )
 t = ( t+1 ) % 24;
 }
 return *this;
 }

ostream& operator<<(ostream& o, const Klocka other){
    
}