
#include <ostream>

using namespace std;
class Klocka {
public:
 Klocka( int tim = 0, int min = 0, int sek = 0 );
 void setTime( int tim, int min, int sek );
 void getTime( int& tim, int& min, int& sek ) const;
 void ticka(); // Tick, Klockan ökar en sek.

bool operator==(const Klocka& other) const;

bool operator !=(const Klocka other) const;

bool operator <(const Klocka& other) const;

bool operator >(const Klocka& other) const;

bool operator <=(const Klocka& other) const;

bool operator >=(const Klocka& other) const;

const Klocka& operator++();

private:
int t, m, s; // tim, min, sek
friend ostream& operator<< (ostream& o, const Klocka&);

};

ostream& operator<< (ostream& o, const Klocka& klocka){
if (klocka.t<10){
    o << 0;
}
o << klocka.t << ":";
if (klocka.m<10){
    o << 0;
}
o << klocka.m << ":";
if (klocka.t<10){
    o << 0;
}
o << klocka.s;
return o;
}

Klocka::Klocka( int tim, int min, int sek ) {
 setTime( tim, min, sek );
}

bool Klocka::operator==(const Klocka& other) const{
    return((this->t == other.t) && (this->m == other.m) && (this->s == other.s));
}

bool Klocka::operator !=(const Klocka other) const {
    return!(*this==other);
}

bool Klocka::operator <(const Klocka& other) const{
   return (
   (this->t < other.t) || 
   (this->t < other.t) && (this->m < other.m) ||
   (this->t < other.t) && (this->m < other.m ) && (this->s < other.s)); 
}

bool Klocka::operator <=(const Klocka& other) const{
    return (*this<other || *this==other);
}

bool Klocka::operator >(const Klocka& other) const{
    return!(*this<=other);
}

bool Klocka::operator >=(const Klocka& other) const{
    return !(*this<other);
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

void Klocka::ticka() {
 s = ( s+1 ) % 60;
 if ( s==0 ) {
 m = ( m+1 ) % 60;
 if ( m==0 )
 t = ( t+1 ) % 24;
 }
}

void Klocka::setTime( int tim, int min, int sek ) {
    if (tim<24 && tim>=0){
        t = tim;
    } else t = 0;
    if (min<60 && min>=0){
        m = min;
    } else m = 0;
    if (sek<60 && sek>=0){
        s = sek;
    } else s = 0;
}

Klocka::Klocka(int tim, int min, int sek){
setTime(tim, min, sek);
}

void Klocka::getTime( int& tim, int& min, int& sek ) const{
    tim = t;
    min = m;
    sek = s;
}


