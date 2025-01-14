//Amir Eihab El Abidou, amel6385
// Labb3, Datum.cpp – definitioner av icke-triviala medlemsfunktioner

#include <iostream>
#include <string>
#include "Datum.h"

// Initialisera statisk medlem
// (första elementet används inte i denna lösning!)
const std::array< unsigned int, 13 > Datum::ANT_DAGAR_PER_MAANAD = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
std::array<std::string, 12> months = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };


// Konstruktor
Datum::Datum(){
  year = 2000;
  month = 1;
  day = 1;
}

Datum::Datum( int year, int month, int day  )
{
  
  if (!(year >= 2000 && year <= 2100)){
    throw std::invalid_argument("Året måste vara mellan >= 2000 och <= 2100");
  }
  if (!(month >= 1 && month <= 12)){
    throw std::invalid_argument("Månaden måste vara >= 1 och <= 12");
  }
  if (!(day >= 1 && day <= (month == 2 && is_skott_aar(year) ? 29 : ANT_DAGAR_PER_MAANAD[month]))){
    throw std::invalid_argument("Dagen stämmer inte med år och månad");
  }
  set_date( year, month, day);
}

void Datum::set_date( int yy, int mm, int dd )
{
  // Glöm inte att kontrollera inmatade värden, annars "exception"
  year = yy;
  month = mm;
  day = dd;
}

// Denna medlemsfunktion är tänkt att lägga till 1 dag till befintligt datum.
// Om sista dagen i månaden, så byt månad.
//     Om skottår, så ta hänsyn till att februari(månad 2) har 29 dagar.
// Om sista dagen på året, så byt år.
void Datum::step_one_day()
{
  // Dagen är inte sista dagen i månaden!
  if ( !end_of_month( day ) )
    ++day;
  else
    if ( month < 12 )
    {
      ++month;
      day = 1;
    }
    else
    {
      ++year;
      month = 1;
      day = 1;
    }
}

// Returnera true om yy(year) är skottår!
bool Datum::is_skott_aar( int yy )
{
  if ( yy % 400 == 0 ||
      ( yy % 100 != 0 && yy % 4 == 0 ) )
    return true;
  else
    return false;
}

// Är det sista dagen (dd) i månaden?
bool Datum::end_of_month( int dd ) const
{
  if ( month == 2 && is_skott_aar( year ) )
    return dd == 29;
  else
    return dd == ANT_DAGAR_PER_MAANAD[ month ];
}

// operator<<
// operator<<
std::ostream &operator<<( std::ostream &output, const Datum &d )
{
  // OBS. Glöm inte att modifiera vad som skrivs ut!
  output << d.day << " " << months[d.month-1] << " " << d.year;
  return output;
  
}


Datum operator+(int numOfDays, const Datum & date){
  Datum result = date;

  while (numOfDays>0) {
      result.step_one_day();
      --numOfDays;
    }
    return result;
}

 bool Datum::operator==(const Datum& other) const{
  return ((this->year == other.year) && (this->month == other.month) && (this->day == other.day));
 }

  bool Datum::operator!=(const Datum& other) const{
    return!(*this == other);
  }

  bool Datum::operator<(const Datum& other) const{
    if (other.year < this->year) return false;
    else if (other.year == this->year && other.month < this->month){return false;}
    else if (other.year == this->year && other.month == this->month && other.day < this->day){return false;}
    else if (other.year == this->year && other.month == this->month && other.day == this->day){return false;}
    else return true;
  }

  bool Datum::operator>(const Datum& other) const{
    return (other<*this);
  }

  bool Datum::operator<=(const Datum& other) const{
    return (*this == other || *this < other);
  }

  bool Datum::operator>=(const Datum& other) const{
    return (*this == other || *this > other);
  }

  //prefix
  const Datum& Datum::operator++(){
    return *this += 1;
  }
  //postfix
  const Datum Datum::operator++(int){
    Datum temp = *this;
    ++*this;
    return temp;
  } 

  const Datum& Datum::operator+=(int numOfDays){
    while (numOfDays>0) {
      this->step_one_day();
      --numOfDays;
    }

    return *this;
  }

  const Datum Datum::operator+(int numOfDays) const{
    Datum result = *this;
    
    while (numOfDays>0) {
      result.step_one_day();
      --numOfDays;
    }

    return result;
  }
  