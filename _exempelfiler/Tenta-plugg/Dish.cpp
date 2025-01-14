#include "Dish.h"
#include <iostream>
#include <string>
using namespace std;

using namespace Food;


 Dish::Dish(string n, int c):name(n), calories(c){}
 string Dish::getName() const { return name; }
 int Dish::getCalories() const { return calories; }

 void printDish(Dish* dish){
 cout << dish->getName() << ": " << dish->getCalories() << endl;
 }
