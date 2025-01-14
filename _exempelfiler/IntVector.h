//Amir Eihab El Abidou, amel6385

// Labb2, IntVector.h – klassdefinition
#ifndef __IntVector
#define __IntVector
#include <initializer_list>
#include <iostream>

using namespace std;

class IntVector
{
public:
    // Om man vill skapa en IntVector med en lista av värden direkt, t.ex.:
    // IntVector v = {1, 2, 3, 4};
    // så används denna konstruktor som tar emot en initializer_list.
    IntVector(const initializer_list<int> &intlist);

    // Tom lista
    IntVector();

    // Om man har skapat en int lista genom:
    // int arr[] = {1, 2, 3, 4};
    // så har man en int pekare till första elementet, därför ska det finnas en konstruktor som accepterar int pekare.
    IntVector(const int *intlist);

    // copy-konstruktor: Om man vill skapa en kopia av en befintlig IntVector, t.ex.:
    // IntVector original = {1, 2, 3};
    // IntVector kopia(original);
    // så används denna kopieringskonstruktor som skapar en ny IntVector med samma innehåll som den ursprungliga.
    IntVector(const IntVector &other);

    // move-konstruktor: Om man vill flytta innehållet från en temporär IntVector till en ny, t.ex.:
    // IntVector v = getIntVector();
    // Där getIntVector() returnerar en temporär IntVector
    // && = refererar till ett temporärt objekt (rvalue)
    IntVector(IntVector &&other); // move

    // Kopierar innehållet från ett objekt till ett annat.
    // "const" innebär att vi inte kan ändra det returnerade objektet, vilket möjliggör kedjad tilldelning (ex. a = b = c;).
    // "&" gör att vi tar emot en referens till det andra objektet, utan att skapa en onödig kopia.
    const IntVector& operator=(const IntVector &other);

    // Gör det möjligt att komma åt och modifiera element i vektorn via index.
    // "&" innebär att vi returnerar en referens till elementet så att vi kan ändra det direkt (t.ex. v[0] = 10).
    int & operator[](int pos) const;

    int size () const;

    void push_back(const int &value);

    ~IntVector();

private:
    int _size;
    // pekar på det första elementet och kan manipuleras för att komma åt de andra
    int *data;


// Vänfunktion som gör det möjligt att skriva ut innehållet i en IntVector.
// Den överlagrar <<-operatorn för att skriva ut elementen i vektorn som en lista,
// exempelvis: [1, 2, 3, 4]. "const" gör att objektet inte modifieras, "&" 
// gör att vi arbetar med originalet och inte en kopia, och returtypen gör att 
// vi kan kedja flera utskrifter.
    friend std::ostream& operator<<(std::ostream& os, const IntVector& t);
};

#endif