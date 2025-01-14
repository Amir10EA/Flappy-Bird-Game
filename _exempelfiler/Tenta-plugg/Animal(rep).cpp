
class Animal{
public:
 Animal(int v):vikt(v), refCount(0){}
 int getVikt() const { return vikt; }
private:
 int vikt;
 int refCount;
 friend class AnimalPointer;
};

class AnimalPointer{
public:
 AnimalPointer(Animal* a = 0);
 int getVikt() const { return theAnimal->getVikt(); }
 ~AnimalPointer() { delete theAnimal; }
~AnimalPointer();
AnimalPointer(const AnimalPointer& other);
const AnimalPointer& operator=(const AnimalPointer& other);


private:
 Animal* theAnimal;
};

AnimalPointer::AnimalPointer(Animal* a = 0):theAnimal(a){
if (theAnimal)
theAnimal->refCount++;
}
AnimalPointer::~AnimalPointer(){
if (theAnimal && --theAnimal->refCount < 1){
    delete theAnimal;
}
}
AnimalPointer::AnimalPointer(const AnimalPointer& other) : theAnimal(other.theAnimal){
    if (theAnimal)
    theAnimal->refCount++;
}
const AnimalPointer& AnimalPointer::operator=(const AnimalPointer& other){
    if (theAnimal != other.theAnimal){
    if (theAnimal && --theAnimal->refCount < 1){
    delete theAnimal;
    }
    theAnimal = other.theAnimal;
    theAnimal->refCount++;
} return *this;
}

