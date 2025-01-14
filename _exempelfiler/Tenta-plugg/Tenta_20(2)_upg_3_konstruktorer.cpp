#include "vector"

#include <iostream>
#include <string>
using namespace std;


class Managed{
public:
 Managed(std::string d):data(d){ objects.push_back(this); }
//copy konstruktor
Managed(const Managed& m):data(m.data){
objects.push_back(this);
}

//inga objekt eller pointer ändrades, vi kan använda default.
Managed& operator=(const Managed&) = default;



~Managed() {
    for (int i = 0; i<objects.size(); ++i){
        if (objects[i] == this){
            objects.erase(objects.begin() + i);
        }
        break;
    }
}


 std::string get_data() const { return data; }

private:
 std::string data;
 static std::vector<Managed *> objects;
}; // Managed
std::vector<Managed *> Managed::objects; 