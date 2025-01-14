#ifndef TRAD_CPP
#define TRAD_CPP

#include "Trad.h"

template<typename T>
void Trad<T>::kopiera(const Trad<T>& t) {
    if (t.tomt())
        rot = 0;
    else {
        rot = new Nod(t.varde());
        v_barn().kopiera(t.v_barn());
        h_barn().kopiera(t.h_barn());
    }
}

template<typename T>
Trad<T>& Trad<T>::operator=(const Trad<T>& t) {
    if (rot != t.rot) {
        delete rot;
        kopiera(t);
    }
    return *this;
}

template<typename T>
bool Trad<T>::operator==(const Trad<T>& t) const {
    return (tomt() && t.tomt()) ||
           (!tomt() && !t.tomt() && varde() == t.varde() &&
            v_barn() == t.v_barn() && h_barn() == t.h_barn());
}

template<typename T>
void Trad<T>::skriv_ut() const {
    if (!tomt()) {
        v_barn().skriv_ut();
        std::cout << varde() << ' ';
        h_barn().skriv_ut();
    }
}

template<typename T>
bool Trad<T>::sok(const T& value) const {
    if (tomt()) {
        return false;
    }
    if (value == varde()) {
        return true;
    }
    if (value < varde()) {
        return v_barn().sok(value);
    }
    return h_barn().sok(value);
}

template<typename T>
void Trad<T>::satt_in(const T& value) {
    if (tomt()) {
        rot = new Nod(value);
        return;
    }
    
    if (value == varde()) {
        return;  // Value already exists
    }
    
    if (value < varde()) {
        v_barn().satt_in(value);
    } else {
        h_barn().satt_in(value);
    }
}

template<typename T>
void inmatning(Trad<T>& t) {
    T i;
    std::cout << "Mata in tal: ";
    std::cin >> i;
    if (t.sok(i))
        std::cout << "Finns redan i trädet!" << std::endl;
    else
        t.satt_in(i);
}

#endif /* TRAD_CPP */

