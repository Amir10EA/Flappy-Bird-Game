#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <string>


namespace Food{

 class Dish{
 public:
 Dish(std::string n, int c);
 std::string getName() const;
 int getCalories() const;
 private:
 std::string name;
 int calories;
 };
 void printDish(Dish* dish);
} 
#endif