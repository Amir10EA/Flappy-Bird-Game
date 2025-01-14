#include <vector>
#include <string>

using namespace std;

class Shape{

public:
virtual double getArea() = 0;
virtual ~Shape();

string getName() const { return name;}

protected:
Shape(string n) : name(n){}
double area;

private:
Shape(const Shape& other) = delete;
const Shape& operator=(const Shape& other) = delete;
string name;
};

//----------------------------------------------------------------//

class Circle : public Shape{

public:
double getArea(){
    return 3.14*radius*radius;
}
static Circle* getInstance(double r){
    return new Circle(r);
}
double getRadie() const { return radius;}

protected:
Circle(double r) : Shape("Circle"), radius(r) {
    area = getArea();
}

private:
double radius;
Circle(const Circle& other) = delete;
const Circle& operator=(const Circle& other) = delete;
};

//----------------------------------------------------------------//

class Polygon : public Shape{
    public:
    virtual double getArea() = 0;
    virtual int getHörn() = 0;
    virtual ~Polygon();
    protected:
    Polygon(string name, int h) : Shape(name), hörn(h){}
    private:
    Polygon(const Polygon& other) = delete;
    const Polygon& operator=(const Polygon& other) = delete;
    int hörn;
};

class Triangle : public Polygon{
  public:
double getArea(){
    return (bas*höjd)/2.0;
}
int getHörn(){
    return 3;
}

static Triangle* getInstance(double bas, double höjd){
    return new Triangle(bas, höjd);
}
virtual ~Triangle();

protected:
Triangle(double b, double h) : Polygon("Triangle", 3), bas(b), höjd(h){
    area = getArea();
}

private:
double bas;
double höjd;
Triangle(const Triangle& other) = delete;
const Triangle& operator=(const Triangle& other) = delete;  
};

class Compound : public Polygon {
    public:
    double getArea(){
    double area = 0.0;
    for (Shape* shape : shapes){
        area += shape->getArea();
    }
    return area;
    }
 
    int getHörn(){
        int hörn = 0;
        for (Shape* shape : shapes){
            if (Polygon* p = dynamic_cast<Polygon*>(shape)){
                hörn += p->getHörn();
            }
        }
        return hörn;
    }
    
    static Compound* getInstance() { return new Compound(); }

    virtual ~Compound(){
        shapes.clear();
    }
    void addshape(Shape* s){
        shapes.push_back(s);
    }
    protected:
    Compound() : Polygon("Compound", 0){}

    private:
    vector<Shape*> shapes;
    Compound(const Compound& other) = delete;
    const Compound& operator=(const Compound& other) = delete;
};