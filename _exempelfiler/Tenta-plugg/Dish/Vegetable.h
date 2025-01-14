#ifndef VEGETABLE_H
#define VEGETABLE_H

#include <iostream>
#include <string>
#include "Dish.h"


class Vegetable : public Food::Dish{
public:
 Vegetable(bool fr):Dish("Grönsak", 0), fibreRich(fr){}
private:
 bool fibreRich;
};

#endif