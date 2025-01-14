#include <iostream>
#include "Trad.h"

void print_eval_short(Trad<short>& t) {
    t.satt_in(short(5));
    t.satt_in(short(4));
    t.satt_in(short(7));
    t.satt_in(short(1));
    t.satt_in(short(3));
    t.satt_in(short(6));
    t.satt_in(short(8));
    t.satt_in(short(9));
    
    std::cout << "t1: ";
    t.skriv_ut();
    std::cout << std::endl;
    
    inmatning(t); //2
    inmatning(t); //7
    
    std::cout << "t2: ";
    t.skriv_ut();
    std::cout << std::endl;
}

void print_eval_double(Trad<double>& tf, Trad<double>& tf2) {
    tf.satt_in(double(5.01));
    tf.satt_in(double(4.12));
    tf.satt_in(double(7.23));
    tf.satt_in(double(1.34));
    tf.satt_in(double(3.45));
    tf.satt_in(double(6.56));
    tf.satt_in(double(8.67));
    tf.satt_in(double(9.78));
    
    std::cout << "tf1: ";
    tf.skriv_ut();
    std::cout << std::endl;
    
    tf2 = tf;
    
    std::cout << "tf2: ";
    tf.skriv_ut();
    std::cout << std::endl;
    
    if (tf == tf2)
        std::cout << "LIKA" << std::endl;
    else
        std::cout << "OLIKA" << std::endl;
    
    inmatning(tf2); //3.52
    
    if (tf == tf2)
        std::cout << "LIKA" << std::endl;
    else
        std::cout << "OLIKA" << std::endl;
    
    std::cout << "tf2: ";
    tf2.skriv_ut();
    std::cout << std::endl;
}

int main() {
    // For VPL evaluation
    Trad<short> t;
    print_eval_short(t);
    
    Trad<double> tf, tf2;
    print_eval_double(tf, tf2);
    
    return 0;
}

