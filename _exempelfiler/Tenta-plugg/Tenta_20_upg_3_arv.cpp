#include <iostream>
#include <vector>

class Vehicle{

public:
int getPassengers() const { return passenger_load; }
std::string getReg() const { return reg_nr; }
virtual void message() =0;
virtual ~Vehicle() {}

protected:
Vehicle(std::string r = "", int ant=0):reg_nr(r),
passenger_load(ant){}

private:
int passenger_load;
std::string reg_nr;
const Vehicle& operator=(const Vehicle& other){};
Vehicle(const Vehicle& other);
};


class Car : public Vehicle {
public:
static Car* getInstance(std::string r = "", int ant=0){
return new Car(r, ant);
}
 
 void message() {
 std::cout<< getReg() << " Typ: Bil\n";
 }
private:
Car (std::string r = "", int ant=0): Vehicle(r, ant) {}
};


class Truck : public Vehicle{
public:
 static Truck* getInstance (std::string r = "", int ant=0, int kg=0) {
 return new Truck(r, ant, kg);
 }
 int getMaxLoad() const { return max_load; }
 void message() {
 std::cout<< getReg() << " Typ: Lasbil\n";
 }
private:
Truck (std::string r = "", int ant=0, int kg=0): Vehicle(r, ant), max_load(kg){}
int max_load;
};

int main() {
    std::vector<Vehicle*> vehicles;

    // Lägg till fordon i vektorn
    vehicles.push_back(Car::getInstance("ABC 123", 5));
    vehicles.push_back(Truck::getInstance("TUV 987", 2, 30000));

    // Räkna totala antalet passagerare
    int totalAntPassagerare = 0;
    for (const auto& vehicle : vehicles) {
        totalAntPassagerare += vehicle->getPassengers();
    }

    std::cout << "Totalt antal passagerare = " << totalAntPassagerare << std::endl;

    // Anropa message för varje fordon
    for (const auto& vehicle : vehicles) {
        vehicle->message();
    }

    return 0;
}