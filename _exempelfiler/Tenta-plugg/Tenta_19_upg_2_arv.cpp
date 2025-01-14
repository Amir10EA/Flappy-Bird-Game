#include <string>
#include <iostream>
#include <vector>

class Djur {
    public:
    std::string getNamn() const { return namn; }
    int getVikt() const { return vikt; }
    virtual int getVarde() const =0;
    virtual ~Djur(){}

    protected:
    Djur(std::string namn, int vikt) : vikt(vikt), namn(namn) {}

    private:
    int vikt;
    std::string namn;
    Djur(const Djur& other) = delete;
    const Djur& operator=(const Djur& other) = delete;
};

class Elefant : public Djur {
public:
static Elefant* getInstance(std::string n, int v, int s);
 int getSnabel() const { return snabel; }
 void setSnabel(int nySnabel){ snabel = nySnabel; }
 int getVarde() const { return snabel * getVikt(); }

protected:
Elefant(std::string n, int v, int s): Djur(n,v), snabel(s){}

private:
int snabel;
};

Elefant* Elefant::getInstance(std::string n, int v, int s){
    return new Elefant(n,v,s);
} 

class Tusenfoting : public Djur{
public:
static Tusenfoting* getInstance(std::string n,int v);

 ~Tusenfoting() { delete [] fotter; }

 void setFot(int pos, double vad){ fotter[pos] = vad; }
 int getVarde() const {
 double sum = 0;
 for(int i=0; i<1000; i++)
 sum += fotter[i];
 return getVikt() + static_cast<int>(sum);
 }
protected:
Tusenfoting(std::string n,int v): Djur(n,v){
fotter =new double[1000];
 }
private:

 double* fotter;
};

Tusenfoting* Tusenfoting::getInstance(std::string n,int v){
    return new Tusenfoting(n,v);
}

int main(){
 std::vector<Djur*> flock;
 flock.push_back(Elefant::getInstance("Jumbo", 5000, 2));
 flock.push_back(Tusenfoting::getInstance("Milloped", 0));

int summaVarde = 0;
int snabelSumma = 0;
int elefantAntal = 0;
 
 for (Djur* djur : flock){
    summaVarde += djur->getVarde();
    if (Elefant * e = dynamic_cast<Elefant*>(djur)){
        snabelSumma += e->getSnabel();
        elefantAntal++;
    }
    
 }
 

 std::cout << "Värdet totalt: " << summaVarde << std::endl;
 if (elefantAntal == 0)
 std::cout << "Inga elefanter!" << std::endl;
 else {
 std::cout << "Genomsnittlig snabel: " <<
 static_cast<double>(snabelSumma) / elefantAntal << std::endl;
 }
 return 0;
}