#include "Dish.h"
#include "Vegetable.h"
using namespace Food;

int main(){
 Dish* supper[3];
 supper[0] = new Dish("Hamburgare", 1500);
 supper[1] = new Vegetable(true);
 supper[2] = new Dish("Tårta", 5000);
 for(int i = 0; i < 3; ++i)
 printDish(supper[i]);
 return 0;
}