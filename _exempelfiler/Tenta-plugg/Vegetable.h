#ifndef VEGETABLE_H
#define VEGETABLE_H
#include "Dish.h"

class Vegetable : public Food::Dish{
public:
 Vegetable(bool fr);
private:
 bool fibreRich;
};

#endif