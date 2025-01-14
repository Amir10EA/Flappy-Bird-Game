//Amir Eihab El Abidou, amel6385
// Labb3, Datum.h – klassdefinition

#ifndef DATUM_H
#define DATUM_H

#include <array>
#include <iostream>

class Datum
{
  friend std::ostream &operator<<( std::ostream &, const Datum & );
  friend Datum operator+(int, const Datum & );
  
  unsigned int year;
  unsigned int month;
  unsigned int day;
  
  // Deklaration av statisk privat medlem, "ant_dagar per månad"
  static const std::array< unsigned int, 13 > ANT_DAGAR_PER_MAANAD;
  //void step_one_day(); // Öka datum med en dag
   private:
   void step_one_day(); // Öka datum med en dag
public:
  Datum();
  Datum( int, int, int );
  void set_date( int, int, int ); // set year, month, day

  
  //OBS. funktionen "step_one_day()" bör vara PRIVATE
 
  static bool is_skott_aar( int ); // Är det skottår?
  bool end_of_month( int ) const; // Är dagen den sista i månaden?


  //medlemsfunktioner
  bool operator==(const Datum& other) const;
  bool operator!=(const Datum& other) const;
  bool operator<(const Datum& other) const;
  bool operator>(const Datum& other) const;
  bool operator<=(const Datum& other) const;
  bool operator>=(const Datum& other) const;

  const Datum& operator++(); //prefix
  const Datum operator++(int); //postfix

  const Datum& operator+=(int);

  const Datum operator+(int) const;
  
};

#endif

