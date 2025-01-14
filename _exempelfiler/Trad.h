#ifndef TRAD_H
#define TRAD_H

#include <iostream>

template<typename T>
class Trad {
public:
    Trad() : rot(0) {};                    // default constructor
    Trad(T d) { rot = new Nod(d); };       // constructor with data
    Trad(const Trad<T>& t) { kopiera(t); }; // copy constructor
    ~Trad() { delete rot; };

    bool tomt() const { return !rot; };
    T& varde() const {
        koll();
        return rot->data;
    };
    Trad<T>& v_barn() const {
        koll();
        return *rot->vanster;
    };
    Trad<T>& h_barn() const {
        koll();
        return *rot->hoger;
    };
    
    Trad<T>& operator=(const Trad<T>&);
    bool operator==(const Trad<T>&) const;
    void skriv_ut() const;
    
    bool sok(const T& value) const;
    void satt_in(const T& value);

private:
    class Nod {
        friend class Trad;
        T data;
        Trad<T> *vanster, *hoger;
        Nod(T d) : data(d), vanster(new Trad<T>), hoger(new Trad<T>) {};
        ~Nod() {
            delete vanster;
            delete hoger;
        };
    }; // end class Nod

    Nod *rot;
    void koll() const {
        if (tomt())
            throw std::range_error("Trad");
    }
    void kopiera(const Trad<T>& t);
};

// Template function declaration
template<typename T>
void inmatning(Trad<T>& t);

#include "Trad.cpp" // Include the implementation file

#endif /* Trad_h */

